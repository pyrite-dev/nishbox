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

#endif
