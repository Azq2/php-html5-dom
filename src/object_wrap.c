#include "object_wrap.h"
#include "zend_smart_str.h"

static inline void *_object_alloc(size_t obj_size, zend_class_entry *ce) {
	void *obj = emalloc(obj_size + zend_object_properties_size(ce));
	/* Subtraction of sizeof(zval) is necessary, because zend_object_properties_size() may be
	 * -sizeof(zval), if the object has no properties. */
	memset(obj, 0, obj_size - sizeof(zval));
	return obj;
}

html5_dom_object_wrap_t *html5_dom_object_wrap_create(zend_class_entry *ce, zend_object_handlers *handlers) {
	html5_dom_object_wrap_t *intern = _object_alloc(sizeof(html5_dom_object_wrap_t), ce);
	intern->free_handler = NULL;
	zend_object_std_init(&intern->std, ce);
	object_properties_init(&intern->std, ce);
	intern->std.handlers = handlers;
	return intern;
}

void html5_dom_object_wrap_free(html5_dom_object_wrap_t *intern) {
	if (intern->free_handler)
		intern->free_handler(intern);
	zend_object_std_dtor(&intern->std);
}

void html5_dom_prop_handler_init(HashTable *hash) {
	zend_hash_init(hash, 0, NULL, NULL, 1);
}

void html5_dom_prop_handler_add(HashTable *hash, html5_dom_prop_handlers_init_t *list) {
	int i = 0;
	while (list[i].handlers.read) {
		zend_string *str = zend_string_init_interned(list[i].name, strlen(list[i].name), 1);
		zend_hash_add_mem(hash, str, &list[i].handlers, sizeof(list[i].handlers));
		zend_string_release(str);
		++i;
	}
}

void html5_dom_prop_handler_free(HashTable *hash) {
	zend_hash_destroy(hash);
}

zval *html5_dom_get_property_ptr_ptr(zval *object, zval *member, int type, void **cache_slot) {
	html5_dom_object_wrap_t *obj = html5_dom_object_unwrap(Z_OBJ_P(object))
	
	zend_string *member_str = zval_get_string(member);
	zval *retval = NULL;
	
	if (!obj->prop_handler || !zend_hash_exists(obj->prop_handler, member_str))
		retval = zend_get_std_object_handlers()->get_property_ptr_ptr(object, member, type, cache_slot);
	
	zend_string_release(member_str);
	
	return retval;
}

zval *html5_dom_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv) {
	html5_dom_object_wrap_t *obj = html5_dom_object_unwrap(Z_OBJ_P(object));
	zend_string *member_str = zval_get_string(member);
	zval *retval;
	html5_dom_prop_handlers_t *handlers = NULL;
	
	if (obj->prop_handler != NULL)
		handlers = zend_hash_find_ptr(obj->prop_handler, member_str);
	
	if (handlers->read) {
		if (handlers->read(obj, rv)) {
			retval = rv;
		} else {
			retval = &EG(uninitialized_zval);
		}
	} else {
		retval = zend_get_std_object_handlers()->read_property(object, member, type, cache_slot, rv);
	}
	
	zend_string_release(member_str);
	
	return retval;
}

// PHP internal API very unstable.
// Why if i write extension in perl - it works  without any changes after each new version?! :(
#if PHP_VERSION_ID > 70400
zval *html5_dom_write_property(zval *object, zval *member, zval *value, void **cache_slot) {
	html5_dom_object_wrap_t *obj = html5_dom_object_unwrap(Z_OBJ_P(object));
	zend_string *member_str = zval_get_string(member);
	html5_dom_prop_handlers_t *handlers = NULL;
	
	if (obj->prop_handler != NULL)
		handlers = zend_hash_find_ptr(obj->prop_handler, member_str);
	
	if (handlers->write) {
		handlers->write(obj, value);
	} else {
		value = zend_get_std_object_handlers()->write_property(object, member, value, cache_slot);
	}
	
	zend_string_release(member_str);
	
	return value;
}
#else
void html5_dom_write_property(zval *object, zval *member, zval *value, void **cache_slot) {
	html5_dom_object_wrap_t *obj = html5_dom_object_unwrap(Z_OBJ_P(object));
	zend_string *member_str = zval_get_string(member);
	html5_dom_prop_handlers_t *handlers = NULL;
	
	if (obj->prop_handler != NULL)
		handlers = zend_hash_find_ptr(obj->prop_handler, member_str);
	
	if (handlers->write) {
		handlers->write(obj, value);
	} else {
		zend_get_std_object_handlers()->write_property(object, member, value, cache_slot);
	}
	
	zend_string_release(member_str);
}
#endif

int html5_dom_has_property(zval *object, zval *member, int has_set_exists, void **cache_slot) {
	html5_dom_object_wrap_t *obj = html5_dom_object_unwrap(Z_OBJ_P(object));
	zend_string *member_str = zval_get_string(member);
	html5_dom_prop_handlers_t *handlers = NULL;
	
	if (obj->prop_handler != NULL)
		handlers = zend_hash_find_ptr(obj->prop_handler, member_str);
	
	int retval = 0;
	
	if (handlers->read) {
		zval tmp;
		
		switch (has_set_exists) {
			default:
				retval = 1;
			break;
			
			case ZEND_ISEMPTY:
				if (handlers->read(obj, &tmp)) {
					retval = zend_is_true(&tmp);
					zval_ptr_dtor(&tmp);
				}
			break;
			
			case 0:
				if (handlers->read(obj, &tmp)) {
					retval = (Z_TYPE(tmp) != IS_NULL);
					zval_ptr_dtor(&tmp);
				}
			break;
		}
	} else {
		retval = zend_get_std_object_handlers()->has_property(object, member, has_set_exists, cache_slot);
	}
	
	zend_string_release(member_str);
	
	return retval;
}

HashTable *html5_dom_get_debug_info(zval *object, int *is_temp) {
	html5_dom_object_wrap_t *obj = html5_dom_object_unwrap(Z_OBJ_P(object));
	
	*is_temp = 1;
	
	HashTable *debug_info, *std_props;
	zend_string *string_key;
	html5_dom_prop_handlers_t *handlers;
	
	std_props = zend_std_get_properties(object);
	debug_info = zend_array_dup(std_props);
	
	if (!obj->prop_handler)
		return debug_info;
	
	zend_string *object_str = zend_string_init(ZEND_STRS("(object value omitted)") - 1, 0);
	
	ZEND_HASH_FOREACH_STR_KEY_PTR(obj->prop_handler, string_key, handlers) {
		zval value;
		
		if (!string_key || !handlers->read(obj, &value))
			continue;
		
		// Prevent recursion dump
		if (Z_TYPE(value) == IS_OBJECT) {
			zval_ptr_dtor(&value);
			ZVAL_NEW_STR(&value, object_str);
			zend_string_addref(object_str);
		}
		
		zend_hash_add(debug_info, string_key, &value);
	} ZEND_HASH_FOREACH_END();
	
	zend_string_release(object_str);
	
	return debug_info;
}
