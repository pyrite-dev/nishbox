#ifndef __NB_DRAW_PLATFORM_H__
#define __NB_DRAW_PLATFORM_H__

#include <nb_macro.h>

/* External library */
#ifdef NB_EXPOSE_DRAW_PLATFORM
#if defined(USE_GLX)
#include <X11/Xlib.h>
#include <GL/glx.h>
#elif defined(USE_WGL)
#include <windows.h>
#endif
#endif

/* NishBox */

/* Standard */

#ifdef NB_EXPOSE_DRAW_PLATFORM
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
#else
typedef void nb_draw_t;
#endif

void _nb_draw_create(nb_draw_t** pdraw);
void _nb_draw_destroy(nb_draw_t* draw);

#endif
