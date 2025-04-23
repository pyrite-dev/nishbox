#define GF_EXPOSE_DRAW
#define GF_EXPOSE_TEXTURE

#include <gf_pre.h>

/* External library */
#include <gf_directx.h>

/* Interface */
#include <gf_graphic.h>

/* Engine */
#include <gf_draw.h>
#include <gf_texture.h>
#include <gf_draw_driver.h>
#include <gf_math.h>

/* Standard */
#include <stdarg.h>
#include <stdio.h>

void gf_graphic_begin_2d(gf_draw_t* draw) { /* TODO: Implement this */ }

void gf_graphic_end_2d(gf_draw_t* draw) { /* TODO: Implement this */ }

void gf_graphic_clear(gf_draw_t* draw) { /* TODO: Implement this */ }

void gf_graphic_draw_texture_polygon(gf_draw_t* draw, gf_texture_t* texture, gf_graphic_color_t color, int dim, int npair, ...) { /* TODO: Implement this */ }

void gf_graphic_fill_polygon(gf_draw_t* draw, gf_graphic_color_t color, int dim, int npair, ...) { /* TODO: Implement this */ }

void gf_graphic_perspective(gf_draw_t* draw, double fovy, double znear, double zfar) { /* TODO: Implement this */ }

void gf_graphic_set_camera(gf_draw_t* draw) { /* TODO: Implement this */ }

void gf_graphic_clip_push(gf_draw_t* draw, double x, double y, double w, double h) { /* TODO: Implement this */ }

void gf_graphic_clip_pop(gf_draw_t* draw) { /* TODO: Implement this */ }
