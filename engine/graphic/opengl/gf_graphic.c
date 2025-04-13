#define GF_EXPOSE_DRAW
#define GF_EXPOSE_TEXTURE

#include <gf_pre.h>

/* External library */
#include <GL/gl.h>
#include <GL/glu.h>

/* Interface */
#include <gf_graphic.h>

/* Engine */
#include <gf_draw.h>
#include <gf_texture.h>
#include <gf_draw_driver.h>

/* Standard */

void gf_graphic_begin_2d(gf_draw_t* draw) {
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
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
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}

void gf_graphic_clear(gf_draw_t* draw) { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

void gf_graphic_draw_texture_2d(gf_draw_t* draw, float x, float y, float w, float h, gf_texture_t* texture, gf_color_t color) {
	double tw = (double)texture->width / texture->internal_width;
	double th = (double)texture->height / texture->internal_height;

	gf_graphic_begin_2d(draw);

	gf_draw_driver_set_color(draw, color);
	gf_draw_driver_begin_texture_2d(draw, texture);
	glBegin(GL_QUADS);

	glTexCoord2d(0, 0);
	glVertex2f(x, y);

	glTexCoord2d(0, th);
	glVertex2f(x, y + h);

	glTexCoord2d(tw, th);
	glVertex2f(x + w, y + h);

	glTexCoord2d(tw, 0);
	glVertex2f(x + w, y);

	glEnd();
	gf_draw_driver_end_texture_2d(draw);

	gf_graphic_end_2d(draw);
}

void gf_graphic_fill_rect(gf_draw_t* draw, float x, float y, float w, float h, gf_color_t color) {
	gf_graphic_begin_2d(draw);

	gf_draw_driver_set_color(draw, color);
	glBegin(GL_QUADS);

	glVertex2f(x, y);
	glVertex2f(x, y + h);
	glVertex2f(x + w, y + h);
	glVertex2f(x + w, y);

	glEnd();

	gf_graphic_end_2d(draw);
}

void gf_graphic_text(gf_draw_t* draw, float x, float y, float size, const char* text, gf_color_t color) {
	int i;
	for(i = 0; text[i] != 0; i++) {
		gf_graphic_draw_texture_2d(draw, x + i * (size / 2), y, size / 2, size, draw->font[text[i]], color);
	}
}
