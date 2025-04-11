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

#ifdef FT_CONFIG_OPTION_USE_HARFBUZZ

#include "ft-hb.h"

#include <dlfcn.h>

ft_hb_funcs_t * ft_hb_funcs (void)
{
  static ft_hb_funcs_t *funcs = NULL;
  if (funcs) return funcs;

#if 0
  if ( FT_NEW ( funcs ) )
    return NULL;
#endif

  funcs->lib = NULL;
  ft_hb_version_at_least_func_t version_at_least = dlsym( RTLD_DEFAULT, "hb_version_at_least" );
  if ( !version_at_least ) {
    /* Load the HarfBuzz library */
    funcs->lib = dlopen( "libharfbuzz.so", RTLD_GLOBAL );
    if ( !funcs->lib )
      goto fail;
    version_at_least = dlsym( funcs->lib, "hb_version_at_least" );
    if ( !version_at_least )
      goto fail;
  }

  /* Keep version in sync with meson.build and configure.raw */
  if ( !version_at_least ( 2, 0, 0 ) )
    goto fail;

  /* Load all symbols we use. */
#define FT_HB_API(name) \
  { \
    funcs->name = dlsym( funcs->lib, #name ); \
    if ( !funcs->name ) \
	    goto fail; \
  }
  FT_HB_APIS
#undef FT_HB_API

  return funcs;

fail:
  if (funcs->lib)
    dlclose (funcs->lib);
#if 0
  if (funcs)
    FT_FREE (funcs);
#endif
  funcs = NULL;
  return NULL;
}

#else /* !FT_CONFIG_OPTION_USE_HARFBUZZ */

/* ANSI C doesn't like empty source files */
typedef int  ft_hb_dummy_;

#endif /* !FT_CONFIG_OPTION_USE_HARFBUZZ */

/* END */
