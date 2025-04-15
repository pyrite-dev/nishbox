/**
 * @file gf_draw_platform.h
 * @~english
 * @brief Platform-dependent part of drawing driver
 */

#ifndef __GF_DRAW_PLATFORM_H__
#define __GF_DRAW_PLATFORM_H__

#include <gf_pre.h>
#include <gf_macro.h>

/* Type */
#include <gf_type/draw_platform.h>

/* Engine */
#include <gf_type/draw.h>

/* Standard */

GF_EXPORT void gf_draw_platform_create(gf_draw_t* draw);
GF_EXPORT void gf_draw_platform_destroy(gf_draw_t* draw);
GF_EXPORT int  gf_draw_platform_step(gf_draw_t* draw);
GF_EXPORT int  gf_draw_platform_has_extension(gf_draw_t* draw, const char* query);
GF_EXPORT void gf_draw_platform_begin(void);
GF_EXPORT void gf_draw_platform_end(void);

#endif
