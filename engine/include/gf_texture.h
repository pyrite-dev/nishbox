#ifndef __GF_TEXTURE_H__
#define __GF_TEXTURE_H__

#include <gf_pre.h>
#include <gf_macro.h>

/* Type */
#include <gf_type/texture.h>

/* Engine */
#include <gf_type/draw.h>

/* Standard */

gf_texture_t* gf_register_texture(gf_draw_t* draw, int width, int height, unsigned char* data);
void	      gf_destroy_texture(gf_texture_t* texture);
void	      gf_draw_texture(gf_draw_t* draw, float x, float y, float w, float h, gf_texture_t* texture, float r, float g, float b, float a);

#endif
