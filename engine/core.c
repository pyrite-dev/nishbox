#define NB_EXPOSE_CORE

/* External library */

/* Interface */
#include "nb_core.h"

/* NishBox */
#include "nb_draw.h"
#include "nb_log.h"
#include "nb_version.h"

/* Standard */
#include <stdlib.h>

void nb_engine_begin(void) {
	nb_version_t ver;
	nb_get_version(&ver);
	nb_function_log("NishBox engine %s", ver.full);
	nb_function_log("OpenGL backend: %s", ver.opengl);
	dInitODE();
}

void nb_engine_end(void) { dCloseODE(); }

nb_engine_t* nb_engine_create(void) {
	nb_engine_t* engine = malloc(sizeof(*engine));
	engine->draw	    = nb_draw_create();
	if(engine->draw == NULL) {
		nb_function_log("Failed to create drawing interface", "");
		free(engine);
		return NULL;
	}
	engine->world = dWorldCreate();
	dWorldSetGravity(engine->world, 0, 0, -9.81);
	return engine;
}

void nb_engine_destroy(nb_engine_t* engine) { dWorldDestroy(engine->world); }
