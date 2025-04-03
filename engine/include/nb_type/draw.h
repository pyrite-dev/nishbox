#ifndef __NB_TYPE_DRAW_H__
#define __NB_TYPE_DRAW_H__

#include <nb_pre.h>
#include <nb_macro.h>

#ifdef NB_EXPOSE_DRAW
/* External library */

/* NishBox */
#include <nb_type/draw_platform.h>
#include <nb_type/draw_driver.h>
#include <nb_type/texture.h>
#include <nb_type/math.h>

/* Standard */

NB_DECLARE_TYPE(draw, {
	nb_draw_platform_t* platform;
	nb_draw_driver_t*   driver;
	int		    close;
	int		    x;
	int		    y;
	int		    width;
	int		    height;
	int		    running;
	nb_texture_t*	    font[128];
	nb_vector_t	    light;
	nb_vector_t	    lookat;
	nb_vector_t	    camera;
});
#else
typedef void nb_draw_t;
#endif

#endif
