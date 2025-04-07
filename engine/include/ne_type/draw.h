#ifndef __NE_TYPE_DRAW_H__
#define __NE_TYPE_DRAW_H__

#include <ne_pre.h>
#include <ne_macro.h>

#ifdef NE_EXPOSE_DRAW
/* External library */

/* NishBox */
#include <ne_type/draw_platform.h>
#include <ne_type/draw_driver.h>
#include <ne_type/texture.h>
#include <ne_type/math.h>

/* Standard */

NE_DECLARE_TYPE(draw, {
	ne_draw_platform_t* platform;
	ne_draw_driver_t*   driver;
	int		    close;
	int		    x;
	int		    y;
	int		    width;
	int		    height;
	int		    running;
	ne_texture_t*	    font[128];
	ne_vector_t	    light;
	ne_vector_t	    lookat;
	ne_vector_t	    camera;
});
#else
typedef void ne_draw_t;
#endif

#endif
