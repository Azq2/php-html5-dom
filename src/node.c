#include "node.h"
#include "zend_exceptions.h"
#include "zend_smart_str.h"
#include "parser.h"
#include "ext/spl/spl_exceptions.h"

#include "lexbor/html/html.h"
#include "lexbor/html/interfaces/element.h"

#include "lexbor/html/interface.h"
#include "lexbor/dom/interfaces/element.h"
#include "lexbor/dom/interfaces/document_type.h"
#include "lexbor/dom/interfaces/character_data.h"
#include "lexbor/dom/interfaces/processing_instruction.h"

/*
 * Methods
 * */

/* HTML5\DOM\EventTarget */
PHP_METHOD(HTML5_DOM_EventTarget, __construct) {
	
}

/* HTML5\DOM\Node */
PHP_METHOD(HTML5_DOM_Node, getRootNode) {
	HTML5_DOM_METHOD_PARAMS(lxb_dom_node_t);
	html5_dom_node_to_zval(lxb_dom_interface_node(self->owner_document), return_value);
}

PHP_METHOD(HTML5_DOM_Node, hasChildNodes) {
	HTML5_DOM_METHOD_PARAMS(lxb_dom_node_t);
	RETURN_BOOL(self->first_child ? 1 : 0);
}

PHP_METHOD(HTML5_DOM_Node, normalize) {
	HTML5_DOM_METHOD_PARAMS(lxb_dom_node_t);
	html5_dom_node_normalize(self);
}

PHP_METHOD(HTML5_DOM_Node, cloneNode) {
	HTML5_DOM_METHOD_PARAMS(lxb_dom_node_t);
	
	zend_bool deep = 0;
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "|b", &deep) == FAILURE)
		WRONG_PARAM_COUNT;
	
	html5_dom_node_to_zval(html5_dom_node_clone(self, deep, NULL), return_value);
}

PHP_METHOD(HTML5_DOM_Node, isEqualNode) {
	
}

PHP_METHOD(HTML5_DOM_Node, isSameNode) {
	HTML5_DOM_METHOD_PARAMS(lxb_dom_node_t);
	
	zval *other_node_obj;
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "O!", &other_node_obj, html5_dom_node_ce) == FAILURE)
		WRONG_PARAM_COUNT;
	
	lxb_dom_node_t *other_node = html5_dom_zval_to_node(other_node_obj);
	RETURN_BOOL(other_node == self);
}

PHP_METHOD(HTML5_DOM_Node, compareDocumentPosition) {
	
}

PHP_METHOD(HTML5_DOM_Node, contains) {
	HTML5_DOM_METHOD_PARAMS(lxb_dom_node_t);
	
	zval *other_node_obj;
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "O!", &other_node_obj, html5_dom_node_ce) == FAILURE)
		WRONG_PARAM_COUNT;
	
	lxb_dom_node_t *other_node = html5_dom_zval_to_node(other_node_obj);
	
	if (!other_node || other_node->owner_document != self->owner_document)
		RETURN_FALSE;
	
	while (other_node) {
		if (other_node == self)
			RETURN_TRUE;
		other_node = other_node->parent;
	}
	
	RETURN_FALSE;
}

PHP_METHOD(HTML5_DOM_Node, insertBefore) {
	HTML5_DOM_METHOD_PARAMS(lxb_dom_node_t);
	
	zval *new_node_obj, *ref_node_obj;
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "OO!", &new_node_obj, html5_dom_node_ce, &ref_node_obj, html5_dom_node_ce) == FAILURE)
		WRONG_PARAM_COUNT;
	
	// The new child element contains the parent.
	// The node before which the new node is to be inserted is not a child of this node.
	
	lxb_dom_node_t *new_node = html5_dom_zval_to_node(new_node_obj);
	lxb_dom_node_t *ref_node = html5_dom_zval_to_node(ref_node_obj);
	
	if (ref_node) {
		lxb_dom_node_insert_before(ref_node, new_node);
	} else {
		lxb_dom_node_insert_child(self, new_node);
	}
	
	html5_dom_node_to_zval(new_node, return_value);
}

PHP_METHOD(HTML5_DOM_Node, appendChild) {
	HTML5_DOM_METHOD_PARAMS(lxb_dom_node_t);
	
	zval *child_node_obj;
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "O", &child_node_obj, html5_dom_node_ce) == FAILURE)
		WRONG_PARAM_COUNT;
	
	lxb_dom_node_t *child_node = html5_dom_zval_to_node(child_node_obj);
	lxb_dom_node_insert_child(self, child_node);
	html5_dom_node_to_zval(child_node, return_value);
}

PHP_METHOD(HTML5_DOM_Node, replaceChild) {
	HTML5_DOM_METHOD_PARAMS(lxb_dom_node_t);
	
	zval *new_node_obj, *old_node_obj;
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "OO", &new_node_obj, html5_dom_node_ce, &old_node_obj, html5_dom_node_ce) == FAILURE)
		WRONG_PARAM_COUNT;
	
	lxb_dom_node_t *new_node = html5_dom_zval_to_node(new_node_obj);
	lxb_dom_node_t *old_node = html5_dom_zval_to_node(old_node_obj);
	
	lxb_dom_node_insert_before(old_node, new_node);
	lxb_dom_node_remove(old_node);
	
	html5_dom_node_to_zval(old_node, return_value);
}

