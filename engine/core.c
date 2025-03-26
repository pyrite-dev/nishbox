#include "nb_core.h"

#include <ode/ode.h>

void nb_engine_init(nb_engine_t* engine){
	engine->world = dWorldCreate();
	dWorldSetGravity(engine->world, 0, 0, -9.81);
}

void nb_engine_destroy(nb_engine_t* engine){
	dWorldDestroy(engine->world);
}
