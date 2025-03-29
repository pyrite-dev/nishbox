#define NB_EXPOSE_DRAW
#define NB_EXPOSE_DRAW_PLATFORM

/* External library */
#include <GL/gl.h>

/* Interface */
#include "nb_draw.h"

/* NishBox */
#include "nb_log.h"
#include "nb_draw_platform.h"

/* Standard */
#include <stdlib.h>
#include <string.h>

nb_draw_t* nb_draw_create(void) {
	nb_draw_t* draw = malloc(sizeof(*draw));
	memset(draw, 0, sizeof(*draw));
	_nb_draw_create(&draw);
	if(draw != NULL) {
		nb_function_log("Created drawing interface successfully", "");
	}
	return draw;
}

void nb_draw_destroy(nb_draw_t* draw) { _nb_draw_destroy(draw); }
