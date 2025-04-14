#ifndef __GF_TYPE_DRAW_PLATFORM_H__
#define __GF_TYPE_DRAW_PLATFORM_H__

#include <gf_pre.h>
#include <gf_macro.h>

#ifdef GF_EXPOSE_DRAW_PLATFORM
/* External library */
#ifdef DRV_OPENGL
#include <gf_opengl.h>
#endif

/* Engine */

/* Standard */

#ifdef DRV_OPENGL
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
#endif
#else
typedef void gf_draw_platform_t;
#endif

#endif
