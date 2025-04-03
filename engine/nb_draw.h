#ifndef __NB_DRAW_H__
#define __NB_DRAW_H__

#include <nb_pre.h>
#include <nb_macro.h>

/* Type */
#include <nb_type/draw.h>

/* NishBox */

/* Standard */

nb_draw_t* nb_draw_create(void);
void	   nb_draw_destroy(nb_draw_t* draw);
void	   nb_draw_frame(nb_draw_t* draw);
int	   nb_draw_step(nb_draw_t* draw);
void	   nb_draw_begin(void);
void	   nb_draw_end(void);
void	   nb_draw_reshape(nb_draw_t* draw);
void	   nb_draw_begin_2d(nb_draw_t* draw);
void	   nb_draw_end_2d(nb_draw_t* draw);

#endif
