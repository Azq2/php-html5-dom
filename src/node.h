#ifndef HTML5_DOM_NODE_H
#define HTML5_DOM_NODE_H

#include "port.h"
#include "interfaces.h"
#include "lexbor/dom/interfaces/node.h"

void html5_dom_node_to_zval(lxb_dom_node_t *node, zval *retval);
bool html5_dom_node_normalize(lxb_dom_node_t *node);
void html5_dom_node_remove(lxb_dom_node_t *node, bool can_destroy);
lxb_dom_node_t *html5_dom_node_clone(lxb_dom_node_t *node, bool deep, bool adopt, lxb_dom_document_t *new_document);
lxb_status_t html5_dom_node_serialize_callback(const lxb_char_t *data, size_t len, void *ctx);
void html5_dom_node_text(lxb_dom_node_t *node, smart_str *str);
void html5_dom_node_replace_intern(lxb_dom_node_t *old_node, lxb_dom_node_t *new_node);

static inline lxb_dom_node_t *html5_dom_node_adopt(lxb_dom_node_t *node, lxb_dom_document_t *new_document) {
	if (node && node->owner_document != new_document)
		return html5_dom_node_clone(node, true, true, new_document);
	return node;
}

static inline lxb_dom_node_t *html5_dom_zval_to_node(zval *obj, lxb_dom_document_t *new_document) {
	if (obj) {
		html5_dom_object_wrap_t *intern = html5_dom_object_unwrap(Z_OBJ_P(obj));
		if (new_document) {
			return html5_dom_node_adopt(lxb_dom_interface_node(intern->ptr), new_document);
		} else {
			return lxb_dom_interface_node(intern->ptr);
		}
	}
	return NULL;
}

#endif // HTML5_DOM_NODE_H