PHP_METHOD(HTML5_DOM_Node, removeChild) {
	HTML5_DOM_METHOD_PARAMS(lxb_dom_node_t);
	
	zval *child_node_obj;
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "O", &child_node_obj, html5_dom_node_ce) == FAILURE)
		WRONG_PARAM_COUNT;
	
	lxb_dom_node_t *child_node = html5_dom_zval_to_node(child_node_obj);
	lxb_dom_node_remove(child_node);
	html5_dom_node_to_zval(child_node, return_value);
}

/* HTML5\DOM\Document */
PHP_METHOD(HTML5_DOM_Document, createElement) {
	
}

PHP_METHOD(HTML5_DOM_Document, createElementNS) {
	
}

PHP_METHOD(HTML5_DOM_Document, createDocumentFragment) {
	
}

PHP_METHOD(HTML5_DOM_Document, createTextNode) {
	
}

PHP_METHOD(HTML5_DOM_Document, createComment) {
	
}

PHP_METHOD(HTML5_DOM_Document, createCDATASection) {
	
}

PHP_METHOD(HTML5_DOM_Document, createProcessingInstruction) {
	
}

PHP_METHOD(HTML5_DOM_Document, importNode) {
	
}

PHP_METHOD(HTML5_DOM_Document, adoptNode) {
	
}

PHP_METHOD(HTML5_DOM_Document, createAttribute) {
	
}

PHP_METHOD(HTML5_DOM_Document, createAttributeNS) {
	
}

/* HTML5\DOM\CharacterData */
PHP_METHOD(HTML5_DOM_CharacterData, substringData) {
	
}

PHP_METHOD(HTML5_DOM_CharacterData, appendData) {
	
}

PHP_METHOD(HTML5_DOM_CharacterData, insertData) {
	
}

PHP_METHOD(HTML5_DOM_CharacterData, deleteData) {
	
}

PHP_METHOD(HTML5_DOM_CharacterData, replaceData) {
	
}

/* HTML5\DOM\Text */
PHP_METHOD(HTML5_DOM_Text, splitText) {
	
}

/* HTML5\DOM\Element */
PHP_METHOD(HTML5_DOM_Element, hasAttributes) {
	
}

PHP_METHOD(HTML5_DOM_Element, getAttributeNames) {
	
}

PHP_METHOD(HTML5_DOM_Element, getAttribute) {
	
}

PHP_METHOD(HTML5_DOM_Element, getAttributeNS) {
	
}

PHP_METHOD(HTML5_DOM_Element, setAttribute) {
	
}

PHP_METHOD(HTML5_DOM_Element, setAttributeNS) {
	
}

PHP_METHOD(HTML5_DOM_Element, removeAttribute) {
	
}

PHP_METHOD(HTML5_DOM_Element, removeAttributeNS) {
	
}

PHP_METHOD(HTML5_DOM_Element, toggleAttribute) {
	
}

PHP_METHOD(HTML5_DOM_Element, toggleAttributeNS) {
	
}

PHP_METHOD(HTML5_DOM_Element, hasAttribute) {
	
}

PHP_METHOD(HTML5_DOM_Element, hasAttributeNS) {
	
}

PHP_METHOD(HTML5_DOM_Element, getAttributeNode) {
	
}

PHP_METHOD(HTML5_DOM_Element, getAttributeNodeNS) {
	
}

PHP_METHOD(HTML5_DOM_Element, setAttributeNode) {
	
}

PHP_METHOD(HTML5_DOM_Element, setAttributeNodeNS) {
	
}

PHP_METHOD(HTML5_DOM_Element, removeAttributeNode) {
	
}

PHP_METHOD(HTML5_DOM_Element, closest) {
	
}

PHP_METHOD(HTML5_DOM_Element, matches) {
	
}

PHP_METHOD(HTML5_DOM_Element, insertAdjacentElement) {
	
}

PHP_METHOD(HTML5_DOM_Element, insertAdjacentText) {
	
}

PHP_METHOD(HTML5_DOM_Element, insertAdjacentHTML) {
	
}

/* HTML5\DOM\NonElementParentNode */
PHP_METHOD(HTML5_DOM_NonElementParentNode, getElementById) {
	
}

/* HTML5\DOM\ParentNode */
PHP_METHOD(HTML5_DOM_ParentNode, getElementsByTagName) {
	
}

PHP_METHOD(HTML5_DOM_ParentNode, getElementsByTagNameNS) {
	
}

PHP_METHOD(HTML5_DOM_ParentNode, getElementsByClassName) {
	
}

PHP_METHOD(HTML5_DOM_ParentNode, prepend) {
	
}

PHP_METHOD(HTML5_DOM_ParentNode, append) {
	
}

PHP_METHOD(HTML5_DOM_ParentNode, querySelector) {
	
}

PHP_METHOD(HTML5_DOM_ParentNode, querySelectorAll) {
	
}

