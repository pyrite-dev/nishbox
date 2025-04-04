#ifndef __NB_TYPE_DRAW_PLATFORM_H__
#define __NB_TYPE_DRAW_PLATFORM_H__

#include <nb_pre.h>
#include <nb_macro.h>

#ifdef NB_EXPOSE_DRAW_PLATFORM
/* External library */
#include <GL/gl.h>
#include <GL/glu.h>
#if defined(USE_GLX)
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <GL/glx.h>
#elif defined(USE_WGL)
/* Should require nothing... for now? */
#elif defined(USE_GLFW)
#include <GLFW/glfw3.h>
#endif

/* NishBox */

/* Standard */

#if defined(USE_GLX)
NB_DECLARE_TYPE(draw_platform, {
	Display*   display;
	Window	   window;
	GLXContext context;
	Atom	   wm_delete_window;
});
#elif defined(USE_WGL)
NB_DECLARE_TYPE(draw_platform, {
	HINSTANCE instance;
	HWND	  window;
	HDC	  dc;
	HGLRC	  glrc;
});
#elif defined(USE_GLFW)
NB_DECLARE_TYPE(draw_platform, { GLFWwindow* window; });
#endif
#else
typedef void nb_draw_platform_t;
#endif

#endif
