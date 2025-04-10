#define GF_EXPOSE_DRAW_DRIVER
#define GF_EXPOSE_DRAW

#include <gf_pre.h>

/* External library */
#include <GL/gl.h>
#include <GL/glu.h>

/* Interface */
#include <gf_draw_driver.h>

/* Engine */
#include <gf_draw_platform.h>
#include <gf_texture.h>
#include <gf_draw.h>
#include <gf_log.h>
#include <gf_font.h>
#include <gf_math.h>
#include <gf_graphic.h>

/* Standard */
#include <stdlib.h>
#include <string.h>
#include <math.h>

GLfloat lightwht[] = {1.0, 1.0, 1.0, 1.0};
GLfloat lightdim[] = {0.2, 0.2, 0.2, 1.0};
GLfloat lightblk[] = {0.0, 0.0, 0.0, 1.0};

#define NEAREST_POW2(x) pow((2), gf_log2((int)(x) + 1))

gf_draw_driver_texture_t* gf_draw_driver_register_texture(gf_draw_t* draw, int width, int height, unsigned char* data) {
	gf_draw_driver_texture_t* r = malloc(sizeof(*r));
	int			  w = NEAREST_POW2(width);
	int			  h = NEAREST_POW2(height);
	int			  x, y;
	unsigned char*		  d = malloc(w * h * 4);

	memset(d, 0, w * h);
	for(y = 0; y < height; y++) {
		for(x = 0; x < width; x++) {
			int pos	  = (y * h + x) * 4;
			int ogpos = (y * height + x) * 4;
			memcpy(d + pos + 0, data + ogpos + 0, 4);
		}
	}

	glGenTextures(1, &r->id);
	glBindTexture(GL_TEXTURE_2D, r->id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, d);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glBindTexture(GL_TEXTURE_2D, 0);

	return r;
}

void gf_draw_driver_destroy_texture(gf_draw_driver_texture_t* t) {
	glDeleteTextures(1, &t->id);
	free(t);
}

void gf_draw_driver_init(gf_draw_t* draw) {
	int i;
	int w, h, ch;
	draw->driver = malloc(sizeof(*draw->driver));

	glEnable(GL_BLEND);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glCullFace(GL_BACK);

	glShadeModel(GL_FLAT);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightdim);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightwht);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightblk);

	glLoadIdentity();

	for(i = 0; i < sizeof(gf_font) / sizeof(gf_font[0]); i++) {
		unsigned char* font = malloc(8 * 8 * 4);
		int	       j;
		for(j = 0; j < 8 * 8; j++) {
			unsigned char val = (gf_font[i][j / 8] >> (j % 8)) & 1 ? 255 : 0;
			font[j * 4 + 0]	  = val;
			font[j * 4 + 1]	  = val;
			font[j * 4 + 2]	  = val;
			font[j * 4 + 3]	  = val;
		}
		draw->font[i] = gf_register_texture(draw, 8, 8, font);
		free(font);
	}
	gf_function_log("Registered %d glyphs", sizeof(gf_font) / sizeof(gf_font[0]));

	glClearColor(0, 0, 0, 1);

	draw->driver->quadric = gluNewQuadric();
}

int gf_draw_driver_has_extension(gf_draw_t* draw, const char* query) {
	int	    ret = gf_draw_platform_has_extension(draw, query);
	const char* ext = NULL;
	const char* ptr;
	const int   len = strlen(query);
	if(ret != 0) return ret;

	ext = glGetString(GL_EXTENSIONS);
	ptr = strstr(ext, query);
	return ((ptr != NULL) && ((ptr[len] == ' ') || (ptr[len] == '\0')));
}

void gf_draw_driver_reshape(gf_draw_t* draw) {
	glViewport(0, 0, (GLint)draw->width, (GLint)draw->height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30, (double)draw->width / (double)draw->height, 1.0, 1000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void gf_draw_driver_draw_texture(gf_draw_t* draw, float x, float y, float w, float h, gf_draw_driver_texture_t* texture, float r, float g, float b, float a) {
	gf_graphic_begin_2d(draw);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture->id);

	glColor4f(r / 255, g / 255, b / 255, a / 255);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex2f(x, y);
	glTexCoord2f(0, 1);
	glVertex2f(x, y + h);
	glTexCoord2f(1, 1);
	glVertex2f(x + w, y + h);
	glTexCoord2f(1, 0);
	glVertex2f(x + w, y);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	gf_graphic_end_2d(draw);
}

void gf_draw_driver_destroy(gf_draw_t* draw) {
	int i;
	for(i = 0; i < sizeof(gf_font) / sizeof(gf_font[0]); i++) {
		gf_destroy_texture(draw->font[i]);
	}
}

void gf_draw_driver_before(gf_draw_t* draw) {
	GLfloat lightpos[3];
	GF_VECTOR_COPY(draw->light, lightpos);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(draw->camera[0], draw->camera[1], draw->camera[2], draw->lookat[0], draw->lookat[1], draw->lookat[2], 0, 1, 0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	glPushMatrix();
	gf_graphic_clear(draw);
}

void gf_draw_driver_after(gf_draw_t* draw) {
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}
