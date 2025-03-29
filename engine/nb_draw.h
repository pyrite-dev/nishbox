#ifndef __NB_DRAW_H__
#define __NB_DRAW_H__

#include <nb_macro.h>

/* External library */

/* NishBox */

/* Standard */

#ifdef NB_EXPOSE_DRAW
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

nb_draw_t* nb_draw_create(void);

#endif