/* HTML5\DOM\ChildNode */
PHP_METHOD(HTML5_DOM_ChildNode, before) {
	
}

PHP_METHOD(HTML5_DOM_ChildNode, after) {
	
}

PHP_METHOD(HTML5_DOM_ChildNode, replaceWith) {
	
}

PHP_METHOD(HTML5_DOM_ChildNode, remove) {
	
}

/* HTML5\DOM\DocumentNonStandart */
PHP_METHOD(HTML5_DOM_DocumentNonStandart, getParseErrors) {
	
}

/*
 * Properties
 * */

/* HTML5\DOM\Node */
int html5_dom_node__nodeType(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_node_t *self = lxb_dom_interface_node(obj->ptr);
	ZVAL_LONG(val, self->type);
	return 1;
}

int html5_dom_node__nodeName(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_node_t *self = lxb_dom_interface_node(obj->ptr);
	size_t str_len = 0;
	const lxb_char_t *str = lxb_dom_node_name(self, &str_len);
	if (str) {
		ZVAL_STRINGL(val, str, str_len);
	} else {
		ZVAL_NULL(val);
	}
	return 1;
}

int html5_dom_node__baseURI(html5_dom_object_wrap_t *obj, zval *val) {
	// TODO: implement
	ZVAL_NULL(val);
	return 1;
}

int html5_dom_node__isConnected(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_node_t *self = lxb_dom_interface_node(obj->ptr);
	ZVAL_BOOL(val, self->parent ? 1 : 0);
	return 1;
}

int html5_dom_node__ownerDocument(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_node_t *self = lxb_dom_interface_node(obj->ptr);
	html5_dom_node_to_zval(lxb_dom_interface_node(self->owner_document), val);
	return 1;
}

int html5_dom_node__parentNode(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_node_t *self = lxb_dom_interface_node(obj->ptr);
	html5_dom_node_to_zval(self->parent, val);
	return 1;
}

int html5_dom_node__parentElement(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_node_t *self = lxb_dom_interface_node(obj->ptr);
	lxb_dom_node_t *parent = self->parent && self->parent->type == LXB_DOM_NODE_TYPE_ELEMENT ? self->parent : NULL;
	html5_dom_node_to_zval(parent, val);
	return 1;
}

int html5_dom_node__childNodes(html5_dom_object_wrap_t *obj, zval *val) {
	return 0;
}

int html5_dom_node__firstChild(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_node_t *self = lxb_dom_interface_node(obj->ptr);
	html5_dom_node_to_zval(self->first_child, val);
	return 1;
}

int html5_dom_node__lastChild(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_node_t *self = lxb_dom_interface_node(obj->ptr);
	html5_dom_node_to_zval(self->last_child, val);
	return 1;
}

int html5_dom_node__previousSibling(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_node_t *self = lxb_dom_interface_node(obj->ptr);
	html5_dom_node_to_zval(self->prev, val);
	return 1;
}

int html5_dom_node__nextSibling(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_node_t *self = lxb_dom_interface_node(obj->ptr);
	html5_dom_node_to_zval(self->next, val);
	return 1;
}

int html5_dom_node__nodeValue(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_node_t *self = lxb_dom_interface_node(obj->ptr);
	switch (self->type) {
		case LXB_DOM_NODE_TYPE_ATTRIBUTE:
		{
			lxb_dom_attr_t *node_attr = lxb_dom_interface_attr(self);
			if (node_attr->value) {
				ZVAL_STRINGL(val, node_attr->value->data, node_attr->value->length);
			} else {
				ZVAL_EMPTY_STRING(val);
			}
		}
		break;
		
		case LXB_DOM_NODE_TYPE_TEXT:
		case LXB_DOM_NODE_TYPE_COMMENT:
		case LXB_DOM_NODE_TYPE_CDATA_SECTION:
		case LXB_DOM_NODE_TYPE_PROCESSING_INSTRUCTION:
		{
			lxb_dom_character_data_t *node_char_data = lxb_dom_interface_character_data(self);
			ZVAL_STRINGL(val, node_char_data->data.data, node_char_data->data.length);
		}
		break;
		
		default:
			ZVAL_NULL(val);
		break;
	}
	return 1;
}

int html5_dom_node__nodeValue_set(html5_dom_object_wrap_t *obj, zval *val) {
	return 0;
}

int html5_dom_node__textContent(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_node_t *self = lxb_dom_interface_node(obj->ptr);
	switch (self->type) {
		case LXB_DOM_NODE_TYPE_ATTRIBUTE:
		case LXB_DOM_NODE_TYPE_TEXT:
		case LXB_DOM_NODE_TYPE_COMMENT:
		case LXB_DOM_NODE_TYPE_CDATA_SECTION:
		case LXB_DOM_NODE_TYPE_PROCESSING_INSTRUCTION:
			return html5_dom_node__nodeValue(obj, val);
		break;
		
		case LXB_DOM_NODE_TYPE_ELEMENT:
		case LXB_DOM_NODE_TYPE_DOCUMENT_FRAGMENT:
		{
			smart_str buf = {0};
			html5_dom_node_text(self, &buf);
			
			if (buf.s) {
				ZSTR_VAL(buf.s)[ZSTR_LEN(buf.s)] = '\0';
				ZVAL_NEW_STR(val, buf.s);
			} else {
				ZVAL_EMPTY_STRING(val);
			}
		}
		break;
		
		default:
			ZVAL_NULL(val);
		break;
	}
	return 1;
}

