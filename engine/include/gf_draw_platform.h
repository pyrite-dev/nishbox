#ifndef __GF_DRAW_PLATFORM_H__
#define __GF_DRAW_PLATFORM_H__

#include <gf_pre.h>
#include <gf_macro.h>

/* Type */
#include <gf_type/draw_platform.h>

/* Engine */
#include <gf_type/draw.h>

/* Standard */

void gf_draw_platform_create(gf_draw_t* draw);
void gf_draw_platform_destroy(gf_draw_t* draw);
int  gf_draw_platform_step(gf_draw_t* draw);
int  gf_draw_platform_has_extension(gf_draw_t* draw, const char* query);
void gf_draw_platform_begin(void);
void gf_draw_platform_end(void);

#endif
