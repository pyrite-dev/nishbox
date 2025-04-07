#ifndef __NE_DRAW_DRIVER_H__
#define __NE_DRAW_DRIVER_H__

#include <ne_pre.h>
#include <ne_macro.h>

/* Type */
#include <ne_type/draw_driver.h>

/* NishBox */
#include <ne_type/draw.h>

/* Standard */

void ne_draw_driver_init(ne_draw_t* draw);
void ne_draw_driver_destroy(ne_draw_t* draw);
int  ne_draw_driver_has_extension(ne_draw_t* draw, const char* query);
void ne_draw_driver_reshape(ne_draw_t* draw);

ne_draw_driver_texture_t* ne_draw_driver_register_texture(ne_draw_t* draw, int width, int height, unsigned char* data);
void			  ne_draw_driver_destroy_texture(ne_draw_driver_texture_t* texture);
void			  ne_draw_driver_draw_texture(ne_draw_t* draw, float x, float y, float w, float h, ne_draw_driver_texture_t* texture, float r, float g, float b, float a);
void			  ne_draw_driver_before(ne_draw_t* draw);
void			  ne_draw_driver_after(ne_draw_t* draw);

#endif
