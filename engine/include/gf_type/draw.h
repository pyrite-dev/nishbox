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
 *
 * @var gf_draw_t::platform
 * @brief Platform-dependent part of drawing
 *
 * @var gf_draw_t::driver
 * @brief Driver-dependent part of drawing
 *
 * @var gf_draw_t::gui
 * @brief GUI
 *
 * @var gf_draw_t::close
 * @brief `1` if it was requested to be closed, otherwise `0`
 *
 * @var gf_draw_t::x
 * @brief X coord of window
 *
 * @var gf_draw_t::y
 * @brief Y coord of window
 *
 * @var gf_draw_t::width
 * @brief Width of window
 *
 * @var gf_draw_t::height
 * @brief Height of window
 *
 * @var gf_draw_t::running
 * @brief `1` if running, otherwise `0`
 *
 * @var gf_draw_t::draw_3d
 * @brief `1` if engine should start rendering 3D stuffs, otherwise `0`
 *
 * @var gf_draw_t::title
 * @brief Window title
 *
 * @var gf_draw_t::font
 * @brief Array of texture of glyphs
 *
 * @var gf_draw_t::light
 * @brief Light location
 * @note gf_draw_t::light[3] should be 1
 *
 * @var gf_draw_t::lookat
 * @brief Where to look at
 *
 * @var gf_draw_t::camera
 * @brief Camera location
 *
 * @var gf_draw_t::camera
 * @brief Camera location
 *
 * @var gf_draw_t::draw
 * @brief User-drawing callback
 */
GF_DECLARE_TYPE(draw, {
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
