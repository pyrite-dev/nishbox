#define NB_EXPOSE_TEXTURE

#include <nb_pre.h>

/* External library */

/* Interface */
#include <nb_texture.h>

/* NishBox */
#include <nb_draw_driver.h>

/* Standard */
#include <stdlib.h>

nb_texture_t* nb_register_texture(nb_draw_t* draw, int width, int height, unsigned char* data) {
	nb_texture_t*		  texture   = malloc(sizeof(*texture));
	nb_draw_driver_texture_t* ddtexture = nb_draw_driver_register_texture(draw, width, height, data);
	if(ddtexture == NULL) {
		free(texture);
		return NULL;
	}
	texture->width		     = width;
	texture->height		     = height;
	texture->draw_driver_texture = ddtexture;
	return texture;
}

void nb_destroy_texture(nb_texture_t* texture) {
	nb_draw_driver_destroy_texture(texture->draw_driver_texture);
	free(texture);
}

void nb_draw_texture(nb_draw_t* draw, float x, float y, float w, float h, nb_texture_t* texture, float r, float g, float b, float a) { nb_draw_driver_draw_texture(draw, x, y, w, h, texture->draw_driver_texture, r, g, b, a); }
