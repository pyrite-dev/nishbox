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
#include <GL/wgl.h>
#elif defined(USE_GLFW)
#include <GLFW/glfw3.h>
#endif

/* NishBox */

/* Standard */

NB_DECLARE_TYPE(draw_platform, {
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
#elif defined(USE_GLFW)
	GLFWwindow* window;
#endif
});
#else
typedef void nb_draw_platform_t;
#endif

#endif
