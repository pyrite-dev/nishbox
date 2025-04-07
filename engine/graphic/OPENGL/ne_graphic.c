#define NE_EXPOSE_DRAW

#include <ne_pre.h>

/* External library */
#include <GL/gl.h>
#include <GL/glu.h>

/* Interface */
#include <ne_graphic.h>

/* NishBox */
#include <ne_draw.h>
#include <ne_texture.h>

/* Standard */

void ne_graphic_begin_2d(ne_draw_t* draw) {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, draw->width, draw->height, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void ne_graphic_end_2d(ne_draw_t* draw) {
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void ne_graphic_clear(ne_draw_t* draw) { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

void ne_graphic_text(ne_draw_t* draw, float x, float y, float size, const char* text, float r, float g, float b, float a) {
	int i;
	for(i = 0; text[i] != 0; i++) {
		ne_draw_texture(draw, x + i * (size / 2), y, size / 2, size, draw->font[text[i]], r, g, b, a);
	}
}
