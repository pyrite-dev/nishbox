#ifndef __NE_DRAW_PLATFORM_H__
#define __NE_DRAW_PLATFORM_H__

#include <ne_pre.h>
#include <ne_macro.h>

/* Type */
#include <ne_type/draw_platform.h>

/* NishBox */
#include <ne_type/draw.h>

/* Standard */

void ne_draw_platform_create(ne_draw_t* draw);
void ne_draw_platform_destroy(ne_draw_t* draw);
int  ne_draw_platform_step(ne_draw_t* draw);
int  ne_draw_platform_has_extension(ne_draw_t* draw, const char* query);
void ne_draw_platform_begin(void);
void ne_draw_platform_end(void);

#endif
