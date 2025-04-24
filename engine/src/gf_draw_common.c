#include "gf_gui_component.h"
#include "gf_type/gui.h"
#define GF_EXPOSE_DRAW
#define GF_EXPOSE_CORE
#define GF_EXPOSE_CLIENT

#include <gf_pre.h>

/* External library */
#include <stb_ds.h>
#include <stb_image.h>

/* Interface */
#include <gf_draw.h>

/* Engine */
#include <gf_prop.h>
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

void gf_draw_begin(void) { gf_draw_platform_begin(); }

void gf_draw_end(void) { gf_draw_platform_end(); }

gf_draw_t* gf_draw_create(gf_engine_t* engine, const char* title) {
	gf_draw_t* draw = malloc(sizeof(*draw));
	memset(draw, 0, sizeof(*draw));
	draw->engine  = engine;
	draw->x	      = 0;
	draw->y	      = 0;
	draw->width   = 800;
	draw->height  = 600;
	draw->running = 0;
	draw->draw_3d = 0;
	draw->font    = NULL;
	draw->input   = NULL;
	draw->clip    = NULL;
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

/* Runs every frame */
void gf_draw_frame(gf_draw_t* draw) {
	gf_graphic_clear(draw);
	if(draw->draw_3d) {
	}
	gf_gui_render(draw->gui);
}

void gf_draw_close_yes(gf_engine_t* engine, gf_draw_t* draw, gf_gui_id_t id, int type) { draw->close = 2; }

void gf_draw_close_no(gf_engine_t* engine, gf_draw_t* draw, gf_gui_id_t id, int type) {
	gf_gui_id_t frame  = gf_gui_get_parent(draw->gui, id);
	gf_gui_id_t window = gf_gui_get_parent(draw->gui, frame);
	if(type == GF_GUI_PRESS_EVENT) {
		gf_gui_destroy_id(draw->gui, window);
	}
}

int gf_draw_step(gf_draw_t* draw) {
	int ret = gf_draw_platform_step(draw);
	if(ret != 0) return ret;
	if(draw->close == 1) {
		gf_gui_id_t window;
		gf_gui_id_t yes;
		gf_gui_id_t no;

		double w    = 600;
		double h    = 200;
		double bh   = 25;
		draw->close = 0;

		window = gf_gui_create_window(draw->gui, (double)draw->width / 2 - w / 2, (double)draw->height / 2 - h / 2, w, h);
		gf_gui_set_text(draw->gui, window, "Confirm");

		yes = gf_gui_create_button(draw->gui, -5.0 - bh * 2.5, -0.0, bh * 2.5, bh);
		gf_gui_set_text(draw->gui, yes, "Yes");
		gf_gui_set_callback(draw->gui, yes, gf_draw_close_yes);
		gf_gui_set_parent(draw->gui, yes, gf_gui_get_prop_id(draw->gui, window, "frame"));

		no = gf_gui_create_button(draw->gui, -0.0, -0.0, bh * 2.5, bh);
		gf_gui_set_text(draw->gui, no, "No");
		gf_gui_set_callback(draw->gui, no, gf_draw_close_no);
		gf_gui_set_parent(draw->gui, no, gf_gui_get_prop_id(draw->gui, window, "frame"));

		gf_gui_set_text(draw->gui, gf_gui_get_prop_id(draw->gui, window, "frame"), "Are you sure you want to quit?");

		gf_gui_sort_component(draw->gui);
	}

	return draw->close;
}

void gf_draw_destroy(gf_draw_t* draw) {
	if(draw->font != NULL) {
		gf_font_destroy(draw->font);
	}
	if(draw->clip != NULL) {
		arrfree(draw->clip);
		draw->clip = NULL;
	}
	if(draw->driver != NULL) gf_draw_driver_destroy(draw->driver);
	if(draw->platform != NULL) gf_draw_platform_destroy(draw->platform);
	gf_log_function(draw->engine, "Destroyed drawing interface", "");
	free(draw);
}

void gf_draw_set_input(gf_draw_t* draw, gf_input_t* input) { draw->input = input; }
