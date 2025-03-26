#ifndef __NB_DRAW_H__
#define __NB_DRAW_H__

#include <GL/gl.h>
#if defined(USE_GLX)
#include <X11/Xlib.h>
#include <GL/glx.h>
#include <GL/glxext.h>
#elif defined(USE_WGL)
#endif

typedef struct nb_draw {
#if defined(USE_GLX)
	Display* display;
	Window window;
	GLXContext context;
#elif defined(USE_WGL)
#endif
} nb_draw_t;

#endif
