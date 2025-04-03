#ifndef __NB_DRAW_DRIVER_H__
#define __NB_DRAW_DRIVER_H__

#include <nb_pre.h>
#include <nb_macro.h>

/* Type */
#include <nb_type/draw_driver.h>

/* NishBox */
#include <nb_type/draw.h>

/* Standard */

void nb_draw_driver_init(nb_draw_t* draw);
void nb_draw_driver_destroy(nb_draw_t* draw);
int  nb_draw_driver_has_extension(nb_draw_t* draw, const char* query);
void nb_draw_driver_reshape(nb_draw_t* draw);

nb_draw_driver_texture_t* nb_draw_driver_register_texture(nb_draw_t* draw, int width, int height, unsigned char* data);
void			  nb_draw_driver_destroy_texture(nb_draw_driver_texture_t* texture);

void nb_draw_clear(nb_draw_t* draw);
void nb_draw_begin_2d(nb_draw_t* draw);
void nb_draw_end_2d(nb_draw_t* draw);

#endif
