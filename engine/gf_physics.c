#define GF_EXPOSE_PHYSICS

#include <gf_pre.h>

/* External library */
#include <ode/ode.h>

/* Interface */
#include <gf_physics.h>

/* Engine */
#include <gf_log.h>

/* Standard */
#include <stdlib.h>

GF_EXPORT void gf_physics_begin(void) { dInitODE(); }

GF_EXPORT void gf_physics_end(void) { dCloseODE(); }

GF_EXPORT gf_physics_t* gf_physics_create(void) {
	gf_physics_t* physics = malloc(sizeof(*physics));
	physics->id	      = dWorldCreate();
	dWorldSetGravity(physics->id, 0, 0, -9.81);
	return physics;
}

GF_EXPORT void gf_physics_destroy(gf_physics_t* physics) {
	dWorldDestroy(physics->id);
	free(physics);
	gf_function_log(NULL, "Destroyed physics", "");
}
