#ifndef __NB_DRAW_H__
#define __NB_DRAW_H__

/* Interface */

/* NishBox */

/* External library */
#include <GL/gl.h>
#if defined(USE_GLX)
#include <X11/Xlib.h>
#include <GL/glx.h>
#elif defined(USE_WGL)
#include <windows.h>
#endif

/* Standard */

typedef struct nb_draw {
#if defined(USE_GLX)
	Display*   display;
	Window	   window;
	GLXContext context;
#elif defined(USE_WGL)
	HINSTANCE instance;
	HWND	  window;
	HDC	  dc;
	HGLRC	  glrc;
#endif
} nb_draw_t;

nb_draw_t* nb_draw_create(void);

#endif
