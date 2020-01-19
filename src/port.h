#ifndef HTML5_DOM_PORT_H
#define HTML5_DOM_PORT_H

#include "php.h"

#if PHP_VERSION_ID < 70300
	#define GC_ADDREF(v) (++GC_REFCOUNT(v))
	#define GC_DELREF(v) (GC_REFCOUNT(v)--)
#endif

#endif // HTML5_DOM_PORT_H
