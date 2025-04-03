#define NB_EXPOSE_DRAW

#include "nb_pre.h"

/* External library */

/* Interface */
#include "nb_draw.h"

/* NishBox */
#include "nb_log.h"
#include "nb_draw_platform.h"
#include "nb_draw_driver.h"

/* Standard */
#include <stdlib.h>
#include <string.h>
#include <math.h>

void nb_draw_begin(void) { nb_draw_platform_begin(); }

void nb_draw_end(void) { nb_draw_platform_end(); }

nb_draw_t* nb_draw_create(void) {
	nb_draw_t* draw = malloc(sizeof(*draw));
	memset(draw, 0, sizeof(*draw));
	draw->x	      = 0;
	draw->y	      = 0;
	draw->width   = 640;
	draw->height  = 480;
	draw->running = 0;
	nb_draw_platform_create(draw);
	if(draw->platform != NULL) {
		nb_function_log("Created drawing interface successfully", "");
		nb_draw_driver_init(draw);
		nb_draw_reshape(draw);
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

void nb_draw_reshape(nb_draw_t* draw) { nb_draw_driver_reshape(draw); }

void nb_draw_begin_2d(nb_draw_t* draw) { nb_draw_driver_begin_2d(draw); }

void nb_draw_end_2d(nb_draw_t* draw) { nb_draw_driver_end_2d(draw); }

void nb_draw_frame(nb_draw_t* draw) {}

int nb_draw_step(nb_draw_t* draw) {
	int ret = nb_draw_platform_step(draw);
	if(ret != 0) return ret;
	draw->close = 0;

	return 0;
}

void nb_draw_destroy(nb_draw_t* draw) {
	int i;
	if(draw->running) {
		nb_draw_driver_destroy(draw);
	}
	nb_draw_platform_destroy(draw);
	nb_function_log("Destroyed drawing interface", "");
}
