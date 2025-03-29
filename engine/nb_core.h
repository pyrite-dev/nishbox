#ifndef __NB_CORE_H__
#define __NB_CORE_H__

/* Interface */

/* NishBox */

/* External library */
#include <ode/ode.h>

/* Standard */

typedef struct nb_engine {
	dWorldID world;
	void*	 draw; /* User should not touch this directly: internally pointer of nb_draw_t */
} nb_engine_t;

void	     nb_engine_begin(void);
void	     nb_engine_end(void);
nb_engine_t* nb_engine_create(void);
void	     nb_engine_destroy(nb_engine_t* engine);

#endif
