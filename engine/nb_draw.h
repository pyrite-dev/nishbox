#ifndef __NB_DRAW_H__
#define __NB_DRAW_H__

#include <nb_pre.h>
#include <nb_macro.h>

/* External library */
#ifdef NB_EXPORT_DRAW
#include <GL/gl.h>
#endif

/* NishBox */
#include <nb_draw_platform.h>

/* Standard */

#ifdef NB_EXPORT_DRAW
typedef struct nb_shape {
	int	points;
	GLfloat points[4][3];
} nb_shape_t;
typedef struct nb_mesh {
	nb_shape_t* shapes;
} nb_mesh_t;
#else
typedef void nb_mesh_t;
typedef void nb_shape_t;
#endif

nb_draw_t* nb_draw_create(void);
void	   nb_draw_destroy(nb_draw_t* draw);
void	   nb_draw_frame(nb_draw_t* draw);
int	   nb_draw_step(nb_draw_t* draw);
void	   nb_draw_reshape(nb_draw_t* draw);
void	   nb_draw_init_opengl(nb_draw_t* draw);
int	   nb_draw_has_extension(nb_draw_t* draw, const char* query);

#endif
