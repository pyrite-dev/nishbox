#define NE_EXPOSE_TEXTURE

#include <ne_pre.h>

/* External library */

/* Interface */
#include <ne_texture.h>

/* NishBox */
#include <ne_draw_driver.h>

/* Standard */
#include <stdlib.h>

ne_texture_t* ne_register_texture(ne_draw_t* draw, int width, int height, unsigned char* data) {
	ne_texture_t*		  texture   = malloc(sizeof(*texture));
	ne_draw_driver_texture_t* ddtexture = ne_draw_driver_register_texture(draw, width, height, data);
	if(ddtexture == NULL) {
		free(texture);
		return NULL;
	}
	texture->width		     = width;
	texture->height		     = height;
	texture->draw_driver_texture = ddtexture;
	return texture;
}

void ne_destroy_texture(ne_texture_t* texture) {
	ne_draw_driver_destroy_texture(texture->draw_driver_texture);
	free(texture);
}

void ne_draw_texture(ne_draw_t* draw, float x, float y, float w, float h, ne_texture_t* texture, float r, float g, float b, float a) { ne_draw_driver_draw_texture(draw, x, y, w, h, texture->draw_driver_texture, r, g, b, a); }
