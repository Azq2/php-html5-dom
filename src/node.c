#include "node.h"
#include "zend_exceptions.h"
#include "parser.h"
#include "ext/spl/spl_exceptions.h"
#include "lexbor/html/html.h"
#include "lexbor/html/interface.h"

/*
 * Methods
 * */

/* HTML5\DOM\EventTarget */
PHP_METHOD(HTML5_DOM_EventTarget, __construct) {
	
}

/* HTML5\DOM\Node */
PHP_METHOD(HTML5_DOM_Node, getRootNode) {
	
}
PHP_METHOD(HTML5_DOM_Node, hasChildNodes) {
	
}
PHP_METHOD(HTML5_DOM_Node, normalize) {
	
}
PHP_METHOD(HTML5_DOM_Node, cloneNode) {
	
}
PHP_METHOD(HTML5_DOM_Node, isEqualNode) {
	
}
PHP_METHOD(HTML5_DOM_Node, isSameNode) {
	
}
PHP_METHOD(HTML5_DOM_Node, compareDocumentPosition) {
	
}
PHP_METHOD(HTML5_DOM_Node, contains) {
	
}
PHP_METHOD(HTML5_DOM_Node, insertBefore) {
	
}
PHP_METHOD(HTML5_DOM_Node, appendChild) {
	
}
PHP_METHOD(HTML5_DOM_Node, replaceChild) {
	
}
PHP_METHOD(HTML5_DOM_Node, removeChild) {
	
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
int html5_dom_node__nodeType(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}
int html5_dom_node__nodeName(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}
int html5_dom_node__baseURI(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}
int html5_dom_node__isConnected(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	lxb_dom_node_t *self = (lxb_dom_node_t *) obj->ptr;
	if (!write) {
		ZVAL_BOOL(val, self->parent ? 1 : 0);
		return 1;
	}
	return 0;
}
int html5_dom_node__ownerDocument(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	lxb_dom_node_t *self = (lxb_dom_node_t *) obj->ptr;
	if (!write) {
		html5_dom_node_to_zval(lxb_dom_interface_node(self->owner_document), val);
		return 1;
	}
	return 0;
}
int html5_dom_node__parentNode(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	lxb_dom_node_t *self = (lxb_dom_node_t *) obj->ptr;
	if (!write) {
		html5_dom_node_to_zval(self->parent, val);
		return 1;
	}
	return 0;
}
int html5_dom_node__parentElement(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	lxb_dom_node_t *self = (lxb_dom_node_t *) obj->ptr;
	if (!write) {
		lxb_dom_node_t *parent = self->parent && self->parent->type == LXB_DOM_NODE_TYPE_ELEMENT ? self->parent : NULL;
		html5_dom_node_to_zval(parent, val);
		return 1;
	}
	return 0;
}
int html5_dom_node__childNodes(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}
int html5_dom_node__firstChild(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	lxb_dom_node_t *self = (lxb_dom_node_t *) obj->ptr;
	if (!write) {
		html5_dom_node_to_zval(self->first_child, val);
		return 1;
	}
	return 0;
}
int html5_dom_node__lastChild(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	lxb_dom_node_t *self = (lxb_dom_node_t *) obj->ptr;
	if (!write) {
		html5_dom_node_to_zval(self->last_child, val);
		return 1;
	}
	return 0;
}
int html5_dom_node__previousSibling(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	lxb_dom_node_t *self = (lxb_dom_node_t *) obj->ptr;
	if (!write) {
		html5_dom_node_to_zval(self->prev, val);
		return 1;
	}
	return 0;
}
int html5_dom_node__nextSibling(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	lxb_dom_node_t *self = (lxb_dom_node_t *) obj->ptr;
	if (!write) {
		html5_dom_node_to_zval(self->next, val);
		return 1;
	}
	return 0;
}
int html5_dom_node__nodeValue(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}
int html5_dom_node__textContent(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}
int html5_dom_node__private(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}

/* HTML5\DOM\Attr */
int html5_dom_attr__namespaceURI(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}
int html5_dom_attr__prefix(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}
int html5_dom_attr__localName(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}
int html5_dom_attr__name(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}
int html5_dom_attr__value(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}
int html5_dom_attr__ownerElement(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}

/* HTML5\DOM\Document */
int html5_dom_document__URL(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}
int html5_dom_document__documentURI(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}
int html5_dom_document__origin(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}
int html5_dom_document__compatMode(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}
int html5_dom_document__characterSet(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}
int html5_dom_document__charset(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}
int html5_dom_document__inputEncoding(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}
int html5_dom_document__contentType(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}
int html5_dom_document__doctype(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	lxb_dom_document_t *self = (lxb_dom_document_t *) obj->ptr;
	if (!write) {
		html5_dom_node_to_zval(lxb_dom_interface_node(self->doctype), val);
		return 1;
	}
	return 0;
}
int html5_dom_document__documentElement(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	lxb_dom_document_t *self = (lxb_dom_document_t *) obj->ptr;
	if (!write) {
		html5_dom_node_to_zval(lxb_dom_interface_node(self->element), val);
		return 1;
	}
	return 0;
}

/* HTML5\DOM\DocumentType */
int html5_dom_documenttype__name(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}
int html5_dom_documenttype__publicId(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}
int html5_dom_documenttype__systemId(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}

/* HTML5\DOM\CharacterData */
int html5_dom_characterdata__data(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}
int html5_dom_characterdata__length(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}

/* HTML5\DOM\Text */
int html5_dom_text__wholeText(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}

/* HTML5\DOM\ProcessingInstruction */
int html5_dom_processinginstruction__target(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}

/* HTML5\DOM\Element */
int html5_dom_element__namespaceURI(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}
int html5_dom_element__prefix(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}
int html5_dom_element__localName(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}
int html5_dom_element__tagName(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}
int html5_dom_element__id(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}
int html5_dom_element__className(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}
int html5_dom_element__classList(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}
int html5_dom_element__attributes(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}
int html5_dom_element__innerHTML(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}
int html5_dom_element__outerHTML(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}

/* HTML5\DOM\ParentNode */
int html5_dom_parentnode__children(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}
int html5_dom_parentnode__firstElementChild(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}
int html5_dom_parentnode__lastElementChild(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}
int html5_dom_parentnode__childElementCount(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}

/* HTML5\DOM\NonDocumentTypeChildNode */
int html5_dom_nondocumenttypechildnode__previousElementSibling(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}
int html5_dom_nondocumenttypechildnode__nextElementSibling(html5_dom_object_wrap_t *obj, zval *val, int write, int debug) {
	return 0;
}

/*
 * Utils
 * */

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
	
	// If Node already have PHP representation - increment ref count
	if (intern) {
		GC_ADDREF(&intern->std);
		ZVAL_OBJ(retval, &intern->std);
		return;
	}
	
	// Create new Node representation in PHP
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
