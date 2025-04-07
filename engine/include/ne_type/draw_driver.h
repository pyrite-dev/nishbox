#ifndef __NE_TYPE_DRAW_DRIVER_H__
#define __NE_TYPE_DRAW_DRIVER_H__

#include <ne_pre.h>
#include <ne_macro.h>

#ifdef NE_EXPOSE_DRAW_DRIVER
/* External library */
#ifdef DRV_OPENGL
#include <GL/gl.h>
#include <GL/glu.h>
#endif

/* NishBox */

/* Standard */

#ifdef DRV_OPENGL
NE_DECLARE_TYPE(draw_driver, { GLUquadric* quadric; });
NE_DECLARE_TYPE(draw_driver_texture, { GLuint id; });
#endif
#else
typedef void ne_draw_driver_t;
typedef void ne_draw_driver_texture_t;
#endif

#endif
