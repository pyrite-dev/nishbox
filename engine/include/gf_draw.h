#ifndef __GF_DRAW_H__
#define __GF_DRAW_H__

#include <gf_pre.h>
#include <gf_macro.h>

/* Type */
#include <gf_type/draw.h>

/* Engine */

/* Standard */

gf_draw_t* gf_draw_create(const char* title);
void	   gf_draw_destroy(gf_draw_t* draw);
void	   gf_draw_frame(gf_draw_t* draw);
int	   gf_draw_step(gf_draw_t* draw);
void	   gf_draw_begin(void);
void	   gf_draw_end(void);
void	   gf_draw_set_draw(gf_draw_t* engine, void (*func)(gf_draw_t*));
void	   gf_draw_reshape(gf_draw_t* draw);

#endif
