#ifndef __NB_DRAW_H__
#define __NB_DRAW_H__

#include <nb_macro.h>

/* External library */

/* NishBox */
#include <nb_draw_platform.h>

/* Standard */

nb_draw_t* nb_draw_create(void);
void	   nb_draw_destroy(nb_draw_t* draw);
void	   nb_draw_frame(nb_draw_t* draw);
int	   nb_draw_step(nb_draw_t* draw);
void	   nb_draw_reshape(nb_draw_t* draw);
void	   nb_draw_init_opengl(nb_draw_t* draw);

#endif
