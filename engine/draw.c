#define NB_EXPOSE_DRAW
#define NB_EXPOSE_DRAW_PLATFORM

/* External library */
#include <GL/gl.h>

/* Interface */
#include "nb_draw.h"

/* NishBox */
#include "nb_log.h"
#include "nb_draw_platform.h"
#include "nb_font.h"

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
	nb_draw_init_opengl(draw);
	nb_draw_reshape(draw);
	return draw;
}

void nb_draw_init_opengl(nb_draw_t* draw) {
	int i;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	for(i = 0; i < sizeof(nb_font) / sizeof(nb_font[0]); i++) {
		unsigned char* font = malloc(8 * 8 * 4);
		int	       j;
		for(j = 0; j < 8 * 8; j++) {
			unsigned char val = (nb_font[i][j / 8] >> (j % 8)) & 1 ? 255 : 0;
			font[j * 4 + 0]	  = val;
			font[j * 4 + 1]	  = val;
			font[j * 4 + 2]	  = val;
			font[j * 4 + 3]	  = val;
		}
		glGenTextures(1, &draw->font[i]);
		glBindTexture(GL_TEXTURE_2D, draw->font[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 8, 8, 0, GL_RGBA, GL_UNSIGNED_BYTE, font);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		free(font);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	nb_function_log("Registered %d glyphs", sizeof(nb_font) / sizeof(nb_font[0]));
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
