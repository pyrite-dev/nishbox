#define GF_EXPOSE_DRAW
#define GF_EXPOSE_TEXTURE

#include <gf_pre.h>

/* External library */
#include <gf_opengl.h>

/* Interface */
#include <gf_graphic.h>

/* Engine */
#include <gf_draw.h>
#include <gf_texture.h>
#include <gf_draw_driver.h>

/* Standard */
#include <stdarg.h>

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

void gf_graphic_clear(gf_draw_t* draw) { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT); }

void gf_graphic_draw_texture_polygon(gf_draw_t* draw, gf_texture_t* texture, gf_color_t color, int dim, int npair, ...) {
	double	tw = (double)texture->width / texture->internal_width;
	double	th = (double)texture->height / texture->internal_height;
	int	i;
	va_list va;
	va_start(va, npair);

	if(dim == 2) gf_graphic_begin_2d(draw);
	gf_draw_driver_begin_texture_2d(draw, texture);

	gf_draw_driver_set_color(draw, color);
	glBegin(GL_TRIANGLE_FAN);

	for(i = 0; i < npair; i++) {
		float tx = va_arg(va, double) * tw;
		float ty = va_arg(va, double) * th;
		float x	 = va_arg(va, double);
		float y	 = va_arg(va, double);
		glTexCoord2f(tx, ty);
		if(dim == GF_GRAPHIC_2D) {
			glVertex2f(x, y);
		} else if(dim == GF_GRAPHIC_3D) {
			float z = va_arg(va, double);
			glVertex3f(x, y, z);
		}
	}

	glEnd();

	gf_draw_driver_end_texture_2d(draw);
	if(dim == 2) gf_graphic_end_2d(draw);

	va_end(va);
}

void gf_graphic_fill_polygon(gf_draw_t* draw, gf_color_t color, int dim, int npair, ...) {
	int	i;
	va_list va;
	va_start(va, npair);

	gf_graphic_begin_2d(draw);

	gf_draw_driver_set_color(draw, color);
	glBegin(GL_TRIANGLE_FAN);

	for(i = 0; i < npair; i++) {
		float x = va_arg(va, double);
		float y = va_arg(va, double);
		if(dim == GF_GRAPHIC_2D) {
			glVertex2f(x, y);
		} else if(dim == GF_GRAPHIC_3D) {
			float z = va_arg(va, double);
			glVertex3f(x, y, z);
		}
	}

	glEnd();
	gf_graphic_end_2d(draw);

	va_end(va);
}
