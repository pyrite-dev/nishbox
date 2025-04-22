/**
 * @file gf_graphic.h
 * @~english
 * @brief Graphic interface
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

/**
 * @~english
 * @brief Dimension parameter for 2D
 */
#define GF_GRAPHIC_2D 2

/**
 * @~english
 * @brief Dimension parameter for 3D
 */
#define GF_GRAPHIC_3D 3

/**
 * @~english
 * @brief Macro to set color safely and shorter
 * @param color gf_graphic_color_t
 */
#define GF_SET_COLOR(color, red, green, blue, alpha) \
	color.r = (red); \
	color.g = (green); \
	color.b = (blue); \
	color.a = (alpha)

/**
 * @~english
 * @brief Clear the screen
 */
GF_EXPORT void gf_graphic_clear(gf_draw_t* draw);

/**
 * @~english
 * @brief Start 2D mode
 */
GF_EXPORT void gf_graphic_begin_2d(gf_draw_t* draw);

/**
 * @~english
 * @brief End 2D mode
 */
GF_EXPORT void gf_graphic_end_2d(gf_draw_t* draw);

/**
 * @~english
 * @brief Draw polygon with texture
 */
GF_EXPORT void gf_graphic_draw_texture_polygon(gf_draw_t* draw, gf_texture_t* texture, gf_graphic_color_t color, int dim, int npair, ...);

/**
 * @~english
 * @brief Draw polygon
 */
GF_EXPORT void gf_graphic_fill_polygon(gf_draw_t* draw, gf_graphic_color_t color, int dim, int npair, ...);

/**
 * @~english
 * @brief Set perspective
 * @param draw Drawing interface
 * @param fovy FOV
 * @param znear Distance from viewer to the near clipping plane
 * @param zfar Distance from viewer to the far clipping plane
 */
GF_EXPORT void gf_graphic_perspective(gf_draw_t* draw, double fovy, double znear, double zfar);

/**
 * @~english
 * @brief Set camera
 * @param draw Drawing interface
 */
GF_EXPORT void gf_graphic_set_camera(gf_draw_t* draw);

/**
 * @~english
 * @brief Set clipping region
 */
GF_EXPORT void gf_graphic_clip(gf_draw_t* draw, double x, double y, double w, double h);

/* Common */

/**
 * @~english
 * @brief Calculate text width
 * @return Text width
 */
GF_EXPORT double gf_graphic_text_width(gf_draw_t* draw, double size, const char* text);

/**
 * @~english
 * @brief Draw text
 */
GF_EXPORT void gf_graphic_text(gf_draw_t* draw, double x, double y, double size, const char* text, gf_graphic_color_t color);

/**
 * @~english
 * @brief Draw filled rectangle
 */
GF_EXPORT void gf_graphic_fill_rect(gf_draw_t* draw, double x, double y, double w, double h, gf_graphic_color_t color);

/**
 * @~english
 * @brief Draw rectangle with texture
 */
GF_EXPORT void gf_graphic_draw_texture_2d(gf_draw_t* draw, double x, double y, double w, double h, gf_texture_t* texture, gf_graphic_color_t color);

#endif
