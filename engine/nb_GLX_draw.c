#define NB_EXPOSE_DRAW_PLATFORM
#define NB_EXPOSE_DRAW

#include "nb_pre.h"

/* External library */
#include <GL/gl.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <GL/glx.h>
#include <GL/glxext.h>

/* Interface */
#include "nb_draw_platform.h"

/* NishBox */
#include "nb_log.h"
#include "nb_draw.h"

/* Standard */
#include <string.h>
#include <stdlib.h>

#ifndef GLX_MESA_swap_control
#define GLX_MESA_swap_control 1
typedef int (*PFNGLXGETSWAPINTERVALMESAPROC)(void);
typedef void (*PFNGLXSWAPINTERVALMESAPROC)(int);
#endif

#ifndef GLX_EXT_swap_control
#define GLX_EXT_swap_control 1
typedef void (*PFNGLXSWAPINTERVALEXTPROC)(Display*, GLXDrawable, int);
#endif

#ifndef GLX_SGI_swap_control
#define GLX_SGI_swap_control 1
typedef void (*PFNGLXSWAPINTERVALSGIPROC)(int);
#endif

void nb_draw_platform_begin(void) {}
void nb_draw_platform_end(void) {}

int nb_draw_platform_has_extension(nb_draw_t* draw, const char* query) {
	const char* ext = NULL;
	const char* ptr;
	const int   len = strlen(query);

	glXMakeCurrent(draw->platform->display, draw->platform->window, draw->platform->context);

	ext = glXQueryExtensionsString(draw->platform->display, DefaultScreen(draw->platform->display));
	ptr = strstr(ext, query);
	return ((ptr != NULL) && ((ptr[len] == ' ') || (ptr[len] == '\0')));
}

void nb_draw_platform_create(nb_draw_t* draw) {
	int		     i = 0;
	int		     attribs[64];
	int		     screen;
	Window		     root;
	XVisualInfo*	     visual;
	XSetWindowAttributes attr;
	XSizeHints	     hints;
	int		     interval = 0;

	draw->platform = malloc(sizeof(*draw->platform));
	memset(draw->platform, 0, sizeof(*draw->platform));

	draw->platform->display = XOpenDisplay(NULL);
	if(draw->platform->display == NULL) {
		nb_function_log("Failed to open display", "");
		nb_draw_destroy(draw);
		return;
	}
	attribs[i++] = GLX_RGBA;
	attribs[i++] = GLX_DOUBLEBUFFER;

	attribs[i++] = GLX_RED_SIZE;
	attribs[i++] = 1;
	attribs[i++] = GLX_GREEN_SIZE;
	attribs[i++] = 1;
	attribs[i++] = GLX_BLUE_SIZE;
	attribs[i++] = 1;
	attribs[i++] = GLX_DEPTH_SIZE;
	attribs[i++] = 1;

	attribs[i++] = None;

	screen = DefaultScreen(draw->platform->display);
	root   = RootWindow(draw->platform->display, screen);

	visual = glXChooseVisual(draw->platform->display, screen, attribs);
	if(visual == NULL) {
		nb_function_log("Failed to get visual", "");
		nb_draw_destroy(draw);
		return;
	}

	attr.colormap	       = XCreateColormap(draw->platform->display, root, visual->visual, AllocNone);
	attr.event_mask	       = StructureNotifyMask | ExposureMask;
	draw->platform->window = XCreateWindow(draw->platform->display, root, draw->width, draw->height, draw->width, draw->height, 0, visual->depth, InputOutput, visual->visual, CWColormap | CWEventMask, &attr);

	hints.x	     = draw->x;
	hints.y	     = draw->y;
	hints.width  = draw->width;
	hints.height = draw->height;
	hints.flags  = USSize | USPosition;
	XSetNormalHints(draw->platform->display, draw->platform->window, &hints);
	XSetStandardProperties(draw->platform->display, draw->platform->window, "NishBox (GLX)", "NishBox", None, (char**)NULL, 0, &hints);

	draw->platform->wm_delete_window = XInternAtom(draw->platform->display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(draw->platform->display, draw->platform->window, &draw->platform->wm_delete_window, 1);

	draw->platform->context = glXCreateContext(draw->platform->display, visual, NULL, True);
	if(draw->platform->context == NULL) {
		XFree(visual);
		nb_function_log("Failed to get OpenGL context", "");
		nb_draw_destroy(draw);
		return;
	}

	XFree(visual);

	XMapWindow(draw->platform->display, draw->platform->window);
	glXMakeCurrent(draw->platform->display, draw->platform->window, draw->platform->context);

#if defined(GLX_EXT_swap_control)
	if(nb_draw_platform_has_extension(draw, "GLX_EXT_swap_control")) {
		unsigned int		  tmp  = -1;
		PFNGLXSWAPINTERVALEXTPROC proc = (PFNGLXSWAPINTERVALEXTPROC)glXGetProcAddressARB("glXSwapIntervalEXT");
		if(proc != NULL) {
			proc(draw->platform->display, draw->platform->window, 1);
		}
		glXQueryDrawable(draw->platform->display, draw->platform->window, GLX_SWAP_INTERVAL_EXT, &tmp);
		interval = tmp;
	} else
#endif
	    if(nb_draw_platform_has_extension(draw, "GLX_MESA_swap_control")) {
		PFNGLXGETSWAPINTERVALMESAPROC proc  = (PFNGLXGETSWAPINTERVALMESAPROC)glXGetProcAddressARB("glXGetSwapIntervalMESA");
		PFNGLXSWAPINTERVALMESAPROC    proc2 = (PFNGLXSWAPINTERVALMESAPROC)glXGetProcAddressARB("glXSwapIntervalMESA");
		if(proc2 != NULL) {
			proc2(1);
		}
		interval = proc();
	} else if(nb_draw_platform_has_extension(draw, "GLX_SGI_swap_control")) {
		PFNGLXSWAPINTERVALSGIPROC proc = (PFNGLXSWAPINTERVALSGIPROC)glXGetProcAddressARB("glXSwapIntervalSGI");
		proc(1);
		interval = 1;
	}
	if(interval > 0) {
		nb_function_log("Enabled VSync", "");
	}
}

int nb_draw_platform_step(nb_draw_t* draw) {
	int ret = 0;
	glXMakeCurrent(draw->platform->display, draw->platform->window, draw->platform->context);
	while(XPending(draw->platform->display) > 0) {
		XEvent event;
		XNextEvent(draw->platform->display, &event);
		if(event.type == Expose) {
			break;
		} else if(event.type == ConfigureNotify) {
			draw->x	     = event.xconfigure.x;
			draw->y	     = event.xconfigure.y;
			draw->width  = event.xconfigure.width;
			draw->height = event.xconfigure.height;
			glXMakeCurrent(draw->platform->display, draw->platform->window, draw->platform->context);
			nb_draw_reshape(draw);
		} else if(event.type == ClientMessage) {
			if(event.xclient.data.l[0] == draw->platform->wm_delete_window) {
				draw->close = 1;
				break;
			}
		}
	}
	if(ret == 0) {
		nb_draw_frame(draw);

		glFlush();
		glXSwapBuffers(draw->platform->display, draw->platform->window);
	}
	return ret;
}

void nb_draw_platform_destroy(nb_draw_t* draw) {
	if(draw->platform->context != NULL) {
		glXMakeCurrent(draw->platform->display, None, NULL);
		glXDestroyContext(draw->platform->display, draw->platform->context);
	}
	if(draw->platform->display != NULL) {
		XDestroyWindow(draw->platform->display, draw->platform->window);
		XCloseDisplay(draw->platform->display);
	}
}
