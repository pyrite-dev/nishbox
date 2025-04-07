#define NE_EXPOSE_CORE

#include <ne_pre.h>

/* External library */
#ifdef _WIN32
#include <winsock.h>
#endif

/* Interface */
#include <ne_core.h>

/* NishBox */
#include <ne_draw.h>
#include <ne_physics.h>
#include <ne_log.h>
#include <ne_version.h>

/* Standard */
#include <stdlib.h>
#include <string.h>

void ne_engine_begin(void) {
	ne_version_t ver;
#ifdef _WIN32
	WSADATA wsa;
#endif
	ne_get_version(&ver);
	ne_function_log("NishEngine %s", ver.full);
	ne_function_log("Lua %s", ver.lua);
	ne_function_log("zlib %s", ver.zlib);
	ne_function_log("Thread model: %s", ver.thread);
	ne_function_log("OpenGL backend: %s", ver.opengl);
#ifdef _WIN32
	WSAStartup(MAKEWORD(1, 1), &wsa);
	ne_function_log("Winsock ready", "");
#endif
	ne_draw_begin();
	ne_physics_begin();
}

void ne_engine_end(void) {
	ne_physics_end();
	ne_draw_end();
}

ne_engine_t* ne_engine_create(int nogui) {
	ne_engine_t* engine = malloc(sizeof(*engine));
	memset(engine, 0, sizeof(*engine));
	if(nogui) {
		ne_function_log("No GUI mode", "");
		engine->draw = NULL;
	} else {
		ne_function_log("GUI mode", "");
		engine->draw = ne_draw_create();
		if(engine->draw == NULL) {
			ne_function_log("Failed to create drawing interface", "");
			free(engine);
			return NULL;
		}
	}
	engine->physics = ne_physics_create();
	return engine;
}

/**
 * Writing this so I don't forget
 *
 * 1. Calls ne_draw_step
 * 2. ne_draw_step calls _ne_draw_step (Platform-dependent)
 * 3. _ne_draw_step processes platform-dependent stuffs (e.g. events)
 * 4. _ne_draw_step calls ne_draw_driver_before
 * 4. _ne_draw_step calls ne_draw_frame
 * 5. ne_draw_frame draws frame
 * 4. _ne_draw_step calls ne_draw_driver_after
 * 6. _ne_draw_step swaps buffers
 * 7. Comes back here
 */
void ne_engine_loop(ne_engine_t* engine) {
	while(1) {
		if(engine->draw != NULL) {
			if(ne_draw_step(engine->draw) != 0) break;
		}
	}
}

void ne_engine_destroy(ne_engine_t* engine) {
	if(engine->physics != NULL) ne_physics_destroy(engine->physics);
	if(engine->draw != NULL) ne_draw_destroy(engine->draw);
	free(engine);
	ne_function_log("Destroyed engine", "");
}