int html5_dom_node__textContent_set(html5_dom_object_wrap_t *obj, zval *val) {
	return 0;
}

int html5_dom_node__private(html5_dom_object_wrap_t *obj, zval *val) {
	return 0;
}

int html5_dom_node__private_set(html5_dom_object_wrap_t *obj, zval *val) {
	return 0;
}

/* HTML5\DOM\Attr */
int html5_dom_attr__namespaceURI(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_attr_t *self = lxb_dom_interface_attr(obj->ptr);
	lxb_dom_document_t *dom_document = lxb_dom_interface_node(self)->owner_document;
	size_t str_len = 0;
	const lxb_char_t *str = lxb_ns_by_id(dom_document->ns, lxb_dom_interface_node(self)->ns, &str_len);
	if (str) {
		ZVAL_STRINGL(val, str, str_len);
	} else {
		ZVAL_NULL(val);
	}
	return 1;
}

int html5_dom_attr__prefix(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_attr_t *self = lxb_dom_interface_attr(obj->ptr);
	size_t str_len = 0;
	const lxb_char_t *str = lxb_dom_attr_prefix(self, &str_len);
	if (str) {
		ZVAL_STRINGL(val, str, str_len);
	} else {
		ZVAL_NULL(val);
	}
	return 1;
}

int html5_dom_attr__localName(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_attr_t *self = lxb_dom_interface_attr(obj->ptr);
	size_t str_len = 0;
	const lxb_char_t *str = lxb_dom_attr_local_name(self, &str_len);
	if (str) {
		ZVAL_STRINGL(val, str, str_len);
	} else {
		ZVAL_NULL(val);
	}
	return 1;
}

int html5_dom_attr__name(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_attr_t *self = lxb_dom_interface_attr(obj->ptr);
	size_t str_len = 0;
	const lxb_char_t *str = lxb_dom_attr_qualified_name(self, &str_len);
	if (str) {
		ZVAL_STRINGL(val, str, str_len);
	} else {
		ZVAL_NULL(val);
	}
	return 1;
}

int html5_dom_attr__value(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_attr_t *self = lxb_dom_interface_attr(obj->ptr);
	size_t str_len = 0;
	const lxb_char_t *str = lxb_dom_attr_value(self, &str_len);
	if (str) {
		ZVAL_STRINGL(val, str, str_len);
	} else {
		ZVAL_NULL(val);
	}
	return 1;
}

int html5_dom_attr__value_set(html5_dom_object_wrap_t *obj, zval *val) {
	return 0;
}

int html5_dom_attr__ownerElement(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_attr_t *self = lxb_dom_interface_attr(obj->ptr);
	html5_dom_node_to_zval(lxb_dom_interface_node(self->owner), val);
}

/* HTML5\DOM\Document */
int html5_dom_document__URL(html5_dom_object_wrap_t *obj, zval *val) {
	ZVAL_NULL(val);
	return 1;
}

int html5_dom_document__documentURI(html5_dom_object_wrap_t *obj, zval *val) {
	ZVAL_NULL(val);
	return 1;
}

int html5_dom_document__origin(html5_dom_object_wrap_t *obj, zval *val) {
	ZVAL_NULL(val);
	return 1;
}

int html5_dom_document__compatMode(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_document_t *self = lxb_dom_interface_document(obj->ptr);
	if (self->compat_mode == LXB_DOM_DOCUMENT_CMODE_QUIRKS) {
		// if the document is in quirks mode.
		ZVAL_STRINGL(val, "BackCompat", sizeof("BackCompat") - 1);
	} else {
		// if the document is in no-quirks (also known as "standards") mode or limited-quirks (also known as "almost standards") mode.
		ZVAL_STRINGL(val, "CSS1Compat", sizeof("CSS1Compat") - 1);
	}
	return 1;
}

int html5_dom_document__characterSet(html5_dom_object_wrap_t *obj, zval *val) {
	ZVAL_STRINGL(val, "UTF-8", sizeof("UTF-8") - 1);
	return 1;
}

int html5_dom_document__charset(html5_dom_object_wrap_t *obj, zval *val) {
	return html5_dom_document__characterSet(obj, val);
}

int html5_dom_document__inputEncoding(html5_dom_object_wrap_t *obj, zval *val) {
	return html5_dom_document__characterSet(obj, val);
}

int html5_dom_document__contentType(html5_dom_object_wrap_t *obj, zval *val) {
	ZVAL_STRINGL(val, "text/html", sizeof("text/html") - 1);
	return 1;
}

int html5_dom_document__doctype(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_document_t *self = lxb_dom_interface_document(obj->ptr);
	html5_dom_node_to_zval(lxb_dom_interface_node(self->doctype), val);
	return 1;
}

int html5_dom_document__documentElement(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_document_t *self = lxb_dom_interface_document(obj->ptr);
	html5_dom_node_to_zval(lxb_dom_interface_node(self->element), val);
	return 1;
}

