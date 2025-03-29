#define NB_EXPOSE_DRAW_PLATFORM

/* External library */
#include <windows.h>

/* Interface */
#include "nb_draw_platform.h"

/* NishBox */
#include "nb_log.h"

/* Standard */

void _nb_draw_create(nb_draw_t** pdraw) { nb_draw_t* draw = *pdraw; }

void _nb_draw_destroy(nb_draw_t* draw) {}
