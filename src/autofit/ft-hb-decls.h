
/* hb-blob.h */

HB_EXTERN(hb_blob_t *,
hb_blob_create,(const char        *data,
		unsigned int       length,
		hb_memory_mode_t   mode,
		void              *user_data,
		hb_destroy_func_t  destroy))

HB_EXTERN(void,
hb_blob_destroy,(hb_blob_t *blob))

/* hb-buffer.h */

HB_EXTERN(void,
hb_buffer_add,(hb_buffer_t    *buffer,
	       hb_codepoint_t  codepoint,
	       unsigned int    cluster))

HB_EXTERN(void,
hb_buffer_add_utf8,(hb_buffer_t  *buffer,
		    const char   *text,
		    int           text_length,
		    unsigned int  item_offset,
		    int           item_length))

HB_EXTERN(hb_bool_t,
hb_buffer_allocation_successful,(hb_buffer_t  *buffer))

HB_EXTERN(void,
hb_buffer_clear_contents,(hb_buffer_t *buffer))

HB_EXTERN(hb_buffer_t *,
hb_buffer_create,(void))

HB_EXTERN(void,
hb_buffer_destroy,(hb_buffer_t *buffer))

HB_EXTERN(hb_glyph_info_t *,
hb_buffer_get_glyph_infos,(hb_buffer_t  *buffer,
			   unsigned int *length))

HB_EXTERN(hb_glyph_position_t *,
hb_buffer_get_glyph_positions,(hb_buffer_t  *buffer,
			       unsigned int *length))

HB_EXTERN(unsigned int,
hb_buffer_get_length,(const hb_buffer_t *buffer))

HB_EXTERN(void,
hb_buffer_guess_segment_properties,(hb_buffer_t *buffer))

HB_EXTERN(hb_bool_t,
hb_buffer_pre_allocate,(hb_buffer_t  *buffer,
			unsigned int  size))

HB_EXTERN(void,
hb_buffer_set_direction,(hb_buffer_t    *buffer,
			 hb_direction_t  direction))

/* hb-face.h */

HB_EXTERN(hb_face_t *,
hb_face_create,(hb_blob_t    *blob,
		unsigned int  index))

HB_EXTERN(hb_face_t *,
hb_face_create_for_tables,(hb_reference_table_func_t  reference_table_func,
			   void                      *user_data,
			   hb_destroy_func_t          destroy))

HB_EXTERN(void,
hb_face_destroy,(hb_face_t *face))

HB_EXTERN(void,
hb_face_set_index,(hb_face_t    *face,
		   unsigned int  index))

HB_EXTERN(void,
hb_face_set_upem,(hb_face_t    *face,
		  unsigned int  upem))

/* hb-font.h */

HB_EXTERN(hb_font_t *,
hb_font_create,(hb_face_t *face))

HB_EXTERN(void,
hb_font_destroy,(hb_font_t *font))

HB_EXTERN(hb_face_t *,
hb_font_get_face,(hb_font_t *font))

HB_EXTERN(void,
hb_font_set_scale,(hb_font_t *font,
		   int x_scale,
		   int y_scale))

/* hb-ot-layout.h */

HB_EXTERN(void,
hb_ot_layout_collect_lookups,(hb_face_t      *face,
			      hb_tag_t        table_tag,
			      const hb_tag_t *scripts,
			      const hb_tag_t *languages,
			      const hb_tag_t *features,
			      hb_set_t       *lookup_indexes /* OUT */))

HB_EXTERN(void,
hb_ot_layout_lookup_collect_glyphs,(hb_face_t    *face,
				    hb_tag_t      table_tag,
				    unsigned int  lookup_index,
				    hb_set_t     *glyphs_before, /* OUT.  May be NULL */
				    hb_set_t     *glyphs_input,  /* OUT.  May be NULL */
				    hb_set_t     *glyphs_after,  /* OUT.  May be NULL */
				    hb_set_t     *glyphs_output  /* OUT.  May be NULL */))

HB_EXTERN(unsigned,
hb_ot_layout_lookup_get_glyph_alternates,(hb_face_t      *face,
					  unsigned        lookup_index,
					  hb_codepoint_t  glyph,
					  unsigned        start_offset,
					  unsigned       *alternate_count /* IN/OUT */,
					  hb_codepoint_t *alternate_glyphs /* OUT */))

HB_EXTERN(hb_bool_t,
hb_ot_layout_lookup_would_substitute,(hb_face_t            *face,
				      unsigned int          lookup_index,
				      const hb_codepoint_t *glyphs,
				      unsigned int          glyphs_length,
				      hb_bool_t             zero_context))

HB_EXTERN(unsigned int,
hb_ot_layout_table_get_feature_tags,(hb_face_t    *face,
				     hb_tag_t      table_tag,
				     unsigned int  start_offset,
				     unsigned int *feature_count /* IN/OUT */,
				     hb_tag_t     *feature_tags /* OUT */))

HB_EXTERN(void,
hb_ot_tags_from_script_and_language,(hb_script_t   script,
				     hb_language_t language,
				     unsigned int *script_count /* IN/OUT */,
				     hb_tag_t     *script_tags /* OUT */,
				     unsigned int *language_count /* IN/OUT */,
				     hb_tag_t     *language_tags /* OUT */))

/* hb-ot-shape.h */

HB_EXTERN(void,
hb_ot_shape_glyphs_closure,(hb_font_t          *font,
			    hb_buffer_t        *buffer,
			    const hb_feature_t *features,
			    unsigned int        num_features,
			    hb_set_t           *glyphs))

/* hb-set.h */

HB_EXTERN(void,
hb_set_add,(hb_set_t       *set,
	    hb_codepoint_t  codepoint))

HB_EXTERN(hb_bool_t,
hb_set_allocation_successful,(const hb_set_t *set))

HB_EXTERN(void,
hb_set_clear,(hb_set_t *set))

HB_EXTERN(hb_set_t *,
hb_set_create,(void))

HB_EXTERN(void,
hb_set_destroy,(hb_set_t *set))

HB_EXTERN(void,
hb_set_del,(hb_set_t       *set,
	    hb_codepoint_t  codepoint))

HB_EXTERN(unsigned int,
hb_set_get_population,(const hb_set_t *set))

HB_EXTERN(hb_bool_t,
hb_set_is_empty,(const hb_set_t *set))

HB_EXTERN(hb_bool_t,
hb_set_next,(const hb_set_t *set,
	     hb_codepoint_t *codepoint))

HB_EXTERN(void,
hb_set_subtract,(hb_set_t       *set,
		 const hb_set_t *other))

HB_EXTERN(void,
hb_set_union,(hb_set_t       *set,
	      const hb_set_t *other))

/* hb-shape.h */

HB_EXTERN(void,
hb_shape,(hb_font_t           *font,
	  hb_buffer_t         *buffer,
	  const hb_feature_t  *features,
	  unsigned int         num_features))

HB_EXTERN(hb_bool_t,
hb_version_atleast,(unsigned int major,
		    unsigned int minor,
		    unsigned int micro))

