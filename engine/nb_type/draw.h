#ifndef __NB_TYPE_DRAW_H__
#define __NB_TYPE_DRAW_H__

#include <nb_pre.h>
#include <nb_macro.h>

#ifdef NB_EXPOSE_DRAW
/* External library */

/* NishBox */
#include <nb_type/draw_platform.h>

/* Standard */

NB_DECLARE_TYPE(draw, {
	nb_draw_platform_t* platform;
	int		    close;
	int		    x;
	int		    y;
	int		    width;
	int		    height;
	int		    running;
	GLuint		    font[128];
	GLfloat		    light[4];
	GLfloat		    lookat[3];
	GLfloat		    camera[3];
	GLUquadric*	    quadric;
});
#else
typedef void nb_draw_t;
#endif

#endif
