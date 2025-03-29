#define NB_EXPOSE_DRAW_PLATFORM

/* External library */
#include <X11/Xlib.h>
#include <GL/glx.h>

/* Interface */
#include "nb_draw_platform.h"

/* NishBox */
#include "nb_log.h"

/* Standard */

void _nb_draw_create(nb_draw_t** pdraw) {
	nb_draw_t*   draw = *pdraw;
	int	     i;
	int	     attribs[64];
	int	     screen;
	Window	     root;
	XVisualInfo* visual;
	draw->display = XOpenDisplay(NULL);
	if(draw->display == NULL) {
		nb_function_log("Failed to open display", "");
		_nb_draw_destroy(draw);
		*pdraw = NULL;
		return;
	}
	attribs[i++] = GLX_RGBA;
	attribs[i++] = GLX_DOUBLEBUFFER;

	attribs[i++] = GLX_RED_SIZE;
	attribs[i++] = 1;
	attribs[i++] = GLX_GREEN_SIZE;
	attribs[i++] = 1;
	attribs[i++] = GLX_BLUE_SIZE;
	attribs[i++] = 1;
	attribs[i++] = GLX_DEPTH_SIZE;
	attribs[i++] = 1;

	attribs[i++] = None;

	screen = DefaultScreen(draw->display);
	root   = RootWindow(draw->display, screen);

	visual = glXChooseVisual(draw->display, screen, attribs);
	if(visual == NULL) {
		nb_function_log("Failed to get a visual", "");
		_nb_draw_destroy(draw);
	}
	XFree(visual);
}

void _nb_draw_destroy(nb_draw_t* draw) {
	if(draw->display != NULL) XCloseDisplay(draw->display);
}
