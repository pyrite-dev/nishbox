#define NB_EXPOSE_DRAW_PLATFORM

#include "nb_pre.h"

/* External library */
#include <GL/gl.h>
#include <windows.h>

/* Interface */
#include "nb_draw_platform.h"

/* NishBox */
#include "nb_log.h"
#include "nb_draw.h"

/* Standard */
#include <string.h>

typedef const char*(APIENTRY* PFNWGLGETEXTENSIONSSTRINGARB)(HDC);
typedef BOOL(APIENTRY* PFNWGLSWAPINTERVALPROC)(int);

void _nb_draw_init(void) {}

LRESULT CALLBACK _nb_draw_proc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	PAINTSTRUCT ps;
	RECT	    rect;
	nb_draw_t*  draw = (nb_draw_t*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	switch(msg) {
	case WM_PAINT:
		BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_SIZE:
		GetClientRect(hWnd, &rect);
		draw->x	     = rect.left;
		draw->y	     = rect.top;
		draw->width  = rect.right - rect.left;
		draw->height = rect.bottom - rect.top;
		wglMakeCurrent(draw->dc, draw->glrc);
		nb_draw_reshape(draw);
		break;
	case WM_CLOSE:
		draw->close = 1;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wp, lp);
	}
	return 0;
}

int _nb_draw_has_extension(nb_draw_t* draw, const char* query) {
	const char*		     ext = NULL;
	const char*		     ptr;
	const int		     len = strlen(query);
	PFNWGLGETEXTENSIONSSTRINGARB proc;

	wglMakeCurrent(draw->dc, draw->glrc);

	proc = (PFNWGLGETEXTENSIONSSTRINGARB)wglGetProcAddress("wglGetExtensionsStringARB");

	if(proc != NULL) {
		ext = proc(draw->dc);
		ptr = strstr(ext, query);
		return ((ptr != NULL) && ((ptr[len] == ' ') || (ptr[len] == '\0')));
	}
	return 0;
}

int _nb_draw_step(nb_draw_t* draw) {
	MSG msg;
	int ret = 0;
	wglMakeCurrent(draw->dc, draw->glrc);
	while(PeekMessage(&msg, draw->window, 0, 0, PM_NOREMOVE)) {
		if(GetMessage(&msg, draw->window, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			ret = 1;
			break;
		}
	}
	if(ret == 0) {
		nb_draw_frame(draw);

		glFlush();
		SwapBuffers(draw->dc);
	}
	return ret;
}

void _nb_draw_create(nb_draw_t** pdraw) {
	nb_draw_t*	       draw = *pdraw;
	WNDCLASSEX	       wc;
	PIXELFORMATDESCRIPTOR  desc;
	PFNWGLSWAPINTERVALPROC wglSwapIntervalEXT;
	RECT		       rect;
	int		       fmt;
	DWORD		       style;
	draw->instance = (HINSTANCE)GetModuleHandle(NULL);
	if(draw->instance == NULL) {
		nb_function_log("Failed to get instance", "");
		nb_draw_destroy(draw);
		*pdraw = NULL;
		return;
	} else {
		nb_function_log("Got instance", "");
	}

	wc.cbSize	 = sizeof(wc);
	wc.style	 = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc	 = _nb_draw_proc;
	wc.cbClsExtra	 = 0;
	wc.cbWndExtra	 = 0;
	wc.hInstance	 = draw->instance;
	wc.hIcon	 = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName	 = NULL;
	wc.lpszClassName = "nishbox";
	wc.hIconSm	 = LoadIcon(NULL, IDI_WINLOGO);
	if(!RegisterClassEx(&wc)) {
		nb_function_log("Failed to register class", "");
		nb_draw_destroy(draw);
		*pdraw = NULL;
		return;
	} else {
		nb_function_log("Registered class", "");
	}

	draw->window = CreateWindow("nishbox", "NishBox (WGL)", (WS_OVERLAPPEDWINDOW), draw->x, draw->y, draw->width, draw->height, NULL, 0, draw->instance, NULL);
	if(draw->window == NULL) {
		nb_function_log("Failed to create window", "");
		nb_draw_destroy(draw);
		*pdraw = NULL;
		return;
	} else {
		nb_function_log("Created window", "");
	}

	SetWindowLongPtr(draw->window, GWLP_USERDATA, (LONG_PTR)draw);

	memset(&desc, 0, sizeof(desc));
	desc.nSize	= sizeof(desc);
	desc.nVersion	= 1;
	desc.dwFlags	= PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	desc.iPixelType = PFD_TYPE_RGBA;
	desc.cColorBits = 24;
	desc.cAlphaBits = 8;
	desc.cDepthBits = 32;

	draw->dc = GetDC(draw->window);

	fmt = ChoosePixelFormat(draw->dc, &desc);
	SetPixelFormat(draw->dc, fmt, &desc);

	draw->glrc = wglCreateContext(draw->dc);
	if(draw->glrc == NULL) {
		nb_function_log("Failed to create OpenGL context", "");
		nb_draw_destroy(draw);
		*pdraw = NULL;
		return;
	} else {
		nb_function_log("Created OpenGL context", "");
	}
	wglMakeCurrent(draw->dc, draw->glrc);

	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALPROC)wglGetProcAddress("wglSwapIntervalEXT");
	if(wglSwapIntervalEXT != NULL) {
		nb_function_log("Enabled VSync", "");
		wglSwapIntervalEXT(1);
	}

	SetRect(&rect, 0, 0, draw->width, draw->height);
	style = (DWORD)GetWindowLongPtr(draw->window, GWL_STYLE);
	AdjustWindowRect(&rect, style, FALSE);
	SetWindowPos(draw->window, NULL, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE);

	ShowWindow(draw->window, SW_NORMAL);
	UpdateWindow(draw->window);
}

void _nb_draw_destroy(nb_draw_t* draw) {
	if(draw->glrc != NULL) {
		wglMakeCurrent(NULL, NULL);
		ReleaseDC(draw->window, draw->dc);
		wglDeleteContext(draw->glrc);
	}
	if(draw->window != NULL) {
		DestroyWindow(draw->window);
	}
}
