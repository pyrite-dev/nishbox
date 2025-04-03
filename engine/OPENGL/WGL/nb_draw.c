#define NB_EXPOSE_DRAW_PLATFORM
#define NB_EXPOSE_DRAW

#include <nb_pre.h>

/* External library */
#include <GL/gl.h>
#include <GL/wgl.h>

/* Interface */
#include <nb_draw_platform.h>

/* NishBox */
#include <nb_log.h>
#include <nb_draw.h>

/* Standard */
#include <string.h>
#include <stdlib.h>

typedef const char*(APIENTRY* PFNWGLGETEXTENSIONSSTRINGARB)(HDC);
typedef BOOL(APIENTRY* PFNWGLSWAPINTERVALPROC)(int);

void nb_draw_platform_begin(void) {}
void nb_draw_platform_end(void) {}

LRESULT CALLBACK nb_draw_platform_proc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
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
		wglMakeCurrent(draw->platform->dc, draw->platform->glrc);
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

int nb_draw_platform_has_extension(nb_draw_t* draw, const char* query) {
	const char*		     ext = NULL;
	const char*		     ptr;
	const int		     len = strlen(query);
	PFNWGLGETEXTENSIONSSTRINGARB proc;

	wglMakeCurrent(draw->platform->dc, draw->platform->glrc);

	proc = (PFNWGLGETEXTENSIONSSTRINGARB)wglGetProcAddress("wglGetExtensionsStringARB");

	if(proc != NULL) {
		ext = proc(draw->platform->dc);
		ptr = strstr(ext, query);
		return ((ptr != NULL) && ((ptr[len] == ' ') || (ptr[len] == '\0')));
	}
	return 0;
}

int nb_draw_platform_step(nb_draw_t* draw) {
	MSG msg;
	int ret = 0;
	wglMakeCurrent(draw->platform->dc, draw->platform->glrc);
	while(PeekMessage(&msg, draw->platform->window, 0, 0, PM_NOREMOVE)) {
		if(GetMessage(&msg, draw->platform->window, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} else {
			ret = 1;
			break;
		}
	}
	if(ret == 0) {
		nb_draw_frame(draw);

		SwapBuffers(draw->platform->dc);
	}
	return ret;
}

void nb_draw_platform_create(nb_draw_t* draw) {
	WNDCLASSEX	       wc;
	PIXELFORMATDESCRIPTOR  desc;
	PFNWGLSWAPINTERVALPROC wglSwapIntervalEXT;
	RECT		       rect;
	int		       fmt;
	DWORD		       style;

	draw->platform = malloc(sizeof(*draw->platform));
	memset(draw->platform, 0, sizeof(*draw->platform));

	draw->platform->instance = (HINSTANCE)GetModuleHandle(NULL);
	if(draw->platform->instance == NULL) {
		nb_function_log("Failed to get instance", "");
		nb_draw_destroy(draw);
		return;
	} else {
		nb_function_log("Got instance", "");
	}

	wc.cbSize	 = sizeof(wc);
	wc.style	 = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc	 = nb_draw_platform_proc;
	wc.cbClsExtra	 = 0;
	wc.cbWndExtra	 = 0;
	wc.hInstance	 = draw->platform->instance;
	wc.hIcon	 = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName	 = NULL;
	wc.lpszClassName = "nishbox";
	wc.hIconSm	 = LoadIcon(NULL, IDI_WINLOGO);
	if(!RegisterClassEx(&wc)) {
		nb_function_log("Failed to register class", "");
		nb_draw_destroy(draw);
		return;
	} else {
		nb_function_log("Registered class", "");
	}

	draw->platform->window = CreateWindow("nishbox", "NishBox (WGL)", (WS_OVERLAPPEDWINDOW), draw->x, draw->y, draw->width, draw->height, NULL, 0, draw->platform->instance, NULL);
	if(draw->platform->window == NULL) {
		nb_function_log("Failed to create window", "");
		nb_draw_destroy(draw);
		return;
	} else {
		nb_function_log("Created window", "");
	}

	SetWindowLongPtr(draw->platform->window, GWLP_USERDATA, (LONG_PTR)draw);

	memset(&desc, 0, sizeof(desc));
	desc.nSize	= sizeof(desc);
	desc.nVersion	= 1;
	desc.dwFlags	= PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	desc.iPixelType = PFD_TYPE_RGBA;
	desc.cColorBits = 24;
	desc.cAlphaBits = 8;
	desc.cDepthBits = 32;

	draw->platform->dc = GetDC(draw->platform->window);

	fmt = ChoosePixelFormat(draw->platform->dc, &desc);
	SetPixelFormat(draw->platform->dc, fmt, &desc);

	draw->platform->glrc = wglCreateContext(draw->platform->dc);
	if(draw->platform->glrc == NULL) {
		nb_function_log("Failed to create OpenGL context", "");
		nb_draw_destroy(draw);
		return;
	} else {
		nb_function_log("Created OpenGL context", "");
	}
	wglMakeCurrent(draw->platform->dc, draw->platform->glrc);

	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALPROC)wglGetProcAddress("wglSwapIntervalEXT");
	if(wglSwapIntervalEXT != NULL) {
		nb_function_log("Enabled VSync", "");
		wglSwapIntervalEXT(1);
	}

	SetRect(&rect, 0, 0, draw->width, draw->height);
	style = (DWORD)GetWindowLongPtr(draw->platform->window, GWL_STYLE);
	AdjustWindowRect(&rect, style, FALSE);
	SetWindowPos(draw->platform->window, NULL, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE);

	ShowWindow(draw->platform->window, SW_NORMAL);
	UpdateWindow(draw->platform->window);
}

void nb_draw_platform_destroy(nb_draw_t* draw) {
	if(draw->platform->glrc != NULL) {
		wglMakeCurrent(NULL, NULL);
	}
	if(draw->platform->dc != NULL) {
		ReleaseDC(draw->platform->window, draw->platform->dc);
	}
	if(draw->platform->glrc != NULL) {
		wglDeleteContext(draw->platform->glrc);
	}
	if(draw->platform->window != NULL) {
		DestroyWindow(draw->platform->window);
	}
	free(draw->platform);
}
