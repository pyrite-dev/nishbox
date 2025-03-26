#ifndef __NB_CORE_H__
#define __NB_CORE_H__

#include <ode/ode.h>

typedef struct nb_engine {
	dWorldID world;
} nb_engine_t;

void nb_engine_init(nb_engine_t* engine);
void nb_engine_destroy(nb_engine_t* engine);

#endif
