#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "ext/standard/info.h"

#include <php7/utils.h>
#include <php7/html5_dom.h>
#include <php7/interfaces.h>

#include <lexbor/core/base.h>

const zend_function_entry html5_dom_functions[] = {
	PHP_FE_END
};

static PHP_MINFO_FUNCTION(html5_dom);
static PHP_MINIT_FUNCTION(html5_dom);
static PHP_MSHUTDOWN_FUNCTION(html5_dom);
static PHP_GINIT_FUNCTION(html5_dom);
static PHP_GSHUTDOWN_FUNCTION(html5_dom);
static PHP_RINIT_FUNCTION(html5_dom);

ZEND_DECLARE_MODULE_GLOBALS(html5_dom)

zend_module_entry html5_dom_module_entry = {
	STANDARD_MODULE_HEADER,
	"html5_dom",
	html5_dom_functions,
	PHP_MINIT(html5_dom), PHP_MSHUTDOWN(html5_dom),
	PHP_RINIT(html5_dom), NULL,
	PHP_MINFO(html5_dom),
	PHP_HTML5_DOM_VERSION,
	PHP_MODULE_GLOBALS(html5_dom),
	PHP_GINIT(html5_dom),
	PHP_GSHUTDOWN(html5_dom),
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};

#ifdef COMPILE_DL_HTML5_DOM
	#ifdef ZTS
		ZEND_TSRMLS_CACHE_DEFINE()
	#endif
	ZEND_GET_MODULE(html5_dom)
#endif

static PHP_GINIT_FUNCTION(html5_dom) {
	// nothing todo
}

static PHP_GSHUTDOWN_FUNCTION(html5_dom) {
	// nothing todo
}

static PHP_MINIT_FUNCTION(html5_dom) {
	html5_dom_interfaces_init();
	return SUCCESS;
}

static PHP_MSHUTDOWN_FUNCTION(html5_dom) {
	html5_dom_interfaces_unload();
	return SUCCESS;
}

static PHP_RINIT_FUNCTION(html5_dom) {
#if defined(ZTS) && defined(COMPILE_DL_HTML5_DOM)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}

static PHP_MINFO_FUNCTION(html5_dom) {
	php_info_print_table_start();
	php_info_print_table_header(2, "HTML5 DOM", "enabled");
	php_info_print_table_header(2, "HTML5 DOM version", PHP_HTML5_DOM_VERSION);
	php_info_print_table_header(2, "lexbor version", LEXBOR_VERSION_STRING);
	php_info_print_table_end();
}