/* HTML5\DOM\DocumentType */
int html5_dom_documenttype__name(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_document_type_t *self = lxb_dom_interface_document_type(obj->ptr);
	ZVAL_STRINGL(val, self->name.data, self->name.length);
	return 1;
}

int html5_dom_documenttype__publicId(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_document_type_t *self = lxb_dom_interface_document_type(obj->ptr);
	ZVAL_STRINGL(val, self->public_id.data, self->public_id.length);
	return 1;
}

int html5_dom_documenttype__systemId(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_document_type_t *self = lxb_dom_interface_document_type(obj->ptr);
	ZVAL_STRINGL(val, self->system_id.data, self->system_id.length);
	return 1;
}

/* HTML5\DOM\CharacterData */
int html5_dom_characterdata__data(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_character_data_t *self = lxb_dom_interface_character_data(obj->ptr);
	ZVAL_STRINGL(val, self->data.data, self->data.length);
	return 1;
}

int html5_dom_characterdata__data_set(html5_dom_object_wrap_t *obj, zval *val) {
	return 0;
}

int html5_dom_characterdata__length(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_character_data_t *self = lxb_dom_interface_character_data(obj->ptr);
	ZVAL_LONG(val, self->data.length);
	return 1;
}

/* HTML5\DOM\Text */
int html5_dom_text__wholeText(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_text_t *self = (lxb_dom_text_t *) obj->ptr;
	// Find first whole text node
	lxb_dom_node_t *node = lxb_dom_interface_node(self);
	while (node->prev && node->prev->type == LXB_DOM_NODE_TYPE_TEXT)
		node = node->prev;
	
	// Concat all whole text nodes
	smart_str buf = {0};
	while (node && node->type == LXB_DOM_NODE_TYPE_TEXT) {
		lxb_dom_character_data_t *node_char_data = lxb_dom_interface_character_data(node);
		if (node_char_data->data.length)
			smart_str_appendl(&buf, node_char_data->data.data, node_char_data->data.length);
		node = node->next;
	}
	
	// Return result string
	if (buf.s) {
		ZSTR_VAL(buf.s)[ZSTR_LEN(buf.s)] = '\0';
		ZVAL_NEW_STR(val, buf.s);
	} else {
		ZVAL_EMPTY_STRING(val);
	}
	
	return 1;
}

/* HTML5\DOM\ProcessingInstruction */
int html5_dom_processinginstruction__target(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_processing_instruction_t *self = lxb_dom_interface_processing_instruction(obj->ptr);
	ZVAL_STRINGL(val, self->target.data, self->target.length);
	return 1;
}

/* HTML5\DOM\Element */
int html5_dom_element__namespaceURI(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_element_t *self = lxb_dom_interface_element(obj->ptr);
	lxb_dom_document_t *dom_document = lxb_dom_interface_node(self)->owner_document;
	size_t str_len = 0;
	const lxb_char_t *str = lxb_ns_by_id(dom_document->ns, lxb_dom_interface_node(self)->ns, &str_len);
	if (str) {
		ZVAL_STRINGL(val, str, str_len);
	} else {
		ZVAL_NULL(val);
	}
	return 1;
}

int html5_dom_element__prefix(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_element_t *self = lxb_dom_interface_element(obj->ptr);
	size_t str_len = 0;
	const lxb_char_t *str = lxb_dom_element_prefix(self, &str_len);
	if (str) {
		ZVAL_STRINGL(val, str, str_len);
	} else {
		ZVAL_NULL(val);
	}
	return 1;
}

int html5_dom_element__localName(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_element_t *self = lxb_dom_interface_element(obj->ptr);
	size_t str_len = 0;
	const lxb_char_t *str = lxb_dom_element_local_name(self, &str_len);
	if (str) {
		ZVAL_STRINGL(val, str, str_len);
	} else {
		ZVAL_NULL(val);
	}
	return 1;
}

int html5_dom_element__tagName(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_element_t *self = lxb_dom_interface_element(obj->ptr);
	size_t str_len = 0;
	const lxb_char_t *str = lxb_dom_element_tag_name(self, &str_len);
	if (str) {
		ZVAL_STRINGL(val, str, str_len);
	} else {
		ZVAL_NULL(val);
	}
	return 1;
}

int html5_dom_element__id(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_element_t *self = lxb_dom_interface_element(obj->ptr);
	size_t str_len = 0;
	const lxb_char_t *str = lxb_dom_element_id(self, &str_len);
	if (str) {
		ZVAL_STRINGL(val, str, str_len);
	} else {
		ZVAL_EMPTY_STRING(val);
	}
	return 1;
}

int html5_dom_element__id_set(html5_dom_object_wrap_t *obj, zval *val) {
	return 0;
}

int html5_dom_element__className(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_element_t *self = lxb_dom_interface_element(obj->ptr);
	size_t str_len = 0;
	const lxb_char_t *str = lxb_dom_element_class(self, &str_len);
	if (str) {
		ZVAL_STRINGL(val, str, str_len);
	} else {
		ZVAL_EMPTY_STRING(val);
	}
	return 1;
}

