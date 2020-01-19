#ifndef HTML5_DOM_NODE_H
#define HTML5_DOM_NODE_H

#include "port.h"
#include "interfaces.h"
#include "lexbor/dom/interfaces/node.h"

void html5_dom_node_to_zval(lxb_dom_node_t *node, zval *retval);

#endif // HTML5_DOM_NODE_H
