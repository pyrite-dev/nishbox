#define NE_EXPOSE_DRAW

#include <ne_pre.h>

/* External library */

/* Interface */
#include <ne_draw.h>

/* NishBox */
#include <ne_log.h>
#include <ne_draw_platform.h>
#include <ne_draw_driver.h>
#include <ne_graphic.h>

/* Standard */
#include <stdlib.h>
#include <string.h>
#include <math.h>

void ne_draw_begin(void) { ne_draw_platform_begin(); }

void ne_draw_end(void) { ne_draw_platform_end(); }

ne_draw_t* ne_draw_create(void) {
	ne_draw_t* draw = malloc(sizeof(*draw));
	memset(draw, 0, sizeof(*draw));
	draw->x	      = 0;
	draw->y	      = 0;
	draw->width   = 640;
	draw->height  = 480;
	draw->running = 0;
	ne_draw_platform_create(draw);
	if(draw->platform != NULL) {
		ne_function_log("Created drawing interface successfully", "");
		ne_draw_driver_init(draw);
		ne_draw_reshape(draw);
		draw->running = 1;

		draw->light[0] = 10.0;
		draw->light[1] = 10.0;
		draw->light[2] = 0.0;
		draw->light[3] = 1.0;

		draw->camera[0] = 0;
		draw->camera[1] = 10;
		draw->camera[2] = 0;

		draw->lookat[0] = 0;
		draw->lookat[1] = 0;
		draw->lookat[2] = 0;
	}
	return draw;
}

void ne_draw_reshape(ne_draw_t* draw) { ne_draw_driver_reshape(draw); }

/* Runs every frame */
void ne_draw_frame(ne_draw_t* draw) {
	ne_graphic_text(draw, 0, 0, 32, "test text", 255, 0, 0, 128);
	ne_graphic_text(draw, 8, 8, 32, "test text", 0, 255, 0, 128);
	ne_graphic_text(draw, 16, 16, 32, "test text", 0, 0, 255, 128);
}

int ne_draw_step(ne_draw_t* draw) {
	int ret = ne_draw_platform_step(draw);
	if(ret != 0) return ret;
	draw->close = 0;

	return 0;
}

void ne_draw_destroy(ne_draw_t* draw) {
	int i;
	if(draw->running) {
		ne_draw_driver_destroy(draw);
	}
	ne_draw_platform_destroy(draw);
	ne_function_log("Destroyed drawing interface", "");
}
