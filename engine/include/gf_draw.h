/**
 * Drawing interface
 *
 * Handles rendering.
 */

#ifndef __GF_DRAW_H__
#define __GF_DRAW_H__

#include <gf_pre.h>
#include <gf_macro.h>

/* Type */
#include <gf_type/draw.h>

/* Engine */
#include <gf_type/core.h>

/* Standard */

GF_EXPORT gf_draw_t* gf_draw_create(gf_engine_t* engine, const char* title);
GF_EXPORT void	     gf_draw_destroy(gf_draw_t* draw);
GF_EXPORT void	     gf_draw_frame(gf_draw_t* draw);
GF_EXPORT int	     gf_draw_step(gf_draw_t* draw);
GF_EXPORT void	     gf_draw_begin(void);
GF_EXPORT void	     gf_draw_end(void);
GF_EXPORT void	     gf_draw_set_draw(gf_draw_t* engine, void (*func)(gf_draw_t*));
GF_EXPORT void	     gf_draw_reshape(gf_draw_t* draw);

#endif
