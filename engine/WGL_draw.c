#define NB_EXPOSE_DRAW_PLATFORM

/* External library */
#include <windows.h>

/* Interface */
#include "nb_draw_platform.h"

/* NishBox */
#include "nb_log.h"
#include "nb_draw.h"

/* Standard */
#include <string.h>

LRESULT CALLBACK _nb_draw_proc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) { return DefWindowProc(hWnd, msg, wp, lp); }

typedef BOOL(APIENTRY* PFNWGLSWAPINTERVALPROC)(int);

void _nb_draw_create(nb_draw_t** pdraw) {
	nb_draw_t*	       draw = *pdraw;
	WNDCLASSEX	       wc;
	PIXELFORMATDESCRIPTOR  desc;
	PFNWGLSWAPINTERVALPROC wglSwapIntervalEXT;
	RECT		       rect;
	int		       fmt;
	draw->instance = (HINSTANCE)GetModuleHandle(NULL);
	if(draw->instance == NULL) {
		nb_function_log("Failed to get the instance", "");
		nb_draw_destroy(draw);
		*pdraw = NULL;
		return;
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
	}

	draw->window = CreateWindow("nishbox", "NishBox", (WS_OVERLAPPEDWINDOW), draw->x, draw->y, draw->width, draw->height, NULL, 0, draw->instance, NULL);
	if(draw->window == NULL) {
		nb_function_log("Failed to create window", "");
		nb_draw_destroy(draw);
		*pdraw = NULL;
		return;
	}

	GetWindowRect(draw->window, &rect);

	memset(&desc, 0, sizeof(desc));
	desc.nSize	= sizeof(desc);
	desc.nVersion	= 1;
	desc.dwFlags	= PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	desc.iPixelType = PFD_TYPE_RGBA;
	desc.cColorBits = 16;
	desc.cAlphaBits = 8;
	desc.cDepthBits = 16;

	draw->dc = GetDC(draw->window);

	fmt = ChoosePixelFormat(draw->dc, &desc);
	SetPixelFormat(draw->dc, fmt, &desc);
	SetWindowPos(draw->window, HWND_TOP, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_FRAMECHANGED);

	draw->glrc = wglCreateContext(draw->dc);
	wglMakeCurrent(draw->dc, draw->glrc);

	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALPROC)wglGetProcAddress("wglSwapIntervalEXT");
	if(wglSwapIntervalEXT != NULL) {
		nb_function_log("Enabled VSync", "");
		wglSwapIntervalEXT(1);
	}

	ShowWindow(draw->window, SW_NORMAL);
	UpdateWindow(draw->window);
}

void _nb_draw_destroy(nb_draw_t* draw) {}
