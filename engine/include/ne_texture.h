#ifndef __NE_TEXTURE_H__
#define __NE_TEXTURE_H__

#include <ne_pre.h>
#include <ne_macro.h>

/* Type */
#include <ne_type/texture.h>

/* NishBox */
#include <ne_type/draw.h>

/* Standard */

ne_texture_t* ne_register_texture(ne_draw_t* draw, int width, int height, unsigned char* data);
void	      ne_destroy_texture(ne_texture_t* texture);
void	      ne_draw_texture(ne_draw_t* draw, float x, float y, float w, float h, ne_texture_t* texture, float r, float g, float b, float a);

#endif
