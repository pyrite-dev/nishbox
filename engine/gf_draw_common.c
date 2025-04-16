#define GF_EXPOSE_DRAW

#include <gf_pre.h>

/* External library */
#include <stb_image.h>

/* Interface */
#include <gf_draw.h>

/* Engine */
#include <gf_core.h>
#include <gf_log.h>
#include <gf_draw_platform.h>
#include <gf_draw_driver.h>
#include <gf_texture.h>
#include <gf_graphic.h>
#include <gf_font.h>
#include <gf_gui.h>

/* Standard */
#include <stdlib.h>
#include <string.h>
#include <math.h>

void gf_draw_begin(void) { gf_draw_platform_begin(); }

void gf_draw_end(void) { gf_draw_platform_end(); }

gf_texture_t* test_texture;

gf_draw_t* gf_draw_create(gf_engine_t* engine, const char* title) {
	gf_draw_t* draw = malloc(sizeof(*draw));
	memset(draw, 0, sizeof(*draw));
	draw->engine  = engine;
	draw->x	      = 0;
	draw->y	      = 0;
	draw->width   = 640;
	draw->height  = 480;
	draw->running = 0;
	draw->draw_3d = 0;
	strcpy(draw->title, title);
	draw->platform = gf_draw_platform_create(engine, draw);
	if(draw->platform != NULL) {
		int i;
		draw->driver = gf_draw_driver_create(engine, draw);
		gf_draw_reshape(draw);
		draw->running = 1;

		draw->light[0] = 0.0;
		draw->light[1] = 10.0;
		draw->light[2] = 0.0;
		draw->light[3] = 1.0;

		draw->camera[0] = 0;
		draw->camera[1] = 2;
		draw->camera[2] = 2;

		draw->lookat[0] = 0;
		draw->lookat[1] = 0;
		draw->lookat[2] = 0;

		draw->gui = gf_gui_create(engine, draw);
		if(1) {
			int	       w, h, c;
			unsigned char* d = stbi_load("texture/test.bmp", &w, &h, &c, 4);
			test_texture	 = gf_texture_create(draw, w, h, d);
			free(d);
		}

		for(i = 0; i < sizeof(gf_font) / sizeof(gf_font[0]); i++) {
			unsigned char* font = malloc(8 * 8 * 4);
			int	       j;
			for(j = 0; j < 8 * 8; j++) {
				unsigned char val = (gf_font[i][j / 8] >> (j % 8)) & 1 ? 255 : 0;
				font[j * 4 + 0]	  = val;
				font[j * 4 + 1]	  = val;
				font[j * 4 + 2]	  = val;
				font[j * 4 + 3]	  = val;
			}
			draw->font[i] = gf_texture_create(draw, 8, 8, font);
			free(font);
		}
		gf_log_function(engine, "Registered %d glyphs", sizeof(gf_font) / sizeof(gf_font[0]));
	} else {
		gf_draw_destroy(draw);
		draw = NULL;
	}
	return draw;
}

void gf_draw_reshape(gf_draw_t* draw) { gf_draw_driver_reshape(draw); }

/* Runs every frame */
void gf_draw_frame(gf_draw_t* draw) {
	gf_graphic_color_t color;
	color.r = color.g = color.b = color.a = 255;
	if(!draw->draw_3d) {
		gf_graphic_draw_texture_polygon(draw, test_texture, color, GF_GRAPHIC_3D, 4,
						/* clang-format off */
			0.0, 0.0,
			-1.0, 0.0, -1.0,

			0.0, 4.0,
			-1.0, 0.0, 1.0,

			4.0, 4.0,
			1.0, 0.0, 1.0,

			4.0, 0.0,
			1.0, 0.0, -1.0
						/* clang-format on */
		);
	}
}

int gf_draw_step(gf_draw_t* draw) {
	int ret = gf_draw_platform_step(draw);
	if(ret != 0) return ret;
	draw->close = 0;

	return 0;
}

void gf_draw_destroy(gf_draw_t* draw) {
	if(draw->running) {
		int i;
		for(i = 0; i < sizeof(gf_font) / sizeof(gf_font[0]); i++) {
			gf_texture_destroy(draw->font[i]);
		}
	}
	if(draw->driver != NULL) gf_draw_driver_destroy(draw->driver);
	if(draw->platform != NULL) gf_draw_platform_destroy(draw->platform);
	gf_log_function(draw->engine, "Destroyed drawing interface", "");
	free(draw);
}
