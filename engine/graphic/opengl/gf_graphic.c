#define GF_EXPOSE_DRAW

#include <gf_pre.h>

/* External library */
#include <GL/gl.h>
#include <GL/glu.h>

/* Interface */
#include <gf_graphic.h>

/* Engine */
#include <gf_draw.h>
#include <gf_texture.h>

/* Standard */

void gf_graphic_begin_2d(gf_draw_t* draw) {
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, draw->width, draw->height, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void gf_graphic_end_2d(gf_draw_t* draw) {
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void gf_graphic_clear(gf_draw_t* draw) { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

void gf_graphic_text(gf_draw_t* draw, float x, float y, float size, const char* text, float r, float g, float b, float a) {
	int i;
	for(i = 0; text[i] != 0; i++) {
		gf_draw_texture(draw, x + i * (size / 2), y, size / 2, size, draw->font[text[i]], r, g, b, a);
	}
}
