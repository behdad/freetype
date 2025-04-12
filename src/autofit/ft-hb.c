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

#include "afglobal.h"

#include "ft-hb.h"


#if defined(FT_CONFIG_OPTION_USE_HARFBUZZ) && \
    defined(FT_CONFIG_OPTION_USE_HARFBUZZ_DYNAMIC)

#ifdef _WIN32
#include <windows.h>
#else
#include <dlfcn.h>
#endif


void ft_hb_funcs_init ( struct  AF_ModuleRec_ *af_module )
{
  FT_Memory memory = af_module->root.memory;
  FT_Error error;

  ft_hb_funcs_t *funcs = NULL;
  ft_hb_version_atleast_func_t version_atleast = NULL;

  if ( FT_NEW ( funcs ) )
    goto fail;
  FT_ZERO( funcs );

#ifdef _WIN32
#define DLSYM(lib, name) (ft_##name##_func_t) GetProcAddress( lib, #name )
#else /* !_WIN32 */
#define DLSYM(lib, name) dlsym( lib, #name )
#endif

#ifdef _WIN32
  HANDLE lib = LoadLibraryW( L"libharfbuzz-0.dll" );
  if ( !lib )
    goto fail;
  version_atleast = DLSYM( lib, hb_version_atleast );
#else /* !_WIN32 */
  void *lib = RTLD_DEFAULT;
  version_atleast = DLSYM( lib, hb_version_atleast );
  if ( !version_atleast )
  {
    /* Load the HarfBuzz library.
     *
     * We never close the library, since we opened it with RTLD_GLOBAL.
     * This is important for the case where we are using HarfBuzz
     * as a shared library, and we want to use the symbols from
     * the library in other shared libraries or clients. HarfBuzz
     * holds onto global variables, and closing the library
     * will cause them to be invalidated.
     */
#ifdef __APPLE__
#define LIBHARFBUZZ "libharfbuzz.dylib"
#else
#define LIBHARFBUZZ "libharfbuzz.so"
#endif
    lib = dlopen( LIBHARFBUZZ, RTLD_LAZY | RTLD_GLOBAL );
#undef LIBHARFBUZZ

    if ( !lib )
      goto fail;
    version_atleast = DLSYM( lib, hb_version_atleast );
    if ( !version_atleast )
      goto fail;
  }
#endif

  /* Keep version in sync with meson.build and configure.raw */
  if ( !version_atleast ( 2, 0, 0 ) )
    goto fail;

  /* Load all symbols we use. */

#define HB_EXTERN(ret, name, args) \
  { \
    funcs->name = DLSYM( lib, name ); \
    if ( !funcs->name ) \
      goto fail; \
  }
#include "ft-hb-decls.h"
#undef HB_EXTERN

#undef DLSYM

  af_module->hb_funcs = funcs;
  return;

fail:
  if ( funcs )
    FT_FREE( funcs );

  af_module->hb_funcs = NULL;
}

void ft_hb_funcs_done ( struct AF_ModuleRec_ *af_module)
{
  FT_Memory memory = af_module->root.memory;

  if ( af_module->hb_funcs )
  {
    FT_FREE ( af_module->hb_funcs );
    af_module->hb_funcs = NULL;
  }
}

FT_Bool ft_hb_enabled ( struct AF_FaceGlobalsRec_ *globals )
{
  return globals->module->hb_funcs != NULL;
}

#else /* FT_CONFIG_OPTION_USE_HARFBUZZ_DYNAMIC */

FT_Bool ft_hb_enabled ( struct AF_FaceGlobalsRec_ *globals )
{
#ifdef FT_CONFIG_OPTION_USE_HARFBUZZ
  return TRUE;
#else
  return FALSE;
#endif
}

#endif /* FT_CONFIG_OPTION_USE_HARFBUZZ_DYNAMIC */

/* END */
