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

#ifndef FT_HB_H
#define FT_HB_H

#include <freetype/internal/compiler-macros.h>
#include <freetype/freetype.h>

#if defined (_AIX)
#  include <sys/inttypes.h>
#elif defined (_MSC_VER) && _MSC_VER < 1600
/* VS 2010 (_MSC_VER 1600) has stdint.h   */
typedef __int8 int8_t;
typedef unsigned __int8 uint8_t;
typedef __int16 int16_t;
typedef unsigned __int16 uint16_t;
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#elif defined (_MSC_VER) && _MSC_VER < 1800
/* VS 2013 (_MSC_VER 1800) has inttypes.h */
#  include <stdint.h>
#else
#  include <inttypes.h>
#endif
#include <stddef.h>


FT_BEGIN_HEADER

typedef int hb_bool_t;
typedef uint32_t hb_codepoint_t;
#define HB_CODEPOINT_INVALID ((hb_codepoint_t) -1)
typedef uint32_t hb_tag_t;
#define HB_TAG(c1,c2,c3,c4) ((hb_tag_t)((((uint32_t)(c1)&0xFF)<<24)|(((uint32_t)(c2)&0xFF)<<16)|(((uint32_t)(c3)&0xFF)<<8)|((uint32_t)(c4)&0xFF)))
#define HB_TAG_NONE HB_TAG(0,0,0,0)
#define HB_TAG_MAX_SIGNED HB_TAG(0x7f,0xff,0xff,0xff)
#define HB_OT_TAG_DEFAULT_SCRIPT HB_TAG ('D', 'F', 'L', 'T')
#define HB_OT_TAG_GPOS HB_TAG('G','P','O','S')
#define HB_OT_TAG_GSUB HB_TAG('G','S','U','B')
typedef int32_t hb_position_t;
typedef uint32_t hb_mask_t;
typedef enum {
  HB_DIRECTION_INVALID = 0,
  HB_DIRECTION_LTR = 4,
  HB_DIRECTION_RTL,
  HB_DIRECTION_TTB,
  HB_DIRECTION_BTT
} hb_direction_t;
typedef enum {
  HB_MEMORY_MODE_DUPLICATE,
  HB_MEMORY_MODE_READONLY,
  HB_MEMORY_MODE_WRITABLE,
  HB_MEMORY_MODE_READONLY_MAY_MAKE_WRITABLE
} hb_memory_mode_t;
#define HB_NO_SINGLE_HEADER_ERROR
#include "hb-script-list.h"
#undef HB_NO_SINGLE_HEADER_ERROR
typedef const struct hb_language_impl_t *hb_language_t;
#define HB_LANGUAGE_INVALID ((hb_language_t) 0)
#define HB_SET_VALUE_INVALID HB_CODEPOINT_INVALID
typedef struct hb_feature_t {
  hb_tag_t      tag;
  uint32_t      value;
  unsigned int  start;
  unsigned int  end;
} hb_feature_t;
typedef struct hb_glyph_info_t {
  hb_codepoint_t codepoint;
  hb_mask_t      mask;
  uint32_t       cluster;
  uint32_t       var1;
  uint32_t       var2;
} hb_glyph_info_t;
typedef struct hb_glyph_position_t {
  hb_position_t  x_advance;
  hb_position_t  y_advance;
  hb_position_t  x_offset;
  hb_position_t  y_offset;
  uint32_t       var;
} hb_glyph_position_t;

typedef struct hb_blob_t hb_blob_t;
typedef struct hb_buffer_t hb_buffer_t;
typedef struct hb_face_t hb_face_t;
typedef struct hb_font_t hb_font_t;
typedef struct hb_set_t hb_set_t;

typedef void (*hb_destroy_func_t) (void *data);
typedef hb_blob_t * (*hb_reference_table_func_t)  (hb_face_t *face, hb_tag_t tag, void *user_data);


#include "ft-hb-decls.h"

#define FT_HB_APIS \
	FT_HB_API(hb_blob_create) \
	FT_HB_API(hb_blob_destroy) \
	FT_HB_API(hb_buffer_add_utf8) \
	FT_HB_API(hb_buffer_clear_contents) \
	FT_HB_API(hb_buffer_create) \
	FT_HB_API(hb_buffer_destroy) \
	FT_HB_API(hb_buffer_get_glyph_infos) \
	FT_HB_API(hb_buffer_get_glyph_positions) \
	FT_HB_API(hb_buffer_get_length) \
	FT_HB_API(hb_buffer_guess_segment_properties) \
	FT_HB_API(hb_face_create) \
	FT_HB_API(hb_face_create_for_tables) \
	FT_HB_API(hb_face_destroy) \
	FT_HB_API(hb_face_set_index) \
	FT_HB_API(hb_face_set_upem) \
	FT_HB_API(hb_font_create) \
	FT_HB_API(hb_font_destroy) \
	FT_HB_API(hb_font_get_face) \
	FT_HB_API(hb_font_set_scale) \
	FT_HB_API(hb_ot_layout_collect_lookups) \
	FT_HB_API(hb_ot_layout_lookup_collect_glyphs) \
	FT_HB_API(hb_ot_layout_lookup_would_substitute) \
	FT_HB_API(hb_ot_tags_from_script_and_language) \
	FT_HB_API(hb_set_create) \
	FT_HB_API(hb_set_destroy) \
	FT_HB_API(hb_set_is_empty) \
	FT_HB_API(hb_set_next) \
	FT_HB_API(hb_set_subtract) \
	FT_HB_API(hb_shape) \
	FT_HB_API(hb_version_at_least)


typedef struct ft_hb_funcs_t {
  void *lib; /* dlopen() handle. */
#define FT_HB_API(x) ft_##x##_func_t x;
FT_HB_APIS
#undef FT_HB_API
} ft_hb_funcs_t;

FT_LOCAL( ft_hb_funcs_t * ) ft_hb_funcs (void);

#define hb(x) ft_hb_funcs()->hb_##x

FT_END_HEADER

#endif /* FT_HB_H */


/* END */
