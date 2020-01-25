#ifndef HTML5_DOM_OBJECT_WRAP_H
#define HTML5_DOM_OBJECT_WRAP_H

#include "port.h"

#define html5_dom_object_unwrap(obj) ((html5_dom_object_wrap_t *)((char *)(obj) - XtOffsetOf(html5_dom_object_wrap_t, std)));

#define HTML5_DOM_METHOD_PARAMS(T) \
	zval *self_php_object = getThis(); \
	html5_dom_object_wrap_t *self_object = html5_dom_object_unwrap(Z_OBJ_P(self_php_object)); \
	T *self = (T *) self_object->ptr;

typedef struct html5_dom_object_wrap html5_dom_object_wrap_t;
typedef int (html5_dom_prop_handler_t)(html5_dom_object_wrap_t *obj, zval *val);

struct html5_dom_object_wrap {
	void *ptr;											// custom payload
	HashTable *prop_handler;							// handlers for class properties
	zend_long iter;										// offset for iterator
	void (*free_handler)(html5_dom_object_wrap_t *obj);	// free handler
	zend_object std;									// self object
};

typedef struct {
	html5_dom_prop_handler_t *read;
	html5_dom_prop_handler_t *write;
} html5_dom_prop_handlers_t;

typedef struct {
	const char name[64];
	html5_dom_prop_handlers_t handlers;
} html5_dom_prop_handlers_init_t;

// Object wrap
html5_dom_object_wrap_t *html5_dom_object_wrap_create(zend_class_entry *ce, zend_object_handlers *handlers);
void html5_dom_object_wrap_free(html5_dom_object_wrap_t *object);

// Property handlers
void html5_dom_prop_handler_init(HashTable *hash);
void html5_dom_prop_handler_add(HashTable *hash, html5_dom_prop_handlers_init_t *list);
void html5_dom_prop_handler_free(HashTable *hash);

// Generic property handlers
zval *html5_dom_get_property_ptr_ptr(zval *object, zval *member, int type, void **cache_slot);
zval *html5_dom_read_property(zval *object, zval *member, int type, void **cache_slot, zval *rv);
HashTable *html5_dom_get_debug_info(zval *object, int *is_temp);
int html5_dom_has_property(zval *object, zval *member, int has_set_exists, void **cache_slot);

#if PHP_VERSION_ID > 70400
zval *html5_dom_write_property(zval *object, zval *member, zval *value, void **cache_slot);
#else
void html5_dom_write_property(zval *object, zval *member, zval *value, void **cache_slot);
#endif

#endif // HTML5_DOM_OBJECT_WRAP_H
