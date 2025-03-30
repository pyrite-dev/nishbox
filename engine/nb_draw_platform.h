#ifndef __NB_DRAW_PLATFORM_H__
#define __NB_DRAW_PLATFORM_H__

#include <nb_pre.h>
#include <nb_macro.h>

/* External library */
#ifdef NB_EXPOSE_DRAW_PLATFORM
#if defined(USE_GLX)
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <GL/glx.h>
#elif defined(USE_WGL)
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
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
	int	    close;
	int	    x;
	int	    y;
	int	    width;
	int	    height;
	int	    running;
	GLuint	    font[128];
	GLfloat	    light[4];
	GLfloat	    lookat[3];
	GLfloat	    camera[3];
	GLUquadric* quadric;
} nb_draw_t;
#else
typedef void nb_draw_t;
#endif

void _nb_draw_create(nb_draw_t** pdraw);
void _nb_draw_destroy(nb_draw_t* draw);
int  _nb_draw_step(nb_draw_t* draw);
int  _nb_draw_has_extension(nb_draw_t* draw, const char* query);

#endif
