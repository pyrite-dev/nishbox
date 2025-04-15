/**
 * @file gf_type/draw.h
 * @~english
 * @brief Type definitions related to drawing interface
 */

#ifndef __GF_TYPE_DRAW_H__
#define __GF_TYPE_DRAW_H__

#include <gf_pre.h>
#include <gf_macro.h>

#ifdef GF_EXPOSE_DRAW
/* External library */

/* Engine */
#include <gf_type/draw_platform.h>
#include <gf_type/draw_driver.h>
#include <gf_type/texture.h>
#include <gf_type/core.h>
#include <gf_type/math.h>
#include <gf_type/gui.h>

/* Standard */

GF_DECLARE_TYPE(draw, );

/**
 * @struct gf_draw_t
 * @~english
 * @brief Drawing interface
 */
GF_DECLARE_TYPE(draw, {
	gf_engine_t*	    engine;
	gf_draw_platform_t* platform;
	gf_draw_driver_t*   driver;
	gf_gui_t*	    gui;
	int		    close;
	int		    x;
	int		    y;
	int		    width;
	int		    height;
	int		    running;
	int		    draw_3d;
	char		    title[128];
	gf_texture_t*	    font[128];
	gf_vector_t	    light;
	gf_vector_t	    lookat;
	gf_vector_t	    camera;
	void (*draw)(gf_draw_t*);
});
#else
typedef void gf_draw_t;
#endif

#endif
