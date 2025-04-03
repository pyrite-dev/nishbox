#define NB_EXPOSE_CORE

#include "nb_pre.h"

/* External library */
#include <ode/ode.h>
#ifdef _WIN32
#include <winsock.h>
#endif

#include <lua.h>

/* Interface */
#include "nb_core.h"

/* NishBox */
#include "nb_draw.h"
#include "nb_physics.h"
#include "nb_log.h"
#include "nb_version.h"

/* Standard */
#include <stdlib.h>
#include <string.h>

void nb_engine_begin(void) {
	nb_version_t ver;
#ifdef _WIN32
	WSADATA wsa;
#endif
	nb_get_version(&ver);
	nb_function_log("NishBox engine %s", ver.full);
	nb_function_log("%s", LUA_RELEASE);
	nb_function_log("OpenGL backend: %s", ver.opengl);
#ifdef _WIN32
	WSAStartup(MAKEWORD(1, 1), &wsa);
	nb_function_log("Winsock ready", "");
#endif
	nb_draw_begin();
	nb_physics_begin();
}

void nb_engine_end(void) {
	nb_physics_end();
	nb_draw_end();
}

nb_engine_t* nb_engine_create(int nogui) {
	nb_engine_t* engine = malloc(sizeof(*engine));
	memset(engine, 0, sizeof(*engine));
	if(nogui) {
		nb_function_log("No GUI mode", "");
		engine->draw = NULL;
	} else {
		nb_function_log("GUI mode", "");
		engine->draw = nb_draw_create();
		if(engine->draw == NULL) {
			nb_function_log("Failed to create drawing interface", "");
			free(engine);
			return NULL;
		}
	}
	engine->physics = nb_physics_create();
	return engine;
}

/**
 * Writing this so I don't forget
 *
 * 1. Calls nb_draw_step
 * 2. nb_draw_step calls _nb_draw_step (Platform-dependent)
 * 3. _nb_draw_step processes platform-dependent stuffs (e.g. events)
 * 4. _nb_draw_step calls nb_draw_frame
 * 5. nb_draw_frame draws frame
 * 6. _nb_draw_step swaps buffers
 * 7. Comes back here
 */
void nb_engine_loop(nb_engine_t* engine) {
	while(1) {
		if(engine->draw != NULL) {
			if(nb_draw_step(engine->draw) != 0) break;
		}
	}
}

void nb_engine_destroy(nb_engine_t* engine) {
	if(engine->physics != NULL) nb_physics_destroy(engine->physics);
	if(engine->draw != NULL) nb_draw_destroy(engine->draw);
	free(engine);
	nb_function_log("Destroyed engine", "");
}
