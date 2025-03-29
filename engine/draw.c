#define NB_EXPOSE_DRAW
#define NB_EXPOSE_DRAW_PLATFORM

/* External library */
#include <GL/gl.h>

/* Interface */
#include "nb_draw.h"

/* NishBox */
#include "nb_log.h"
#include "nb_draw_platform.h"

/* Standard */
#include <stdlib.h>
#include <string.h>

nb_draw_t* nb_draw_create(void) {
	nb_draw_t* draw = malloc(sizeof(*draw));
	memset(draw, 0, sizeof(*draw));
	draw->x	     = 0;
	draw->y	     = 0;
	draw->width  = 640;
	draw->height = 480;
	_nb_draw_create(&draw);
	if(draw != NULL) {
		nb_function_log("Created drawing interface successfully", "");
	}
	_nb_draw_init_opengl(draw);
	nb_draw_reshape(draw);
	return draw;
}

void nb_draw_begin_2d(nb_draw_t* draw) {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, draw->width, draw->height, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void nb_draw_end_2d(nb_draw_t* draw) {
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}

void nb_draw_frame(nb_draw_t* draw) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	nb_draw_begin_2d(draw);
	glColor3f(1, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(0, 0);
	glVertex2f(draw->width, draw->height);
	glVertex2f(draw->width, 0);
	glEnd();
	glColor3f(0, 0, 1);
	glBegin(GL_TRIANGLES);
	glVertex2f(0, draw->height);
	glVertex2f(draw->width, draw->height);
	glVertex2f(0, 0);
	glEnd();
	nb_draw_end_2d(draw);
}

int nb_draw_step(nb_draw_t* draw) {
	int ret = _nb_draw_step(draw);
	if(ret != 0) return ret;
	draw->close = 0;
	return 0;
}

void nb_draw_reshape(nb_draw_t* draw) {
	glViewport(0, 0, (GLint)draw->width, (GLint)draw->height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void nb_draw_destroy(nb_draw_t* draw) {
	_nb_draw_destroy(draw);
	free(draw);
	nb_function_log("Destroyed drawing interface", "");
}
