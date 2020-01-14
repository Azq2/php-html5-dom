#ifndef HTML5_DOM_PARSER_H
#define HTML5_DOM_PARSER_H

#include "php.h"

#include "utils.h"
#include "interfaces.h"
#include "lexbor/encoding/encoding.h"

typedef struct {
	bool scripts;
	bool encoding_auto_detect;
	const lxb_encoding_data_t *encoding;
	const lxb_encoding_data_t *encoding_default;
	size_t encoding_prescan_limit;
} html5_dom_options_t;

typedef struct {
	html5_dom_options_t options;
} html5_dom_parser_t;

static bool html5_dom_parse_opt_long(zval *options, const char *key, size_t key_len, long *result);
static bool html5_dom_parse_opt_bool(zval *options, const char *key, size_t key_len, bool *result);
static bool html5_dom_parse_opt_encoding(zval *options, const char *key, size_t key_len, const lxb_encoding_data_t **result, bool *is_auto);

static void html5_dom_init_options(html5_dom_options_t *options);
static bool html5_dom_parse_options(html5_dom_options_t *opts, zval *options);

#endif // HTML5_DOM_PARSER_H
