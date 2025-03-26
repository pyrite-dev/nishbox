#ifndef __NB_CORE_H__
#define __NB_CORE_H__

#include <nb_draw.h>

#include <ode/ode.h>

typedef struct nb_engine {
	dWorldID world;
	nb_draw_t* draw;
} nb_engine_t;

void nb_engine_begin(void);
void nb_engine_end(void);
nb_engine_t* nb_engine_create(void);
void nb_engine_destroy(nb_engine_t* engine);

#endif
