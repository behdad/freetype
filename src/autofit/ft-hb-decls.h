/*
 * Permission is hereby granted, without written agreement and without
 * license or royalty fees, to use, copy, modify, and distribute this
 * software and its documentation for any purpose, provided that the
 * above copyright notice and the following two paragraphs appear in
 * all copies of this software.
 *
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES
 * ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN
 * IF THE COPYRIGHT HOLDER HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 * THE COPYRIGHT HOLDER SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING,
 * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE COPYRIGHT HOLDER HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 *
 * Author(s): Behdad Esfahbod
 */

#ifndef FT_HB_DECLS_H
#define FT_HB_DECLS_H

typedef hb_blob_t* (*ft_hb_blob_create_func_t)(
  const char* data,
  unsigned int length,
  hb_memory_mode_t mode,
  void* user_data,
  hb_destroy_func_t destroy
);

typedef void (*ft_hb_blob_destroy_func_t)(
  hb_blob_t* blob
);

typedef void (*ft_hb_buffer_add_utf8_func_t)(
  hb_buffer_t* buffer,
  const char* text,
  int text_length,
  unsigned int item_offset,
  int item_length
);

typedef void (*ft_hb_buffer_clear_contents_func_t)(
  hb_buffer_t* buffer
);

typedef hb_buffer_t* (*ft_hb_buffer_create_func_t)(void);

typedef void (*ft_hb_buffer_destroy_func_t)(
  hb_buffer_t* buffer
);

typedef hb_glyph_info_t* (*ft_hb_buffer_get_glyph_infos_func_t)(
  hb_buffer_t* buffer,
  unsigned int* length
);

typedef hb_glyph_position_t* (*ft_hb_buffer_get_glyph_positions_func_t)(
  hb_buffer_t* buffer,
  unsigned int* length
);

typedef unsigned int (*ft_hb_buffer_get_length_func_t)(
  hb_buffer_t* buffer
);

typedef void (*ft_hb_buffer_guess_segment_properties_func_t)(
  hb_buffer_t* buffer
);

typedef hb_face_t* (*ft_hb_face_create_func_t)(
  hb_blob_t* blob,
  unsigned int index
);

typedef hb_face_t* (*ft_hb_face_create_for_tables_func_t)(
  hb_reference_table_func_t reference_table_func,
  void* user_data,
  hb_destroy_func_t destroy
);

typedef void (*ft_hb_face_destroy_func_t)(
  hb_face_t* face
);

typedef void (*ft_hb_face_set_index_func_t)(
  hb_face_t* face,
  unsigned int index
);

typedef void (*ft_hb_face_set_upem_func_t)(
  hb_face_t* face,
  unsigned int upem
);

typedef hb_font_t* (*ft_hb_font_create_func_t)(
  hb_face_t* face
);

typedef void (*ft_hb_font_destroy_func_t)(
  hb_font_t* font
);

typedef hb_face_t* (*ft_hb_font_get_face_func_t)(
  hb_font_t* font
);

typedef void (*ft_hb_font_set_scale_func_t)(
  hb_font_t* font,
  int x_scale,
  int y_scale
);

typedef void (*ft_hb_ot_layout_collect_lookups_func_t)(
  hb_face_t* face,
  hb_tag_t table_tag,
  const hb_tag_t* scripts,
  const hb_tag_t* languages,
  const hb_tag_t* features,
  hb_set_t* lookup_indexes
);

typedef void (*ft_hb_ot_layout_lookup_collect_glyphs_func_t)(
  hb_face_t* face,
  hb_tag_t table_tag,
  unsigned int lookup_index,
  hb_set_t* input_glyphs,
  hb_set_t* output_glyphs,
  hb_set_t* lookups_before,
  hb_set_t* lookups_after
);

typedef hb_bool_t (*ft_hb_ot_layout_lookup_would_substitute_func_t)(
  hb_face_t* face,
  unsigned int lookup_index,
  const hb_codepoint_t* glyphs,
  unsigned int glyph_count,
  hb_bool_t zero_context
);

typedef void (*ft_hb_ot_tags_from_script_and_language_func_t)(
  hb_tag_t script,
  hb_tag_t language,
  unsigned int* script_count,
  hb_tag_t* script_tags,
  hb_tag_t* language_tags,
  hb_tag_t* feature_tags
);

typedef hb_set_t* (*ft_hb_set_create_func_t)(void);

typedef void (*ft_hb_set_destroy_func_t)(
  hb_set_t* set
);

typedef hb_bool_t (*ft_hb_set_is_empty_func_t)(
  const hb_set_t* set
);

typedef hb_bool_t (*ft_hb_set_next_func_t)(
  const hb_set_t* set,
  hb_codepoint_t* codepoint
);

typedef void (*ft_hb_set_subtract_func_t)(
  hb_set_t* set,
  const hb_set_t* other
);

typedef void (*ft_hb_shape_func_t)(
  hb_font_t* font,
  hb_buffer_t* buffer,
  const hb_feature_t* features,
  unsigned int num_features
);

typedef hb_bool_t (*ft_hb_version_atleast_func_t)(
  unsigned int major,
  unsigned int minor,
  unsigned int micro
);

#endif /* FT_HB_DECLS_H */
