PHP_ARG_ENABLE(html5-dom, for html5-dom, 
	[AS_HELP_STRING([--enable-html5-dom], [enable html5-dom (default is no)])])

if test "${PHP_HTML5_DOM}" != "no"; then
	AC_DEFINE(HAVE_HTML5_DOM, 1, [ ])
	
	PHP_ADD_INCLUDE(src)
	PHP_ADD_INCLUDE(third_party/lexbor/source)
	
	LEXBOR_PORTS=\
		third_party/lexbor/source/lexbor/ports/posix/lexbor/core/perf.c \
		third_party/lexbor/source/lexbor/ports/posix/lexbor/core/fs.c \
		third_party/lexbor/source/lexbor/ports/posix/lexbor/core/memory.c
	
	case $host_alias in
		cygwin* | mingw* | pw32*)
			LEXBOR_PORTS=\
				third_party/lexbor/source/lexbor/ports/windows_nt/lexbor/core/perf.c \
				third_party/lexbor/source/lexbor/ports/windows_nt/lexbor/core/fs.c \
				third_party/lexbor/source/lexbor/ports/windows_nt/lexbor/core/memory.c
	esac
	
	PHP_NEW_EXTENSION(html5_dom, [
		src/html5_dom.c \
		src/utils.c \
		src/interfaces.c \
		src/stub.c \
		src/parser.c \
		\
		third_party/lexbor/source/lexbor/tag/tag.c \
		third_party/lexbor/source/lexbor/utils/http.c \
		third_party/lexbor/source/lexbor/utils/warc.c \
		third_party/lexbor/source/lexbor/encoding/iso_2022_jp_katakana.c \
		third_party/lexbor/source/lexbor/encoding/big5.c \
		third_party/lexbor/source/lexbor/encoding/euc_kr.c \
		third_party/lexbor/source/lexbor/encoding/gb18030.c \
		third_party/lexbor/source/lexbor/encoding/jis0208.c \
		third_party/lexbor/source/lexbor/encoding/single.c \
		third_party/lexbor/source/lexbor/encoding/range.c \
		third_party/lexbor/source/lexbor/encoding/res.c \
		third_party/lexbor/source/lexbor/encoding/encode.c \
		third_party/lexbor/source/lexbor/encoding/decode.c \
		third_party/lexbor/source/lexbor/encoding/jis0212.c \
		third_party/lexbor/source/lexbor/encoding/encoding.c \
		third_party/lexbor/source/lexbor/dom/interfaces/document.c \
		third_party/lexbor/source/lexbor/dom/interfaces/event_target.c \
		third_party/lexbor/source/lexbor/dom/interfaces/document_fragment.c \
		third_party/lexbor/source/lexbor/dom/interfaces/comment.c \
		third_party/lexbor/source/lexbor/dom/interfaces/shadow_root.c \
		third_party/lexbor/source/lexbor/dom/interfaces/element.c \
		third_party/lexbor/source/lexbor/dom/interfaces/character_data.c \
		third_party/lexbor/source/lexbor/dom/interfaces/text.c \
		third_party/lexbor/source/lexbor/dom/interfaces/attr.c \
		third_party/lexbor/source/lexbor/dom/interfaces/processing_instruction.c \
		third_party/lexbor/source/lexbor/dom/interfaces/document_type.c \
		third_party/lexbor/source/lexbor/dom/interfaces/cdata_section.c \
		third_party/lexbor/source/lexbor/dom/interfaces/node.c \
		third_party/lexbor/source/lexbor/dom/exception.c \
		third_party/lexbor/source/lexbor/dom/interface.c \
		third_party/lexbor/source/lexbor/dom/collection.c \
		third_party/lexbor/source/lexbor/ns/ns.c \
		third_party/lexbor/source/lexbor/css/syntax/tokenizer.c \
		third_party/lexbor/source/lexbor/css/syntax/tokenizer/error.c \
		third_party/lexbor/source/lexbor/css/syntax/token.c \
		third_party/lexbor/source/lexbor/css/syntax/consume.c \
		third_party/lexbor/source/lexbor/css/syntax/state.c \
		third_party/lexbor/source/lexbor/html/tokenizer.c \
		third_party/lexbor/source/lexbor/html/tokenizer/state_script.c \
		third_party/lexbor/source/lexbor/html/tokenizer/error.c \
		third_party/lexbor/source/lexbor/html/tokenizer/state_doctype.c \
		third_party/lexbor/source/lexbor/html/tokenizer/state_rawtext.c \
		third_party/lexbor/source/lexbor/html/tokenizer/state_rcdata.c \
		third_party/lexbor/source/lexbor/html/tokenizer/state_comment.c \
		third_party/lexbor/source/lexbor/html/tokenizer/state.c \
		third_party/lexbor/source/lexbor/html/token.c \
		third_party/lexbor/source/lexbor/html/html.c \
		third_party/lexbor/source/lexbor/html/parser_char.c \
		third_party/lexbor/source/lexbor/html/parser_char_ref.c \
		third_party/lexbor/source/lexbor/html/serialize.c \
		third_party/lexbor/source/lexbor/html/in.c \
		third_party/lexbor/source/lexbor/html/token_attr.c \
		third_party/lexbor/source/lexbor/html/tree.c \
		third_party/lexbor/source/lexbor/html/parser.c \
		third_party/lexbor/source/lexbor/html/interfaces/canvas_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/br_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/image_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/object_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/legend_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/param_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/picture_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/slot_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/document.c \
		third_party/lexbor/source/lexbor/html/interfaces/option_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/data_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/body_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/o_list_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/opt_group_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/script_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/table_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/title_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/button_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/output_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/progress_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/element.c \
		third_party/lexbor/source/lexbor/html/interfaces/iframe_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/hr_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/input_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/table_cell_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/div_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/meta_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/pre_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/media_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/link_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/head_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/time_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/area_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/details_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/anchor_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/directory_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/template_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/select_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/menu_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/d_list_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/source_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/span_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/audio_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/paragraph_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/field_set_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/u_list_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/label_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/frame_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/table_section_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/li_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/track_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/quote_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/font_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/table_caption_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/data_list_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/meter_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/video_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/table_row_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/frame_set_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/text_area_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/unknown_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/heading_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/dialog_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/mod_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/style_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/html_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/map_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/base_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/table_col_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/embed_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/window.c \
		third_party/lexbor/source/lexbor/html/interfaces/form_element.c \
		third_party/lexbor/source/lexbor/html/interfaces/marquee_element.c \
		third_party/lexbor/source/lexbor/html/interface.c \
		third_party/lexbor/source/lexbor/html/tree/error.c \
		third_party/lexbor/source/lexbor/html/tree/open_elements.c \
		third_party/lexbor/source/lexbor/html/tree/active_formatting.c \
		third_party/lexbor/source/lexbor/html/tree/insertion_mode/in_row.c \
		third_party/lexbor/source/lexbor/html/tree/insertion_mode/after_head.c \
		third_party/lexbor/source/lexbor/html/tree/insertion_mode/before_html.c \
		third_party/lexbor/source/lexbor/html/tree/insertion_mode/initial.c \
		third_party/lexbor/source/lexbor/html/tree/insertion_mode/in_table_text.c \
		third_party/lexbor/source/lexbor/html/tree/insertion_mode/in_body.c \
		third_party/lexbor/source/lexbor/html/tree/insertion_mode/in_head.c \
		third_party/lexbor/source/lexbor/html/tree/insertion_mode/in_frameset.c \
		third_party/lexbor/source/lexbor/html/tree/insertion_mode/in_table_body.c \
		third_party/lexbor/source/lexbor/html/tree/insertion_mode/in_head_noscript.c \
		third_party/lexbor/source/lexbor/html/tree/insertion_mode/after_frameset.c \
		third_party/lexbor/source/lexbor/html/tree/insertion_mode/before_head.c \
		third_party/lexbor/source/lexbor/html/tree/insertion_mode/after_after_frameset.c \
		third_party/lexbor/source/lexbor/html/tree/insertion_mode/in_caption.c \
		third_party/lexbor/source/lexbor/html/tree/insertion_mode/in_table.c \
		third_party/lexbor/source/lexbor/html/tree/insertion_mode/foreign_content.c \
		third_party/lexbor/source/lexbor/html/tree/insertion_mode/in_select_in_table.c \
		third_party/lexbor/source/lexbor/html/tree/insertion_mode/after_body.c \
		third_party/lexbor/source/lexbor/html/tree/insertion_mode/in_select.c \
		third_party/lexbor/source/lexbor/html/tree/insertion_mode/text.c \
		third_party/lexbor/source/lexbor/html/tree/insertion_mode/in_column_group.c \
		third_party/lexbor/source/lexbor/html/tree/insertion_mode/in_cell.c \
		third_party/lexbor/source/lexbor/html/tree/insertion_mode/in_template.c \
		third_party/lexbor/source/lexbor/html/tree/insertion_mode/after_after_body.c \
		third_party/lexbor/source/lexbor/html/tree/template_insertion.c \
		third_party/lexbor/source/lexbor/html/encoding.c \
		third_party/lexbor/source/lexbor/core/array.c \
		third_party/lexbor/source/lexbor/core/conv.c \
		third_party/lexbor/source/lexbor/core/str.c \
		third_party/lexbor/source/lexbor/core/strtod.c \
		third_party/lexbor/source/lexbor/core/diyfp.c \
		third_party/lexbor/source/lexbor/core/mem.c \
		third_party/lexbor/source/lexbor/core/in.c \
		third_party/lexbor/source/lexbor/core/plog.c \
		third_party/lexbor/source/lexbor/core/avl.c \
		third_party/lexbor/source/lexbor/core/dtoa.c \
		third_party/lexbor/source/lexbor/core/mraw.c \
		third_party/lexbor/source/lexbor/core/utils.c \
		third_party/lexbor/source/lexbor/core/shs.c \
		third_party/lexbor/source/lexbor/core/array_obj.c \
		third_party/lexbor/source/lexbor/core/bst_map.c \
		third_party/lexbor/source/lexbor/core/dobject.c \
		third_party/lexbor/source/lexbor/core/bst.c \
		third_party/lexbor/source/lexbor/core/hash.c \
		${LEXBOR_PORTS} \
	], $ext_shared)
	
	PHP_ADD_LIBRARY(pthread, 1, HTML5_DOM_SHARED_LIBADD)
	PHP_SUBST(HTML5_DOM_SHARED_LIBADD)
fi
