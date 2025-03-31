#define NB_EXPOSE_DRAW
#define NB_EXPOSE_DRAW_PLATFORM

#include "nb_pre.h"

/* External library */
#include <GL/gl.h>
#include <GL/glu.h>
#include "ext_stb_image.h"

/* Interface */
#include "nb_draw.h"

/* NishBox */
#include "nb_log.h"
#include "nb_draw_platform.h"
#include "nb_font.h"
#include "nb_math.h"

/* Standard */
#include <stdlib.h>
#include <string.h>
#include <math.h>

GLfloat lightwht[] = {1.0, 1.0, 1.0, 1.0};
GLfloat lightdim[] = {0.2, 0.2, 0.2, 1.0};
GLfloat lightblk[] = {0.0, 0.0, 0.0, 1.0};

nb_draw_t* nb_draw_create(void) {
	nb_draw_t* draw = malloc(sizeof(*draw));
	memset(draw, 0, sizeof(*draw));
	draw->x	      = 0;
	draw->y	      = 0;
	draw->width   = 640;
	draw->height  = 480;
	draw->running = 0;
	_nb_draw_create(&draw);
	if(draw != NULL) {
		nb_function_log("Created drawing interface successfully", "");
		nb_draw_init_opengl(draw);
		nb_draw_reshape(draw);
		draw->running = 1;
	}
	return draw;
}

GLuint nb_test_texture;

void nb_draw_body(nb_draw_t* draw);

void nb_draw_init_opengl(nb_draw_t* draw) {
	int	       i;
	int	       w, h, ch;
	unsigned char* img;
	glEnable(GL_BLEND);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glCullFace(GL_BACK);

	glLightfv(GL_LIGHT0, GL_AMBIENT, lightdim);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightwht);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightblk);

	glShadeModel(GL_FLAT);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	glLoadIdentity();

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

	img = stbi_load("texture/test.bmp", &w, &h, &ch, 4);
	glGenTextures(1, &nb_test_texture);
	glBindTexture(GL_TEXTURE_2D, nb_test_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(img);

	draw->quadric = gluNewQuadric();

	draw->light[0] = 10.0;
	draw->light[1] = 10.0;
	draw->light[2] = 0.0;
	draw->light[3] = 1.0;

	draw->camera[0] = 0;
	draw->camera[1] = 10;
	draw->camera[2] = 0;

	draw->lookat[0] = 0;
	draw->lookat[1] = 0;
	draw->lookat[2] = 0;
}

int nb_draw_has_extension(nb_draw_t* draw, const char* query) {
	int	    ret = _nb_draw_has_extension(draw, query);
	const char* ext = NULL;
	const char* ptr;
	const int   len = strlen(query);
	if(ret != 0) return ret;

	ext = glGetString(GL_EXTENSIONS);
	ptr = strstr(ext, query);
	return ((ptr != NULL) && ((ptr[len] == ' ') || (ptr[len] == '\0')));
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
	glMatrixMode(GL_MODELVIEW);
}

double i = 0;

#define NEAREST_POW2(x) pow((2), nb_log2((int)(x) + 1))

void nb_draw_frame(nb_draw_t* draw) {
	double size = 10;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(draw->camera[0], draw->camera[1], draw->camera[2], draw->lookat[0], draw->lookat[1], draw->lookat[2], 0, 1, 0);
	glLightfv(GL_LIGHT0, GL_POSITION, draw->light);

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, nb_test_texture);
	glBegin(GL_QUADS);
	glNormal3d(0, 5, 0);
	glColor3f(1, 1, 1);
	glTexCoord2i(0, 0);
	glVertex3d(-size / 2, 0, -size / 2);
	glTexCoord2i(0, size);
	glVertex3d(-size / 2, 0, size / 2);
	glTexCoord2i(size, size);
	glVertex3d(size / 2, 0, size / 2);
	glTexCoord2i(size, 0);
	glVertex3d(size / 2, 0, -size / 2);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	draw->camera[0] = 10 * cos(i / 180 * M_PI);
	draw->camera[1] = 10;
	draw->camera[2] = 10 * sin(i / 180 * M_PI);

	i++;
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
	gluPerspective(30, (double)draw->width / (double)draw->height, 1.0, 1000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void nb_draw_destroy(nb_draw_t* draw) {
	int i;
	if(draw->running) {
		for(i = 0; i < sizeof(nb_font) / sizeof(nb_font[0]); i++) {
			glDeleteTextures(1, &draw->font[i]);
		}
	}
	_nb_draw_destroy(draw);
	free(draw);
	nb_function_log("Destroyed drawing interface", "");
}
