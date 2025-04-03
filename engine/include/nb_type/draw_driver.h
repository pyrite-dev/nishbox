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

NB_DECLARE_TYPE(draw_driver, {
#ifdef DRV_OPENGL
	GLUquadric* quadric;
#endif
});
NB_DECLARE_TYPE(draw_driver_texture, {
#ifdef DRV_OPENGL
	GLuint id;
#endif
});
#else
typedef void nb_draw_driver_t;
typedef void nb_draw_driver_texture_t;
#endif

#endif