int html5_dom_element__className_set(html5_dom_object_wrap_t *obj, zval *val) {
	return 0;
}

int html5_dom_element__classList(html5_dom_object_wrap_t *obj, zval *val) {
	return 0;
}

int html5_dom_element__attributes(html5_dom_object_wrap_t *obj, zval *val) {
	return 0;
}

int html5_dom_element__innerHTML(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_node_t *self = lxb_dom_interface_node(obj->ptr);
	
	smart_str buf = {0};
	lxb_html_serialize_deep_cb(self, html5_dom_node_serialize_callback, &buf);
	
	if (buf.s) {
		ZSTR_VAL(buf.s)[ZSTR_LEN(buf.s)] = '\0';
		ZVAL_NEW_STR(val, buf.s);
	} else {
		ZVAL_EMPTY_STRING(val);
	}
	return 1;
}

int html5_dom_element__innerHTML_set(html5_dom_object_wrap_t *obj, zval *val) {
	return 0;
}

int html5_dom_element__outerHTML(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_node_t *self = lxb_dom_interface_node(obj->ptr);
	
	smart_str buf = {0};
	lxb_html_serialize_tree_cb(self, html5_dom_node_serialize_callback, &buf);
	
	if (buf.s) {
		ZSTR_VAL(buf.s)[ZSTR_LEN(buf.s)] = '\0';
		ZVAL_NEW_STR(val, buf.s);
	} else {
		ZVAL_EMPTY_STRING(val);
	}
	return 1;
}

int html5_dom_element__outerHTML_set(html5_dom_object_wrap_t *obj, zval *val) {
	return 0;
}

/* HTML5\DOM\ParentNode */
int html5_dom_parentnode__children(html5_dom_object_wrap_t *obj, zval *val) {
	return 0;
}

int html5_dom_parentnode__firstElementChild(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_node_t *self = lxb_dom_interface_node(obj->ptr);
	lxb_dom_node_t *node = self->first_child;
	while (node && node->type != LXB_DOM_NODE_TYPE_ELEMENT)
		node = node->next;
	html5_dom_node_to_zval(node, val);
	return 1;
}

int html5_dom_parentnode__lastElementChild(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_node_t *self = lxb_dom_interface_node(obj->ptr);
	lxb_dom_node_t *node = self->last_child;
	while (node && node->type != LXB_DOM_NODE_TYPE_ELEMENT)
		node = node->prev;
	html5_dom_node_to_zval(node, val);
	return 1;
}

int html5_dom_parentnode__childElementCount(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_node_t *self = lxb_dom_interface_node(obj->ptr);
	zend_long count = 0;
	lxb_dom_node_t *node = self->first_child;
	while (node) {
		if (node->type == LXB_DOM_NODE_TYPE_ELEMENT)
			++count;
		node = node->next;
	}
	ZVAL_LONG(val, count);
	return 1;
}

/* HTML5\DOM\NonDocumentTypeChildNode */
int html5_dom_nondocumenttypechildnode__previousElementSibling(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_node_t *self = lxb_dom_interface_node(obj->ptr);
	lxb_dom_node_t *node = self->next;
	while (node && node->type != LXB_DOM_NODE_TYPE_ELEMENT)
		node = node->next;
	html5_dom_node_to_zval(node, val);
	return 1;
}

int html5_dom_nondocumenttypechildnode__nextElementSibling(html5_dom_object_wrap_t *obj, zval *val) {
	lxb_dom_node_t *self = lxb_dom_interface_node(obj->ptr);
	lxb_dom_node_t *node = self->prev;
	while (node && node->type != LXB_DOM_NODE_TYPE_ELEMENT)
		node = node->prev;
	html5_dom_node_to_zval(node, val);
	return 1;
}

/*
 * Utils
 * */

lxb_status_t html5_dom_node_serialize_callback(const lxb_char_t *data, size_t len, void *ctx) {
	smart_str_appendl((smart_str *) ctx, data, len);
	return LXB_STATUS_OK;
}

void html5_dom_node_text(lxb_dom_node_t *node, smart_str *str) {
	switch (node->type) {
		case LXB_DOM_NODE_TYPE_DOCUMENT:
		case LXB_DOM_NODE_TYPE_ELEMENT:
		case LXB_DOM_NODE_TYPE_DOCUMENT_FRAGMENT:
		{
			lxb_dom_node_t *child = node->first_child;
			while (child) {
				html5_dom_node_text(child, str);
				child = child->next;
			}
		}
		break;
		
		case LXB_DOM_NODE_TYPE_TEXT:
		{
			lxb_dom_character_data_t *node_char_data = lxb_dom_interface_character_data(node);
			if (node_char_data->data.length)
				smart_str_appendl(str, node_char_data->data.data, node_char_data->data.length);
		}
		break;
	}
}

