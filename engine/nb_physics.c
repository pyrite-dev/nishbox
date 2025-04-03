#define NB_EXPOSE_PHYSICS

#include "nb_pre.h"

/* External library */
#include <ode/ode.h>

/* Interface */
#include "nb_physics.h"

/* NishBox */
#include "nb_log.h"

/* Standard */
#include <stdlib.h>

void nb_physics_begin(void) { dInitODE(); }

void nb_physics_end(void) { dCloseODE(); }

nb_physics_t* nb_physics_create(void) {
	nb_physics_t* physics = malloc(sizeof(*physics));
	physics->id	      = dWorldCreate();
	dWorldSetGravity(physics->id, 0, 0, -9.81);
	return physics;
}

void nb_physics_destroy(nb_physics_t* physics) {
	dWorldDestroy(physics->id);
	free(physics);
	nb_function_log("Destroyed physics", "");
}
