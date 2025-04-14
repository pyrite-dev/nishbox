#ifndef __GF_TYPE_DRAW_DRIVER_H__
#define __GF_TYPE_DRAW_DRIVER_H__

#include <gf_pre.h>
#include <gf_macro.h>

#ifdef GF_EXPOSE_DRAW_DRIVER
/* External library */
#ifdef DRV_OPENGL
#include <gf_opengl.h>
#endif

/* Engine */

/* Standard */

#ifdef DRV_OPENGL
GF_DECLARE_TYPE(draw_driver, { GLUquadric* quadric; });
GF_DECLARE_TYPE(draw_driver_texture, {
	GLuint id;
	int    width;
	int    height;
});
#endif
#else
typedef void gf_draw_driver_t;
typedef void gf_draw_driver_texture_t;
#endif

#endif
