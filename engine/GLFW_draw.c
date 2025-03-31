#define NB_EXPOSE_DRAW_PLATFORM

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

void _nb_draw_init(void) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
}

int _nb_draw_has_extension(nb_draw_t* draw, const char* query) {
	const char* ext = NULL;
	const char* ptr;
	const int   len = strlen(query);

	glfwMakeContextCurrent(draw->window);

	return glfwExtensionSupported(query);
}

int _nb_draw_step(nb_draw_t* draw) {
	int ret = 0;
	glfwMakeContextCurrent(draw->window);
	draw->close = glfwWindowShouldClose(draw->window);
	if(draw->close) glfwSetWindowShouldClose(draw->window, GLFW_FALSE);
	glfwPollEvents();
	if(ret == 0) {
		nb_draw_frame(draw);

		glFlush();
		glfwSwapBuffers(draw->window);
	}
	return ret;
}

void _nb_draw_create(nb_draw_t** pdraw) {
	nb_draw_t* draw = *pdraw;

	draw->window = glfwCreateWindow(draw->width, draw->height, "NishBox (GLFW)", NULL, NULL);
	if(draw->window == NULL) {
		nb_function_log("Failed to create window", "");
		nb_draw_destroy(draw);
		*pdraw = NULL;
		return;
	}

	glfwMakeContextCurrent(draw->window);
	glfwSwapInterval(1);
}

void _nb_draw_destroy(nb_draw_t* draw) {
	if(draw->window != NULL) {
		glfwDestroyWindow(draw->window);
	}
}
