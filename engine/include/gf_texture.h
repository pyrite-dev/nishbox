/**
 * Texture
 *
 * Provides a wrapper for drawing driver.
 */

#ifndef __GF_TEXTURE_H__
#define __GF_TEXTURE_H__

#include <gf_pre.h>
#include <gf_macro.h>

/* Type */
#include <gf_type/texture.h>

/* Engine */
#include <gf_type/draw.h>

/* Standard */

GF_EXPORT gf_texture_t* gf_texture_register(gf_draw_t* draw, int width, int height, unsigned char* data);
GF_EXPORT void		gf_texture_destroy(gf_texture_t* texture);

#endif
