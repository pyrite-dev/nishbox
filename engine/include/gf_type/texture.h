#ifndef __GF_TYPE_TEXTURE_H__
#define __GF_TYPE_TEXTURE_H__

#include <gf_pre.h>
#include <gf_macro.h>

#ifdef GF_EXPOSE_TEXTURE
/* External library */

/* Engine */
#include <gf_type/draw_driver.h>

/* Standard */

GF_DECLARE_TYPE(texture, {
	gf_draw_driver_texture_t* draw_driver_texture;
	int			  width;
	int			  height;
	int			  internal_width;
	int			  internal_height;
});
#else
typedef void gf_texture_t;
#endif

#endif
