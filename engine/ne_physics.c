#define NE_EXPOSE_PHYSICS

#include <ne_pre.h>

/* External library */
#include <ode/ode.h>

/* Interface */
#include <ne_physics.h>

/* NishBox */
#include <ne_log.h>

/* Standard */
#include <stdlib.h>

void ne_physics_begin(void) { dInitODE(); }

void ne_physics_end(void) { dCloseODE(); }

ne_physics_t* ne_physics_create(void) {
	ne_physics_t* physics = malloc(sizeof(*physics));
	physics->id	      = dWorldCreate();
	dWorldSetGravity(physics->id, 0, 0, -9.81);
	return physics;
}

void ne_physics_destroy(ne_physics_t* physics) {
	dWorldDestroy(physics->id);
	free(physics);
	ne_function_log("Destroyed physics", "");
}
