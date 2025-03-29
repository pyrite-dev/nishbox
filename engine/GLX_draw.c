#define NB_EXPOSE_DRAW_PLATFORM

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

int _nb_draw_has_glx_extension(nb_draw_t* draw, const char* query) {
	const char* glx_ext = NULL;
	const char* ptr;
	const int   len = strlen(query);
	if(glx_ext == NULL) {
		glx_ext = glXQueryExtensionsString(draw->display, DefaultScreen(draw->display));
	}
	ptr = strstr(glx_ext, query);
	return ((ptr != NULL) && ((ptr[len] == ' ') || (ptr[len] == '\0')));
}

void _nb_draw_create(nb_draw_t** pdraw) {
	nb_draw_t*	     draw = *pdraw;
	int		     i	  = 0;
	int		     attribs[64];
	int		     screen;
	Window		     root;
	XVisualInfo*	     visual;
	XSetWindowAttributes attr;
	XSizeHints	     hints;
	int		     interval = 0;
	draw->display		      = XOpenDisplay(NULL);
	if(draw->display == NULL) {
		nb_function_log("Failed to open display", "");
		nb_draw_destroy(draw);
		*pdraw = NULL;
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

	screen = DefaultScreen(draw->display);
	root   = RootWindow(draw->display, screen);

	visual = glXChooseVisual(draw->display, screen, attribs);
	if(visual == NULL) {
		nb_function_log("Failed to get visual", "");
		nb_draw_destroy(draw);
		*pdraw = NULL;
		return;
	}

	attr.colormap	= XCreateColormap(draw->display, root, visual->visual, AllocNone);
	attr.event_mask = StructureNotifyMask | ExposureMask;
	draw->window	= XCreateWindow(draw->display, root, draw->width, draw->height, draw->width, draw->height, 0, visual->depth, InputOutput, visual->visual, CWColormap | CWEventMask, &attr);

	hints.x	     = draw->x;
	hints.y	     = draw->y;
	hints.width  = draw->width;
	hints.height = draw->height;
	hints.flags  = USSize | USPosition;
	XSetNormalHints(draw->display, draw->window, &hints);
	XSetStandardProperties(draw->display, draw->window, "NishBox", "NishBox", None, (char**)NULL, 0, &hints);

	draw->wm_delete_window = XInternAtom(draw->display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(draw->display, draw->window, &draw->wm_delete_window, 1);

	draw->context = glXCreateContext(draw->display, visual, NULL, True);
	if(draw->context == NULL) {
		XFree(visual);
		nb_function_log("Failed to get OpenGL context", "");
		nb_draw_destroy(draw);
		*pdraw = NULL;
		return;
	}

	XFree(visual);

	XMapWindow(draw->display, draw->window);
	glXMakeCurrent(draw->display, draw->window, draw->context);

#if defined(GLX_EXT_swap_control)
	if(_nb_draw_has_glx_extension(draw, "GLX_EXT_swap_control")) {
		unsigned int		  tmp  = -1;
		PFNGLXSWAPINTERVALEXTPROC proc = (PFNGLXSWAPINTERVALEXTPROC)glXGetProcAddressARB("glXSwapIntervalEXT");
		if(proc != NULL) {
			proc(draw->display, draw->window, 1);
		}
		glXQueryDrawable(draw->display, draw->window, GLX_SWAP_INTERVAL_EXT, &tmp);
		interval = tmp;
	} else
#endif
	    if(_nb_draw_has_glx_extension(draw, "GLX_MESA_swap_control")) {
		PFNGLXGETSWAPINTERVALMESAPROC proc  = (PFNGLXGETSWAPINTERVALMESAPROC)glXGetProcAddressARB("glXGetSwapIntervalMESA");
		PFNGLXSWAPINTERVALMESAPROC    proc2 = (PFNGLXSWAPINTERVALMESAPROC)glXGetProcAddressARB("glXSwapIntervalMESA");
		if(proc2 != NULL) {
			proc2(1);
		}
		interval = proc();
	} else if(_nb_draw_has_glx_extension(draw, "GLX_SGI_swap_control")) {
		PFNGLXSWAPINTERVALSGIPROC proc = (PFNGLXSWAPINTERVALSGIPROC)glXGetProcAddressARB("glXSwapIntervalSGI");
		proc(1);
		interval = 1;
	}
	if(interval > 0) {
		nb_function_log("Enabled VSync", "");
	}
}

int _nb_draw_step(nb_draw_t* draw) {
	int ret = 0;
	glXMakeCurrent(draw->display, draw->window, draw->context);
	while(XPending(draw->display) > 0) {
		XEvent event;
		XNextEvent(draw->display, &event);
		if(event.type == Expose) {
			break;
		} else if(event.type == ConfigureNotify) {
			draw->x	     = event.xconfigure.x;
			draw->y	     = event.xconfigure.y;
			draw->width  = event.xconfigure.width;
			draw->height = event.xconfigure.height;
			nb_draw_reshape(draw);
		} else if(event.type == ClientMessage) {
			if(event.xclient.data.l[0] == draw->wm_delete_window) {
				draw->close = 1;
				break;
			}
		}
	}
	if(ret == 0) {
		nb_draw_frame(draw);

		glFlush();
		glXSwapBuffers(draw->display, draw->window);
	}
	return ret;
}

void _nb_draw_init_opengl(nb_draw_t* draw) {}

void _nb_draw_destroy(nb_draw_t* draw) {
	if(draw->context != NULL) {
		glXMakeCurrent(draw->display, None, NULL);
		glXDestroyContext(draw->display, draw->context);
	}
	if(draw->display != NULL) {
		XDestroyWindow(draw->display, draw->window);
		XCloseDisplay(draw->display);
	}
}
