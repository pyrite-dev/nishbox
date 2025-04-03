#ifndef __NB_DRAW_PLATFORM_H__
#define __NB_DRAW_PLATFORM_H__

#include <nb_pre.h>
#include <nb_macro.h>

/* Type */
#include <nb_type/draw_platform.h>

/* NishBox */
#include <nb_type/draw.h>

/* Standard */

void nb_draw_platform_create(nb_draw_t* draw);
void nb_draw_platform_destroy(nb_draw_t* draw);
int  nb_draw_platform_step(nb_draw_t* draw);
int  nb_draw_platform_has_extension(nb_draw_t* draw, const char* query);
void nb_draw_platform_begin(void);
void nb_draw_platform_end(void);

#endif
