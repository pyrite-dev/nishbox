#define GF_EXPOSE_TEXTURE

#include <gf_pre.h>

/* External library */

/* Interface */
#include <gf_texture.h>

/* Engine */
#include <gf_draw_driver.h>

/* Standard */
#include <stdlib.h>

gf_texture_t* gf_register_texture(gf_draw_t* draw, int width, int height, unsigned char* data) {
	gf_texture_t*		  texture   = malloc(sizeof(*texture));
	gf_draw_driver_texture_t* ddtexture = gf_draw_driver_register_texture(draw, width, height, data);
	if(ddtexture == NULL) {
		free(texture);
		return NULL;
	}
	texture->width		     = width;
	texture->height		     = height;
	texture->draw_driver_texture = ddtexture;
	return texture;
}

void gf_destroy_texture(gf_texture_t* texture) {
	gf_draw_driver_destroy_texture(texture->draw_driver_texture);
	free(texture);
}

void gf_draw_texture(gf_draw_t* draw, float x, float y, float w, float h, gf_texture_t* texture, float r, float g, float b, float a) { gf_draw_driver_draw_texture(draw, x, y, w, h, texture->draw_driver_texture, r, g, b, a); }
