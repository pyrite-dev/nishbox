#ifndef __NB_TEXTURE_H__
#define __NB_TEXTURE_H__

#include <nb_pre.h>
#include <nb_macro.h>

/* Type */
#include <nb_type/texture.h>

/* NishBox */
#include <nb_type/draw.h>

/* Standard */

nb_texture_t* nb_register_texture(nb_draw_t* draw, int width, int height, unsigned char* data);
void	      nb_destroy_texture(nb_texture_t* texture);
void	      nb_draw_texture(nb_draw_t* draw, float x, float y, float w, float h, nb_texture_t* texture, float r, float g, float b, float a);

#endif
