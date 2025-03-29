#define NB_EXPOSE_DRAW

/* External library */
#include <GL/gl.h>
#if defined(USE_GLX)
#include <X11/Xlib.h>
#include <GL/glx.h>
#elif defined(USE_WGL)
#include <windows.h>
#endif

/* Interface */
#include "nb_draw.h"

/* NishBox */

/* Standard */
#include <stdlib.h>

nb_draw_t* nb_draw_create(void) {
	nb_draw_t* draw = malloc(sizeof(*draw));
#if defined(USE_GLX)
#elif defined(USE_WGL)
#endif
	return draw;
}
