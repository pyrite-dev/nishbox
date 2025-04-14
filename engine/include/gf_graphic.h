/**
 * Graphic
 *
 * Provides the function to draw textures, text, and etc for
 * GUI and 3D rendering.
 */

#ifndef __GF_GRAPHIC_H__
#define __GF_GRAPHIC_H__

#include <gf_pre.h>
#include <gf_macro.h>

/* Type */
#include <gf_type/graphic.h>

/* Engine */
#include <gf_type/draw.h>
#include <gf_type/texture.h>

/* Standard */

#define GF_GRAPHIC_FONT_ASPECT_X 1
#define GF_GRAPHIC_FONT_ASPECT_Y 2

#define GF_SET_COLOR(color, red, green, blue, alpha) \
	color.r = (red); \
	color.g = (green); \
	color.b = (blue); \
	color.a = (alpha)

GF_EXPORT void gf_graphic_clear(gf_draw_t* draw);

GF_EXPORT void gf_graphic_begin_2d(gf_draw_t* draw);
GF_EXPORT void gf_graphic_end_2d(gf_draw_t* draw);

GF_EXPORT void gf_graphic_draw_texture_2d(gf_draw_t* draw, float x, float y, float w, float h, gf_texture_t* texture, gf_color_t color);
GF_EXPORT void gf_graphic_fill_polygon(gf_draw_t* draw, gf_color_t color, int npair, ...);

/* Common */
GF_EXPORT float gf_graphic_text_width(gf_draw_t* draw, float size, const char* text);
GF_EXPORT void	gf_graphic_text(gf_draw_t* draw, float x, float y, float size, const char* text, gf_color_t color);
GF_EXPORT void	gf_graphic_fill_rect(gf_draw_t* draw, float x, float y, float w, float h, gf_color_t color);

#endif
