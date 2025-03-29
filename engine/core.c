/* Interface */
#include "nb_core.h"

/* NishBox */
#include "nb_draw.h"

/* External library */
#include <ode/ode.h>

/* Standard */
#include <stdlib.h>

void nb_engine_begin(void) { dInitODE(); }

void nb_engine_end(void) { dCloseODE(); }

nb_engine_t* nb_engine_create(void) {
	nb_engine_t* engine = malloc(sizeof(*engine));
	engine->draw	    = nb_draw_create();
	if(engine->draw == NULL) {
		free(engine);
		return NULL;
	}
	engine->world = dWorldCreate();
	dWorldSetGravity(engine->world, 0, 0, -9.81);
	return engine;
}

void nb_engine_destroy(nb_engine_t* engine) { dWorldDestroy(engine->world); }