lxb_dom_node_t *html5_dom_node_clone(lxb_dom_node_t *node, bool deep, lxb_dom_document_t *new_document) {
	if (!new_document)
		new_document = node->owner_document;
	
	switch (node->type) {
		case LXB_DOM_NODE_TYPE_ELEMENT:
		{
			lxb_dom_element_t *old_element = lxb_dom_interface_element(node);
			
			// localName
			size_t local_name_len = 0;
			const lxb_char_t *local_name = lxb_dom_element_local_name(old_element, &local_name_len);
			
			// prefix
			size_t prefix_len = 0;
			const lxb_char_t *prefix = lxb_dom_element_prefix(old_element, &prefix_len);
			
			// namespaceURI
			size_t ns_link_len = 0;
			const lxb_char_t *ns_link = lxb_ns_by_id(node->owner_document->ns, node->ns, &ns_link_len);
			
			// Create new element
			lxb_dom_element_t *new_element = lxb_dom_element_create(
				new_document, 
				local_name, local_name_len, 
				ns_link, ns_link_len, 
				prefix, prefix_len, 
				(old_element->is_value ? old_element->is_value->data : NULL), (old_element->is_value ? old_element->is_value->length : 0), 
				true
			);
			
			if (!new_element)
				return NULL;
			
			// Copy all attributes
			lxb_dom_attr_t *attr = old_element->first_attr;
			while (attr) {
				lxb_dom_attr_t *new_attr = lxb_dom_interface_attr(html5_dom_node_clone(lxb_dom_interface_node(attr), false, new_document));
				if (!new_attr)
					return NULL;
				lxb_dom_element_attr_append(new_element, new_attr);
				
				attr = attr->next;
			}
			
			// Copy all child nodes
			if (deep) {
				lxb_dom_node_t *child = node->first_child;
				while (child) {
					lxb_dom_node_t *new_child = html5_dom_node_clone(child, true, new_document);
					if (!new_child)
						return NULL;
					
					lxb_dom_node_insert_child(lxb_dom_interface_node(new_element), new_child);
					
					child = child->next;
				}
			}
			
			return lxb_dom_interface_node(new_element);
		}
		break;
		
		case LXB_DOM_NODE_TYPE_ATTRIBUTE:
		{
			lxb_dom_attr_t *old_attr = lxb_dom_interface_attr(node);
			
			// localName
			size_t local_name_len = 0;
			const lxb_char_t *local_name = lxb_dom_attr_local_name(old_attr, &local_name_len);
			
			// prefix
			size_t prefix_len = 0;
			const lxb_char_t *prefix = lxb_dom_attr_prefix(old_attr, &prefix_len);
			
			// namespaceURI
			size_t ns_link_len = 0;
			const lxb_char_t *ns_link = lxb_ns_by_id(old_attr->node.owner_document->ns, old_attr->node.ns, &ns_link_len);
			
			// Create new attribute
			lxb_dom_attr_t *new_attr = lxb_dom_attr_interface_create(new_document);
			
			if (!new_attr)
				return NULL;
			
			lxb_status_t ret = lxb_dom_attr_set_name_ns(
				new_attr, 
				local_name, local_name_len, 
				ns_link, ns_link_len, 
				prefix, prefix_len, 
				false
			);
			
			if (ret != LXB_STATUS_OK)
				return NULL;
			
			if (old_attr->value)
				lxb_dom_attr_set_value(new_attr, old_attr->value->data, old_attr->value->length);
			
			return lxb_dom_interface_node(new_attr);
		}
		break;
		
		case LXB_DOM_NODE_TYPE_TEXT:
		{
			lxb_dom_character_data_t *old_char_data = lxb_dom_interface_character_data(node);
			lxb_dom_text_t *new_text = lxb_dom_document_create_text_node(
				new_document, 
				old_char_data->data.data, old_char_data->data.length
			);
			return lxb_dom_interface_node(new_text);
		}
		break;
		
		case LXB_DOM_NODE_TYPE_CDATA_SECTION:
		{
			lxb_dom_character_data_t *old_char_data = lxb_dom_interface_character_data(node);
			lxb_dom_cdata_section_t *new_cdata = lxb_dom_document_create_cdata_section(
				new_document, 
				old_char_data->data.data, old_char_data->data.length
			);
			return lxb_dom_interface_node(new_cdata);
		}
		break;
		
		case LXB_DOM_NODE_TYPE_PROCESSING_INSTRUCTION:
		{
			lxb_dom_character_data_t *old_char_data = lxb_dom_interface_character_data(node);
			lxb_dom_processing_instruction_t *old_proc_instr = lxb_dom_interface_processing_instruction(node);
			
			lxb_dom_processing_instruction_t *new_proc_instr = lxb_dom_document_create_processing_instruction(
				new_document, 
				old_proc_instr->target.data, old_proc_instr->target.length, 
				old_char_data->data.data, old_char_data->data.length
			);
			
			return lxb_dom_interface_node(new_proc_instr);
		}
		break;
		
		case LXB_DOM_NODE_TYPE_COMMENT:
		{
			lxb_dom_character_data_t *old_char_data = lxb_dom_interface_character_data(node);
			lxb_dom_comment_t *new_comment = lxb_dom_document_create_comment(
				new_document, 
				old_char_data->data.data, old_char_data->data.length
			);
			return lxb_dom_interface_node(new_comment);
		}
		break;
		
		case LXB_DOM_NODE_TYPE_DOCUMENT:
			// unsupported now
		break;
		
		case LXB_DOM_NODE_TYPE_DOCUMENT_TYPE:
		{
			lxb_dom_document_type_t *old_doctype = lxb_dom_interface_document_type(node);
			
			// Create new doctype
			lxb_dom_document_type_t *new_doctype = lxb_dom_document_type_interface_create(new_document);
			if (!new_doctype)
				return NULL;
			
			if (!lexbor_str_copy(&new_doctype->name, &old_doctype->name, new_doctype->node.owner_document->text))
				return NULL;
			
			if (!lexbor_str_copy(&new_doctype->public_id, &old_doctype->public_id, new_doctype->node.owner_document->text))
				return NULL;
			
			if (!lexbor_str_copy(&new_doctype->system_id, &old_doctype->system_id, new_doctype->node.owner_document->text))
				return NULL;
			
			return lxb_dom_interface_node(new_doctype);
		}
		break;
		
		case LXB_DOM_NODE_TYPE_DOCUMENT_FRAGMENT:
			// unsupported now
		break;
	}
	
	return NULL;
}

