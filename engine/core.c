#include "nb_core.h"

#include <ode/ode.h>

void nb_engine_begin(void){
	dInitODE();
}

void nb_engine_end(void){
	dCloseODE();
}

void nb_engine_create(nb_engine_t* engine){
	engine->world = dWorldCreate();
	dWorldSetGravity(engine->world, 0, 0, -9.81);
}

void nb_engine_destroy(nb_engine_t* engine){
	dWorldDestroy(engine->world);
}
