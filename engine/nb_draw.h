#ifndef __NB_DRAW_H__
#define __NB_DRAW_H__

#include <nb_macro.h>

/* External library */

/* NishBox */
#include <nb_draw_platform.h>

/* Standard */

nb_draw_t* nb_draw_create(void);
void	   nb_draw_destroy(nb_draw_t* draw);

#endif
