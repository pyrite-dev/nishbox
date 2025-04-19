#define GF_EXPOSE_DRAW_DRIVER
#define GF_EXPOSE_DRAW
#define GF_EXPOSE_TEXTURE

#include <gf_pre.h>

/* External library */
#include <gf_directx.h>

/* Interface */
#include <gf_draw_driver.h>

/* Engine */
#include <gf_draw_platform.h>
#include <gf_texture.h>
#include <gf_draw.h>
#include <gf_log.h>
#include <gf_math.h>
#include <gf_graphic.h>

/* Standard */
#include <stdlib.h>
#include <string.h>

gf_draw_driver_texture_t* gf_draw_driver_register_texture(gf_draw_t* draw, int width, int height, int* iwidth, int* iheight, unsigned char* data) {
	/* TODO: Implement this */
	return NULL;
}

void gf_draw_driver_destroy_texture(gf_draw_driver_texture_t* t) {
	/* TODO: Implement this */
	free(t);
}

gf_draw_driver_t* gf_draw_driver_create(gf_engine_t* engine, gf_draw_t* draw) {
	gf_draw_driver_t* draw_driver = malloc(sizeof(*draw_driver));
	memset(draw_driver, 0, sizeof(*draw_driver));
	draw_driver->engine = engine;

	/* TODO: Implement this */

	return draw_driver;
}

int gf_draw_driver_has_extension(gf_draw_t* draw, const char* query) { return 0; }

void gf_draw_driver_reshape(gf_draw_t* draw) { /* TODO: Implement this */ }

void gf_draw_driver_begin_texture_2d(gf_draw_t* draw, gf_texture_t* texture) { /* TODO: Implement this */ }

void gf_draw_driver_end_texture_2d(gf_draw_t* draw) { /* TODO: Implement this */ }

void gf_draw_driver_set_color(gf_draw_t* draw, gf_graphic_color_t color) { /* TODO: Implement this */ }

void gf_draw_driver_destroy(gf_draw_driver_t* driver) {
	/* TODO: Implement this */
	gf_log_function(driver->engine, "Destroyed drawing driver", "");
	free(driver);
}

void gf_draw_driver_before(gf_draw_t* draw) {
	/* TODO: Remove if needed, needed at least for OpenGL */
	gf_draw_driver_reshape(draw);

	/* TODO: Remove if needed, needed at least for OpenGL */
	gf_graphic_set_camera(draw);

	gf_graphic_clear(draw);
}

void gf_draw_driver_after(gf_draw_t* draw) {}
