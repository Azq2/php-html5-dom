#ifndef HTML5_DOM_NODE_H
#define HTML5_DOM_NODE_H

#include "port.h"
#include "interfaces.h"
#include "lexbor/dom/interfaces/node.h"

void html5_dom_node_to_zval(lxb_dom_node_t *node, zval *retval);
bool html5_dom_node_normalize(lxb_dom_node_t *node);
void html5_dom_node_remove(lxb_dom_node_t *node);

static inline lxb_dom_node_t *html5_dom_zval_to_node(zval *obj) {
	if (obj) {
		html5_dom_object_wrap_t *intern = html5_dom_object_unwrap(Z_OBJ_P(obj));
		return lxb_dom_interface_node(intern->ptr);
	}
	return NULL;
}

#endif // HTML5_DOM_NODE_H
