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
void			  nb_draw_driver_draw_texture(nb_draw_t* draw, float x, float y, float w, float h, nb_draw_driver_texture_t* texture, float r, float g, float b, float a);
void			  nb_draw_driver_before(nb_draw_t* draw);
void			  nb_draw_driver_after(nb_draw_t* draw);

#endif
