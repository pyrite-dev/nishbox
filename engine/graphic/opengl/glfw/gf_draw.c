#define GF_EXPOSE_DRAW_PLATFORM
#define GF_EXPOSE_DRAW

#include <gf_pre.h>

/* External library */
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

/* Interface */
#include <gf_draw_platform.h>

/* Engine */
#include <gf_draw_driver.h>
#include <gf_log.h>
#include <gf_draw.h>

/* Standard */
#include <string.h>
#include <stdlib.h>

void gf_draw_platform_begin(void) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
}

void gf_draw_platform_end(void) {}

void gf_glfw_size(GLFWwindow* window, int w, int h) {
	gf_draw_t* draw = (gf_draw_t*)glfwGetWindowUserPointer(window);
	draw->width	= w;
	draw->height	= h;
	glfwSetWindowSize(window, w, h);
	gf_draw_reshape(draw);
}

int gf_draw_platform_has_extension(gf_draw_t* draw, const char* query) {
	const char* ext = NULL;
	const char* ptr;
	const int   len = strlen(query);

	glfwMakeContextCurrent(draw->platform->window);

	return glfwExtensionSupported(query);
}

int gf_draw_platform_step(gf_draw_t* draw) {
	int ret = 0;
	int w, h;
	glfwMakeContextCurrent(draw->platform->window);
	draw->close = glfwWindowShouldClose(draw->platform->window);
	if(draw->close) glfwSetWindowShouldClose(draw->platform->window, GLFW_FALSE);
	glfwPollEvents();
	if(ret == 0) {
		gf_draw_driver_before(draw);
		gf_draw_frame(draw);
		gf_draw_driver_after(draw);

		glfwSwapBuffers(draw->platform->window);
	}
	return ret;
}

void gf_draw_platform_create(gf_draw_t* draw) {
	draw->platform = malloc(sizeof(*draw->platform));
	memset(draw->platform, 0, sizeof(*draw->platform));

	draw->platform->window = glfwCreateWindow(draw->width, draw->height, draw->title, NULL, NULL);
	if(draw->platform->window == NULL) {
		gf_function_log(NULL, "Failed to create window", "");
		gf_draw_destroy(draw);
		return;
	}

	glfwSetWindowUserPointer(draw->platform->window, draw);
	glfwSetWindowSizeCallback(draw->platform->window, gf_glfw_size);

	glfwMakeContextCurrent(draw->platform->window);
#ifdef DO_SWAP_INTERVAL
	glfwSwapInterval(1);
#endif
}

void gf_draw_platform_destroy(gf_draw_t* draw) {
	if(draw->platform->window != NULL) {
		glfwDestroyWindow(draw->platform->window);
	}
	free(draw->platform);
}
