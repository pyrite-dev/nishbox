#include "nb_core.h"

#include <ode/ode.h>

void nb_engine_init(nb_engine_t* engine){
	engine->world = dWorldCreate();
}

void nb_engine_destroy(nb_engine_t* engine){
	dWorldDestroy(engine->world);
}
