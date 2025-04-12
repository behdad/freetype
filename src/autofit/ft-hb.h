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
  void *lib; /* dlopen() handle. */
#define HB_EXTERN(ret, name, args) ft_##name##_func_t name;
#include "ft-hb-decls.h"
#undef HB_EXTERN
} ft_hb_funcs_t;

struct  AF_FaceGlobalsRec_;
FT_LOCAL( ft_hb_funcs_t * ) ft_hb_funcs_new ( struct  AF_FaceGlobalsRec_ *af_globals );
FT_LOCAL( void ) ft_hb_funcs_free ( ft_hb_funcs_t* funcs , struct  AF_FaceGlobalsRec_ *af_globals );
#define hb(x) globals->hb_funcs->hb_##x

#else /* FT_CONFIG_OPTION_USE_HARFBUZZ_DYNAMIC */

#include <hb-ot.h>

#define hb(x) hb_##x

#endif /* FT_CONFIG_OPTION_USE_HARFBUZZ_DYNAMIC */

#endif /* FT_CONFIG_OPTION_USE_HARFBUZZ */

FT_END_HEADER

#endif /* FT_HB_H */

/* END */
