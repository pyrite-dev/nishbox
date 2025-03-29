#ifndef __NB_DRAW_PLATFORM_H__
#define __NB_DRAW_PLATFORM_H__

#include <nb_macro.h>

/* External library */
#ifdef NB_EXPOSE_DRAW_PLATFORM
#include <GL/gl.h>
#if defined(USE_GLX)
#include <X11/Xlib.h>
#include <X11/Xatom.h>
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
	Atom	   wm_delete_window;
#elif defined(USE_WGL)
	HINSTANCE instance;
	HWND	  window;
	HDC	  dc;
	HGLRC	  glrc;
#endif
	int    close;
	int    x;
	int    y;
	int    width;
	int    height;
	GLuint font[128];
} nb_draw_t;
#else
typedef void nb_draw_t;
#endif

void _nb_draw_create(nb_draw_t** pdraw);
void _nb_draw_destroy(nb_draw_t* draw);
int  _nb_draw_step(nb_draw_t* draw);

#endif
