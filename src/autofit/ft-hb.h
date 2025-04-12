#ifndef FT_HB_H
#define FT_HB_H

#include <freetype/internal/compiler-macros.h>
#include <freetype/freetype.h>

#ifdef FT_CONFIG_OPTION_USE_HARFBUZZ

#ifdef FT_CONFIG_OPTION_USE_HARFBUZZ_DYNAMIC

#include "ft-hb-types.h"

FT_BEGIN_HEADER

#define HB_EXTERN(ret, name, args) typedef ret (*ft_##name##_func_t) args;
#include "ft-hb-decls.h"
#undef HB_EXTERN

typedef struct ft_hb_funcs_t {
#define HB_EXTERN(ret, name, args) ft_##name##_func_t name;
#include "ft-hb-decls.h"
#undef HB_EXTERN
} ft_hb_funcs_t;

struct  AF_ModuleRec_;
FT_LOCAL( void ) ft_hb_funcs_init ( struct  AF_ModuleRec_ *af_module );
FT_LOCAL( void ) ft_hb_funcs_done ( struct  AF_ModuleRec_ *af_module );

struct AF_FaceGlobalsRec_;
FT_LOCAL( int ) ft_hb_enabled ( struct AF_FaceGlobalsRec_ *globals );

#define hb(x) globals->module->hb_funcs->hb_##x

#else /* FT_CONFIG_OPTION_USE_HARFBUZZ_DYNAMIC */

#include <hb-ot.h>

#define hb(x) hb_##x

#endif /* FT_CONFIG_OPTION_USE_HARFBUZZ_DYNAMIC */

#endif /* FT_CONFIG_OPTION_USE_HARFBUZZ */

FT_END_HEADER

#endif /* FT_HB_H */

/* END */
