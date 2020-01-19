#include "parser.h"
#include "node.h"
#include "zend_exceptions.h"
#include "ext/spl/spl_exceptions.h"
#include "lexbor/html/html.h"
#include "lexbor/html/interface.h"

/*
 * Methods
 * */

/* HTML5\DOM */
PHP_METHOD(HTML5_DOM, parse) {
	zval *options_array = NULL;
	zend_string *html;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "S|a", &html, &options_array) != SUCCESS)
		RETURN_FALSE;
	
	html5_dom_t *dom = (html5_dom_t *) emalloc(sizeof(html5_dom_t));
	dom->refcount = 0;
	
	// Parser options
	html5_dom_init_options(&dom->options);
	if (!html5_dom_parse_options(&dom->options, options_array)) {
		efree(dom);
		RETURN_FALSE;
	}
	
	lxb_status_t status;
	lxb_html_document_t *document = lxb_html_document_create();
	
	status = lxb_html_document_parse(document, html->val, html->len);
	if (status != LXB_STATUS_OK) {
		lxb_html_document_destroy(document);
		efree(dom);
		RETURN_FALSE;
	}
	
	lxb_dom_document_t *dom_document = lxb_dom_interface_document(document);
	dom_document->user = dom;
	
	html5_dom_node_to_zval(lxb_dom_interface_node(document), return_value);
}

/* HTML5\DOM\Parser */
PHP_METHOD(HTML5_DOM_Parser, __construct) {
	// HTML5_DOM_METHOD_PARAMS(html5_dom_parser_t);
	
	zval *options_array = NULL;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|a", &options_array) != SUCCESS)
		WRONG_PARAM_COUNT;
	
	html5_dom_options_t options = {0};
	html5_dom_parse_options(&options, options_array);
}
PHP_METHOD(HTML5_DOM_Parser, parse) {
	
}

/* HTML5\DOM\StreamParser */
PHP_METHOD(HTML5_DOM_StreamParser, __construct) {
	
}
PHP_METHOD(HTML5_DOM_StreamParser, begin) {
	
}
PHP_METHOD(HTML5_DOM_StreamParser, parse) {
	
}
PHP_METHOD(HTML5_DOM_StreamParser, end) {
	
}

/*
 * Utils
 * */

size_t html5_dom_document_addref(lxb_dom_document_t *dom_document) {
	html5_dom_t *dom = (html5_dom_t *) dom_document->user;
	++dom->refcount;
	
	DOM_GC_TRACE("[++] DOM TREE (refcount=%ld)\n", dom->refcount);
	
	return dom->refcount;
}

size_t html5_dom_document_delref(lxb_dom_document_t *dom_document) {
	html5_dom_t *dom = (html5_dom_t *) dom_document->user;
	--dom->refcount;
	
	DOM_GC_TRACE("[--] DOM TREE (refcount=%ld)\n", dom->refcount);
	
	// Destroy lexbor document
	if (dom->refcount == 0) {
		DOM_GC_TRACE("[FREE] DOM\n");
		lxb_html_document_destroy(lxb_html_interface_document(dom_document));
	}
	
	return dom->refcount;
}

static bool html5_dom_parse_opt_long(zval *options_array, const char *key, size_t key_len, long *result) {
	if (options_array) {
		zval *tmp = zend_hash_str_find(Z_ARRVAL_P(options_array), key, key_len);
		if (tmp) {
			convert_to_long(tmp);
			
			if (Z_TYPE_P(tmp) != IS_LONG) {
				zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0, "Invalid '%s' value.", key);
				return false;
			}
			
			*result = Z_LVAL_P(tmp);
		}
	}
	return true;
}

static bool html5_dom_parse_opt_bool(zval *options_array, const char *key, size_t key_len, bool *result) {
	if (options_array) {
		zval *tmp = zend_hash_str_find(Z_ARRVAL_P(options_array), key, key_len);
		if (tmp) {
			convert_to_boolean(tmp);
			
			if (Z_TYPE_P(tmp) != _IS_BOOL && Z_TYPE_P(tmp) != IS_FALSE && Z_TYPE_P(tmp) != IS_TRUE) {
				zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0, "Invalid '%s' value.", key);
				return false;
			}
			
			*result = zval_is_true(tmp);
		}
	}
	return true;
}

static bool html5_dom_parse_opt_encoding(zval *options_array, const char *key, size_t key_len, const lxb_encoding_data_t **result, bool *is_auto) {
	if (options_array) {
		zval *tmp = zend_hash_str_find(Z_ARRVAL_P(options_array), key, key_len);
		if (tmp) {
			convert_to_string(tmp);
			
			if (Z_TYPE_P(tmp) != IS_STRING) {
				zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0, "Invalid '%s' value.", key);
				return false;
			}
			
			size_t enc_length = Z_STRLEN_P(tmp);
			const char *enc_str = Z_STRVAL_P(tmp);
			
			if (is_auto)
				*is_auto = false;
			
			if (enc_length == 4 && strcasecmp(enc_str, "auto") == 0) {
				*result = NULL;
				
				if (is_auto)
					*is_auto = true;
			} else {
				*result = lxb_encoding_data_by_pre_name(enc_str, enc_length);
				
				if (!*result) {
					zend_throw_exception_ex(spl_ce_InvalidArgumentException, 0, "Invalid '%s' value: encoding '%s' not found.", key, enc_str);
					return false;
				}
			}
		}
	}
	
	return true;
}

static void html5_dom_init_options(html5_dom_options_t *options) {
	options->scripts					= true;
	options->encoding_prescan_limit		= 1024;
	options->encoding_auto_detect		= true;
	options->encoding					= NULL;
	options->encoding_default			= lxb_encoding_data_by_pre_name(ZEND_STRS("UTF-8") - 1);
}

static bool html5_dom_parse_options(html5_dom_options_t *options, zval *options_array) {
	// Enable <script>
	if (!html5_dom_parse_opt_bool(options_array, ZEND_STRS("scripts") - 1, &options->scripts))
		return false;
	
	// Encoding prescan size
	if (!html5_dom_parse_opt_long(options_array, ZEND_STRS("encoding_prescan_limit") - 1, &options->encoding_prescan_limit))
		return false;
	
	// Encoding
	if (!html5_dom_parse_opt_encoding(options_array, ZEND_STRS("encoding") - 1, &options->encoding, &options->encoding_auto_detect))
		return false;
	
	// Default encoding
	if (!html5_dom_parse_opt_encoding(options_array, ZEND_STRS("encoding_default") - 1, &options->encoding_default, NULL))
		return false;
	
	return true;
}
