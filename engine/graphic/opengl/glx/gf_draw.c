#define GF_EXPOSE_DRAW_PLATFORM
#define GF_EXPOSE_DRAW
#define GF_EXPOSE_INPUT

#include <gf_pre.h>

/* External library */
#include <gf_opengl.h>

/* Interface */
#include <gf_draw_platform.h>

/* Engine */
#include <gf_draw_driver.h>
#include <gf_input.h>
#include <gf_log.h>
#include <gf_draw.h>

/* Standard */
#include <string.h>
#include <stdlib.h>

#ifdef DO_SWAP_INTERVAL
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
#endif

void gf_draw_platform_begin(void) {}
void gf_draw_platform_end(void) {}

int gf_draw_platform_has_extension(gf_draw_t* draw, const char* query) {
	const char* ext = NULL;
	const char* ptr;
	const int   len = strlen(query);

	glXMakeCurrent(draw->platform->display, draw->platform->window, draw->platform->context);

	ext = glXQueryExtensionsString(draw->platform->display, DefaultScreen(draw->platform->display));
	ptr = strstr(ext, query);
	return ((ptr != NULL) && ((ptr[len] == ' ') || (ptr[len] == '\0')));
}

gf_draw_platform_t* gf_draw_platform_create(gf_engine_t* engine, gf_draw_t* draw) {
	int		     i = 0;
	int		     attribs[64];
	int		     screen;
	Window		     root;
	XVisualInfo*	     visual;
	XSetWindowAttributes attr;
	XSizeHints	     hints;
	int		     interval = 0;
	gf_draw_platform_t*  platform = malloc(sizeof(*platform));
	memset(platform, 0, sizeof(*platform));
	platform->engine = engine;

	platform->display = XOpenDisplay(NULL);
	if(platform->display == NULL) {
		gf_log_function(engine, "Failed to open display", "");
		gf_draw_platform_destroy(platform);
		return NULL;
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

	screen = DefaultScreen(platform->display);
	root   = RootWindow(platform->display, screen);

	visual = glXChooseVisual(platform->display, screen, attribs);
	if(visual == NULL) {
		gf_log_function(engine, "Failed to get visual", "");
		gf_draw_platform_destroy(platform);
		return NULL;
	}

	attr.colormap	 = XCreateColormap(platform->display, root, visual->visual, AllocNone);
	attr.event_mask	 = StructureNotifyMask | ExposureMask | PointerMotionMask | ButtonPressMask | ButtonReleaseMask;
	platform->window = XCreateWindow(platform->display, root, draw->width, draw->height, draw->width, draw->height, 0, visual->depth, InputOutput, visual->visual, CWColormap | CWEventMask, &attr);

	hints.x	     = draw->x;
	hints.y	     = draw->y;
	hints.width  = draw->width;
	hints.height = draw->height;
	hints.flags  = USSize | USPosition;
	XSetNormalHints(platform->display, platform->window, &hints);
	XSetStandardProperties(platform->display, platform->window, draw->title, "GoldFish", None, (char**)NULL, 0, &hints);

	platform->wm_delete_window = XInternAtom(platform->display, "WM_DELETE_WINDOW", False);
	XSetWMProtocols(platform->display, platform->window, &platform->wm_delete_window, 1);

	platform->context = glXCreateContext(platform->display, visual, NULL, True);
	if(platform->context == NULL) {
		XFree(visual);
		gf_log_function(engine, "Failed to get OpenGL context", "");
		gf_draw_platform_destroy(platform);
		return NULL;
	}

	XFree(visual);

	XMapWindow(platform->display, platform->window);
	glXMakeCurrent(platform->display, platform->window, platform->context);

#ifdef DO_SWAP_INTERVAL
	if(gf_draw_platform_has_extension(draw, "GLX_EXT_swap_control")) {
		unsigned int		  tmp  = -1;
		PFNGLXSWAPINTERVALEXTPROC proc = (PFNGLXSWAPINTERVALEXTPROC)glXGetProcAddressARB("glXSwapIntervalEXT");
		if(proc != NULL) {
			proc(platform->display, platform->window, 1);
		}
		glXQueryDrawable(platform->display, platform->window, GLX_SWAP_INTERVAL_EXT, &tmp);
		interval = tmp;
	} else if(gf_draw_platform_has_extension(draw, "GLX_MESA_swap_control")) {
		PFNGLXGETSWAPINTERVALMESAPROC proc  = (PFNGLXGETSWAPINTERVALMESAPROC)glXGetProcAddressARB("glXGetSwapIntervalMESA");
		PFNGLXSWAPINTERVALMESAPROC    proc2 = (PFNGLXSWAPINTERVALMESAPROC)glXGetProcAddressARB("glXSwapIntervalMESA");
		if(proc2 != NULL) {
			proc2(1);
		}
		interval = proc();
	} else if(gf_draw_platform_has_extension(draw, "GLX_SGI_swap_control")) {
		PFNGLXSWAPINTERVALSGIPROC proc = (PFNGLXSWAPINTERVALSGIPROC)glXGetProcAddressARB("glXSwapIntervalSGI");
		proc(1);
		interval = 1;
	}
	if(interval > 0) {
		gf_log_function(engine, "Enabled VSync", "");
	}
#endif
	return platform;
}

int gf_draw_platform_step(gf_draw_t* draw) {
	int ret = 0;
	glXMakeCurrent(draw->platform->display, draw->platform->window, draw->platform->context);
	while(XPending(draw->platform->display) > 0) {
		XEvent event;
		XNextEvent(draw->platform->display, &event);
		if(event.type == Expose) {
			break;
		} else if(event.type == MotionNotify) {
			if(draw->input != NULL) {
				draw->input->mouse_x = event.xmotion.x;
				draw->input->mouse_y = event.xmotion.y;
			}
		} else if(event.type == ConfigureNotify) {
			draw->x	     = event.xconfigure.x;
			draw->y	     = event.xconfigure.y;
			draw->width  = event.xconfigure.width;
			draw->height = event.xconfigure.height;
			glXMakeCurrent(draw->platform->display, draw->platform->window, draw->platform->context);
			gf_draw_reshape(draw);
		} else if(event.type == ButtonPress) {
			if(draw->input != NULL) {
				if(event.xbutton.button == Button1) draw->input->mouse_flag |= GF_INPUT_MOUSE_LEFT_MASK;
				if(event.xbutton.button == Button2) draw->input->mouse_flag |= GF_INPUT_MOUSE_MIDDLE_MASK;
				if(event.xbutton.button == Button3) draw->input->mouse_flag |= GF_INPUT_MOUSE_RIGHT_MASK;
			}
		} else if(event.type == ButtonRelease) {
			if(draw->input != NULL) {
				if(event.xbutton.button == Button1) draw->input->mouse_flag ^= GF_INPUT_MOUSE_LEFT_MASK;
				if(event.xbutton.button == Button2) draw->input->mouse_flag ^= GF_INPUT_MOUSE_MIDDLE_MASK;
				if(event.xbutton.button == Button3) draw->input->mouse_flag ^= GF_INPUT_MOUSE_RIGHT_MASK;
			}
		} else if(event.type == ClientMessage) {
			if(event.xclient.data.l[0] == draw->platform->wm_delete_window) {
				draw->close = 1;
				break;
			}
		}
	}
	if(ret == 0) {
		gf_draw_driver_before(draw);
		gf_draw_frame(draw);
		gf_draw_driver_after(draw);

		glXSwapBuffers(draw->platform->display, draw->platform->window);
	}
	return ret;
}

void gf_draw_platform_destroy(gf_draw_platform_t* platform) {
	if(platform->context != NULL) {
		glXMakeCurrent(platform->display, None, NULL);
		glXDestroyContext(platform->display, platform->context);
	}
	if(platform->display != NULL) {
		XDestroyWindow(platform->display, platform->window);
		XCloseDisplay(platform->display);
	}
	gf_log_function(platform->engine, "Destroyed platform-dependent part of drawing driver", "");
	free(platform);
}
