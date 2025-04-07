#define NB_EXPOSE_DRAW

#include <nb_pre.h>

/* External library */
#include <GL/gl.h>
#include <GL/glu.h>

/* Interface */
#include <nb_graphic.h>

/* NishBox */
#include <nb_draw.h>
#include <nb_texture.h>

/* Standard */

void nb_graphic_begin_2d(nb_draw_t* draw) {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, draw->width, draw->height, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void nb_graphic_end_2d(nb_draw_t* draw) {
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void nb_graphic_clear(nb_draw_t* draw) { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

void nb_graphic_text(nb_draw_t* draw, float x, float y, float size, const char* text, float r, float g, float b, float a) {
	int i;
	for(i = 0; text[i] != 0; i++) {
		nb_draw_texture(draw, x + i * (size / 2), y, size / 2, size, draw->font[text[i]], r, g, b, a);
	}
}
