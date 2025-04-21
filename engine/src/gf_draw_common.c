#define GF_EXPOSE_DRAW
#define GF_EXPOSE_CORE
#define GF_EXPOSE_CLIENT

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
#include <gf_audio.h>

/* Standard */
#include <stdlib.h>
#include <string.h>
#include <math.h>

void gf_draw_begin(void) { gf_draw_platform_begin(); }

void gf_draw_end(void) { gf_draw_platform_end(); }

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
	draw->font    = NULL;
	strcpy(draw->title, title);
	draw->platform = gf_draw_platform_create(engine, draw);
	if(draw->platform != NULL) {
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
	} else {
		gf_draw_destroy(draw);
		draw = NULL;
	}
	return draw;
}

void gf_draw_reshape(gf_draw_t* draw) { gf_draw_driver_reshape(draw); }

int made = 0;

void gf_button_callback(gf_engine_t* engine, gf_draw_t* draw, gf_gui_id_t id, int type) {
	if(type == GF_GUI_PRESS_EVENT) {
		gf_log_function(engine, "GUI component %d was pressed", id);
	}
}

/* Runs every frame */
void gf_draw_frame(gf_draw_t* draw) {
	gf_graphic_color_t color;
	color.r = color.g = color.b = color.a = 255;
	if(made == 0) {
		int i;
		gf_audio_resume(draw->engine->client->audio, gf_audio_load_file(draw->engine->client->audio, "base:/music/mikke-shine.xm"));
		made = 1;
		for(i = 0; i < 5; i++) {
			double	    p = 50;
			double	    s = 300 - i * p;
			gf_gui_id_t id;

			if(i > 0) {
				p = (s + p) / 2 - (s / 2);
			}

			id = gf_gui_create_button(draw->gui, p, p, s, s, "test");
			if(i > 0) {
				gf_gui_set_parent(draw->gui, id, id - 1);
			}
		}
	}
	if(draw->draw_3d) {
	}
	gf_gui_render(draw->gui);
}

int gf_draw_step(gf_draw_t* draw) {
	int ret = gf_draw_platform_step(draw);
	if(ret != 0) return ret;
	draw->close = 0;

	return 0;
}

void gf_draw_destroy(gf_draw_t* draw) {
	if(draw->font != NULL) {
		gf_font_destroy(draw->font);
	}
	if(draw->driver != NULL) gf_draw_driver_destroy(draw->driver);
	if(draw->platform != NULL) gf_draw_platform_destroy(draw->platform);
	gf_log_function(draw->engine, "Destroyed drawing interface", "");
	free(draw);
}

void gf_draw_set_input(gf_draw_t* draw, gf_input_t* input) { draw->input = input; }
