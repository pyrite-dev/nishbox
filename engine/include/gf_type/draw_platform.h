/**
 * @file gf_type/draw_platform.h
 * @~english
 * @brief Type definitions related to platform-dependent part of drawing driver
 */

#ifndef __GF_TYPE_DRAW_PLATFORM_H__
#define __GF_TYPE_DRAW_PLATFORM_H__

#include <gf_pre.h>
#include <gf_macro.h>

#ifdef GF_EXPOSE_DRAW_PLATFORM
typedef struct gf_draw_platform_t gf_draw_platform_t;

/* External library */
#if defined(DRV_OPENGL)
#include <gf_opengl.h>
#elif defined(DRV_DIRECTX)
#include <gf_directx.h>
#endif

/* Engine */
#include <gf_type/core.h>

/* Standard */

#if defined(DRV_OPENGL)
#if defined(USE_GLX)
GF_DECLARE_TYPE(draw_platform, {
	gf_engine_t* engine;
	Display*     display;
	Window	     window;
	GLXContext   context;
	Atom	     wm_delete_window;
});
#elif defined(USE_WGL)
GF_DECLARE_TYPE(draw_platform, {
	gf_engine_t* engine;
	HINSTANCE    instance;
	HWND	     window;
	HDC	     dc;
	HGLRC	     glrc;
});
#elif defined(USE_RGFW)
GF_DECLARE_TYPE(draw_platform, {
	gf_engine_t* engine;
	RGFW_window* window;
});
#endif
#else
/**
 * @struct gf_draw_platform_t
 * @~english
 * @brief Platform-dependent part of drawing driver
 * @note Definition depends on the drawing driver and the platform, read the header file for definition
 */
GF_DECLARE_TYPE(draw_platform, {});
#endif
#else
typedef void gf_draw_platform_t;
#endif

#endif
