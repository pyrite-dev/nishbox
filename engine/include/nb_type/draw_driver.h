#ifndef __NB_TYPE_DRAW_DRIVER_H__
#define __NB_TYPE_DRAW_DRIVER_H__

#include <nb_pre.h>
#include <nb_macro.h>

#ifdef NB_EXPOSE_DRAW_DRIVER
/* External library */
#ifdef DRV_OPENGL
#include <GL/gl.h>
#include <GL/glu.h>
#endif

/* NishBox */

/* Standard */

#ifdef DRV_OPENGL
NB_DECLARE_TYPE(draw_driver, { GLUquadric* quadric; });
NB_DECLARE_TYPE(draw_driver_texture, { GLuint id; });
#endif
#else
typedef void nb_draw_driver_t;
typedef void nb_draw_driver_texture_t;
#endif

#endif
