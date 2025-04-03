#ifndef __NB_GRAPHIC_H__
#define __NB_GRAPHIC_H__

#include <nb_pre.h>
#include <nb_macro.h>

/* Type */

/* NishBox */
#include <nb_type/draw.h>

/* Standard */

void nb_graphic_clear(nb_draw_t* draw);
void nb_graphic_begin_2d(nb_draw_t* draw);
void nb_graphic_end_2d(nb_draw_t* draw);
void nb_graphic_text(nb_draw_t* draw, float x, float y, float size, const char* text, float r, float g, float b, float a);

#endif