bool html5_dom_characterdata_append(lxb_dom_character_data_t *char_data, const char *data, size_t length) {
	if (char_data->data.data == NULL)
		lexbor_str_init(&char_data->data, char_data->node.owner_document->text, length);
	
	if (!char_data->data.data)
		return false;
	
	if (!lexbor_str_append(&char_data->data, char_data->node.owner_document->text, data, length))
		return false;
	
	return true;
}

bool html5_dom_node_normalize(lxb_dom_node_t *node) {
	lxb_dom_character_data_t *first_char_data = NULL;
	lxb_dom_node_t *cursor = node->first_child;
	
	while (cursor) {
		if (cursor->type == LXB_DOM_NODE_TYPE_TEXT) {
			lxb_dom_character_data_t *char_data = lxb_dom_interface_character_data(cursor);
			if (first_char_data) {
				if (char_data->data.length)
					html5_dom_characterdata_append(first_char_data, char_data->data.data, char_data->data.length);
				html5_dom_node_remove(cursor);
			} else {
				first_char_data = char_data;
			}
		} else if (cursor->type == LXB_DOM_NODE_TYPE_ELEMENT) {
			first_char_data = NULL;
			html5_dom_node_normalize(cursor);
		} else {
			first_char_data = NULL;
		}
		cursor = node->next;
	}
	
	return true;
}

void html5_dom_node_remove(lxb_dom_node_t *node) {
	if (node->owner_document) {
		lxb_dom_document_t *dom_document = lxb_dom_interface_document(node->owner_document);
		if (lxb_dom_interface_node(dom_document->element) == node)
			dom_document->element = NULL;
		if (lxb_dom_interface_node(dom_document->doctype) == node)
			dom_document->doctype = NULL;
	}
	lxb_dom_node_remove(node);
}

static void _node_free_handler(html5_dom_object_wrap_t *intern) {
	lxb_dom_node_t *node = intern->ptr;
	node->user = NULL;
	
	// Del ref from document
	html5_dom_document_delref(lxb_dom_interface_document(node->owner_document));
}

void html5_dom_node_to_zval(lxb_dom_node_t *node, zval *retval) {
	if (!node) {
		ZVAL_NULL(retval);
		return;
	}
	
	html5_dom_object_wrap_t *intern = (html5_dom_object_wrap_t *) node->user;
	
	// Reuse exists php object
	if (intern) {
		GC_ADDREF(&intern->std);
		ZVAL_OBJ(retval, &intern->std);
		return;
	}
	
	// Create new php object
	zend_class_entry *ce = html5_dom_node_ce;
	switch (node->type) {
		case LXB_DOM_NODE_TYPE_ELEMENT:
			ce = html5_dom_element_ce;
		break;
		case LXB_DOM_NODE_TYPE_ATTRIBUTE:
			ce = html5_dom_attr_ce;
		break;
		case LXB_DOM_NODE_TYPE_TEXT:
			ce = html5_dom_text_ce;
		break;
		case LXB_DOM_NODE_TYPE_CDATA_SECTION:
			ce = html5_dom_cdatasection_ce;
		break;
		case LXB_DOM_NODE_TYPE_PROCESSING_INSTRUCTION:
			ce = html5_dom_processinginstruction_ce;
		break;
		case LXB_DOM_NODE_TYPE_COMMENT:
			ce = html5_dom_comment_ce;
		break;
		case LXB_DOM_NODE_TYPE_DOCUMENT:
			ce = html5_dom_document_ce;
		break;
		case LXB_DOM_NODE_TYPE_DOCUMENT_TYPE:
			ce = html5_dom_documenttype_ce;
		break;
		case LXB_DOM_NODE_TYPE_DOCUMENT_FRAGMENT:
			ce = html5_dom_documentfragment_ce;
		break;
	}
	
	object_init_ex(retval, ce);
	intern = html5_dom_object_unwrap(Z_OBJ_P(retval));
	intern->free_handler = _node_free_handler;
	
	intern->ptr = node;
	node->user = intern;
	
	// Add ref to document
	html5_dom_document_addref(lxb_dom_interface_document(node->owner_document));
}
