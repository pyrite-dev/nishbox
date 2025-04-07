#ifndef __NE_DRAW_H__
#define __NE_DRAW_H__

#include <ne_pre.h>
#include <ne_macro.h>

/* Type */
#include <ne_type/draw.h>

/* NishBox */

/* Standard */

ne_draw_t* ne_draw_create(void);
void	   ne_draw_destroy(ne_draw_t* draw);
void	   ne_draw_frame(ne_draw_t* draw);
int	   ne_draw_step(ne_draw_t* draw);
void	   ne_draw_begin(void);
void	   ne_draw_end(void);
void	   ne_draw_set_draw(ne_draw_t* engine, void (*func)(ne_draw_t*));
void	   ne_draw_reshape(ne_draw_t* draw);

#endif
