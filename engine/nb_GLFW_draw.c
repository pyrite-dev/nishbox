#define NB_EXPOSE_DRAW_PLATFORM
#define NB_EXPOSE_DRAW

#include "nb_pre.h"

/* External library */
#include <GL/gl.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>

/* Interface */
#include "nb_draw_platform.h"

/* NishBox */
#include "nb_log.h"
#include "nb_draw.h"

/* Standard */
#include <string.h>
#include <stdlib.h>

void nb_draw_platform_begin(void) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
}

void nb_draw_platform_end(void) {}

int nb_draw_platform_has_extension(nb_draw_t* draw, const char* query) {
	const char* ext = NULL;
	const char* ptr;
	const int   len = strlen(query);

	glfwMakeContextCurrent(draw->platform->window);

	return glfwExtensionSupported(query);
}

int nb_draw_platform_step(nb_draw_t* draw) {
	int ret = 0;
	glfwMakeContextCurrent(draw->platform->window);
	draw->close = glfwWindowShouldClose(draw->platform->window);
	if(draw->close) glfwSetWindowShouldClose(draw->platform->window, GLFW_FALSE);
	glfwPollEvents();
	if(ret == 0) {
		nb_draw_frame(draw);

		glfwSwapBuffers(draw->platform->window);
	}
	return ret;
}

void nb_draw_platform_create(nb_draw_t* draw) {
	draw->platform = malloc(sizeof(*draw->platform));
	memset(draw->platform, 0, sizeof(*draw->platform));

	draw->platform->window = glfwCreateWindow(draw->width, draw->height, "NishBox (GLFW)", NULL, NULL);
	if(draw->platform->window == NULL) {
		nb_function_log("Failed to create window", "");
		nb_draw_destroy(draw);
		return;
	}

	glfwMakeContextCurrent(draw->platform->window);
	glfwSwapInterval(1);
}

void nb_draw_platform_destroy(nb_draw_t* draw) {
	if(draw->platform->window != NULL) {
		glfwDestroyWindow(draw->platform->window);
	}
	free(draw->platform);
}
