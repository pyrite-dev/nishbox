#ifndef __NE_GRAPHIC_H__
#define __NE_GRAPHIC_H__

#include <ne_pre.h>
#include <ne_macro.h>

/* Type */

/* NishBox */
#include <ne_type/draw.h>

/* Standard */

void ne_graphic_clear(ne_draw_t* draw);
void ne_graphic_begin_2d(ne_draw_t* draw);
void ne_graphic_end_2d(ne_draw_t* draw);
void ne_graphic_text(ne_draw_t* draw, float x, float y, float size, const char* text, float r, float g, float b, float a);

#endif
