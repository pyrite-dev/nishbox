#ifndef __GF_TYPE_DRAW_PLATFORM_H__
#define __GF_TYPE_DRAW_PLATFORM_H__

#include <gf_pre.h>
#include <gf_macro.h>

#ifdef GF_EXPOSE_DRAW_PLATFORM
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

/* Engine */

/* Standard */

#if defined(USE_GLX)
GF_DECLARE_TYPE(draw_platform, {
	Display*   display;
	Window	   window;
	GLXContext context;
	Atom	   wm_delete_window;
});
#elif defined(USE_WGL)
GF_DECLARE_TYPE(draw_platform, {
	HINSTANCE instance;
	HWND	  window;
	HDC	  dc;
	HGLRC	  glrc;
});
#elif defined(USE_GLFW)
GF_DECLARE_TYPE(draw_platform, { GLFWwindow* window; });
#endif
#else
typedef void gf_draw_platform_t;
#endif

#endif
