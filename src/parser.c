#include "parser.h"
#include "zend_exceptions.h"

/*
 * Methods
 * */

/* HTML5\DOM */
PHP_METHOD(HTML5_DOM, __construct) {
	HTML5_DOM_METHOD_PARAMS(html5_dom_parser_t);
	
	zval *options_array = NULL;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|a", &options_array) != SUCCESS)
		WRONG_PARAM_COUNT;
	
	html5_dom_options_t options = {0};
	html5_dom_parse_options(&options, options_array);
}

PHP_METHOD(HTML5_DOM, parse) {
	
}

PHP_METHOD(HTML5_DOM, parseChunkStart) {
	
}

PHP_METHOD(HTML5_DOM, parseAsync) {
	
}

PHP_METHOD(HTML5_DOM, parseAsyncChunkStart) {
	
}

/* HTML5\DOM\AsyncResult */
PHP_METHOD(HTML5_DOM_AsyncResult, __construct) {
	
}

PHP_METHOD(HTML5_DOM_AsyncResult, fd) {
	
}

PHP_METHOD(HTML5_DOM_AsyncResult, wait) {
	
}

/* HTML5\DOM\ChunksParser */
PHP_METHOD(HTML5_DOM_ChunksParser, __construct) {
	
}

PHP_METHOD(HTML5_DOM_ChunksParser, parseChunk) {
	
}

PHP_METHOD(HTML5_DOM_ChunksParser, parseChunkEnd) {
	
}

/* HTML5\DOM\ChunksParserAsync */
PHP_METHOD(HTML5_DOM_ChunksParserAsync, __construct) {
	
}

PHP_METHOD(HTML5_DOM_ChunksParserAsync, parseChunk) {
	
}

PHP_METHOD(HTML5_DOM_ChunksParserAsync, parseChunkEnd) {
	
}

/*
 * Properties
 * */

/* HTML5\DOM\AsyncResult */
int html5_dom_asyncresult__done(html5_dom_object_wrap *obj, zval *val, int write, int debug) {
	return 0;
}

/* HTML5\DOM\ChunksParser */
int html5_dom_chunksparser__document(html5_dom_object_wrap *obj, zval *val, int write, int debug) {
	return 0;
}

/*
 * Utils
 * */

static bool html5_dom_parse_opt_long(zval *options_array, const char *key, size_t key_len, long *result) {
	if (options_array) {
		zval *tmp = zend_hash_str_find(Z_ARRVAL_P(options_array), key, key_len);
		if (tmp) {
			convert_to_long(tmp);
			
			if (Z_TYPE_P(tmp) != IS_LONG) {
				zend_throw_exception_ex(html5_dom_domexception_ce, 
					HTML5_DOM_DOMException__VALIDATION_ERR, "Invalid '%s' value.", key);
				return false;
			}
			
			*result = Z_LVAL_P(tmp);
		}
	}
	return true;
}

static bool html5_dom_parse_opt_bool(zval *options_array, const char *key, size_t key_len, bool *result) {
	long value = *result ? 1 : 0;
	bool status = html5_dom_parse_opt_long(options_array, key, key_len, &value);
	*result = value != 0;
	return status;
}

static bool html5_dom_parse_opt_encoding(zval *options_array, const char *key, size_t key_len, const lxb_encoding_data_t **result, bool *is_auto) {
	if (options_array) {
		zval *tmp = zend_hash_str_find(Z_ARRVAL_P(options_array), key, key_len);
		if (tmp) {
			convert_to_string(tmp);
			
			if (Z_TYPE_P(tmp) != IS_STRING) {
				zend_throw_exception_ex(html5_dom_domexception_ce, 
					HTML5_DOM_DOMException__VALIDATION_ERR, "Invalid '%s' value.", key);
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
					zend_throw_exception_ex(html5_dom_domexception_ce, 
						HTML5_DOM_DOMException__VALIDATION_ERR, "Invalid '%s' value: encoding '%s' not found.", key, enc_str);
					return false;
				}
			}
		}
	}
	
	return true;
}

static bool html5_dom_init_options(html5_dom_options_t *options) {
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
