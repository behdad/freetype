/*
 * Copyright © 2009, 2023  Red Hat, Inc.
 * Copyright © 2015  Google, Inc.
 *
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
 * Red Hat Author(s): Behdad Esfahbod, Matthias Clasen
 * Google Author(s): Behdad Esfahbod
 */

#include <freetype/freetype.h>
#include <freetype/internal/ftmemory.h>

#if defined(FT_CONFIG_OPTION_USE_HARFBUZZ) && \
    defined(FT_CONFIG_OPTION_USE_HARFBUZZ_DYNAMIC)

#include "ft-hb.h"

#include "afglobal.h"

#include <dlfcn.h>

ft_hb_funcs_t * ft_hb_funcs_new ( struct  AF_FaceGlobalsRec_ *af_globals )
{
  FT_Memory memory = af_globals->face->memory;
  FT_Error error;
  ft_hb_funcs_t *funcs = NULL;

  if ( FT_NEW ( funcs ) )
    return NULL;
  FT_ZERO( funcs );

  ft_hb_version_atleast_func_t version_atleast = dlsym( RTLD_DEFAULT, "hb_version_atleast" );
  if ( !version_atleast )
  {
    /* Load the HarfBuzz library */
    funcs->lib = dlopen( "libharfbuzz.so.0", RTLD_LAZY | RTLD_GLOBAL );
    if ( !funcs->lib )
      goto fail;
    version_atleast = dlsym( funcs->lib, "hb_version_atleast" );
    if ( !version_atleast )
      goto fail;
  }

  /* Keep version in sync with meson.build and configure.raw */
  if ( !version_atleast ( 2, 0, 0 ) )
    goto fail;

  /* Load all symbols we use. */
#define HB_EXTERN(ret, name, args) \
  { \
    funcs->name = dlsym( funcs->lib, #name ); \
    if ( !funcs->name ) \
	    goto fail; \
  }
#include "ft-hb-decls.h"
#undef HB_EXTERN

  return funcs;

fail:
  ft_hb_funcs_free ( funcs, af_globals );
  return NULL;
}

void ft_hb_funcs_free ( ft_hb_funcs_t* funcs, struct AF_FaceGlobalsRec_ *af_globals)
{
  FT_Memory memory = af_globals->face->memory;

  if ( !funcs )
    return;

#if 0
  /* Never close the library, since we opened it with RTLD_GLOBAL.
   * This is important for the case where we are using HarfBuzz
   * as a shared library, and we want to use the symbols from
   * the library in other shared libraries or clients. HarfBuzz
   * holds onto global variables, and closing the library
   * will cause them to be invalidated.
   */
  if ( funcs->lib )
    dlclose ( funcs->lib );
#endif

  FT_FREE ( funcs );
}

#else /* !FT_CONFIG_OPTION_USE_HARFBUZZ* */

/* ANSI C doesn't like empty source files */
typedef int  ft_hb_dummy_;

#endif /* !FT_CONFIG_OPTION_USE_HARFBUZZ* */

/* END */
