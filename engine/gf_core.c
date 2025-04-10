#define GF_EXPOSE_CORE

#include <gf_pre.h>

/* External library */
#ifdef _WIN32
#include <winsock.h>
#endif

/* Interface */
#include <gf_core.h>

/* Engine */
#include <gf_draw.h>
#include <gf_physics.h>
#include <gf_log.h>
#include <gf_version.h>

/* Standard */
#include <stdlib.h>
#include <string.h>

void gf_engine_begin(void) {
	gf_version_t ver;
#ifdef _WIN32
	WSADATA wsa;
#endif
	gf_get_version(&ver);
	gf_function_log("GoldFish Engine %s", ver.full);
	gf_function_log("Lua %s", ver.lua);
	gf_function_log("zlib %s", ver.zlib);
	gf_function_log("Thread model: %s", ver.thread);
	gf_function_log("OpenGL backend: %s", ver.opengl);
#ifdef _WIN32
	WSAStartup(MAKEWORD(1, 1), &wsa);
	gf_function_log("Winsock ready", "");
#endif
	gf_draw_begin();
	gf_physics_begin();
}

void gf_engine_end(void) {
	gf_physics_end();
	gf_draw_end();
}

gf_engine_t* gf_engine_create(int nogui) {
	gf_engine_t* engine = malloc(sizeof(*engine));
	memset(engine, 0, sizeof(*engine));
	if(nogui) {
		gf_function_log("No GUI mode", "");
		engine->draw = NULL;
	} else {
		gf_function_log("GUI mode", "");
		engine->draw = gf_draw_create();
		if(engine->draw == NULL) {
			gf_function_log("Failed to create drawing interface", "");
			free(engine);
			return NULL;
		}
	}
	engine->physics = gf_physics_create();
	return engine;
}

void gf_engine_set_draw(gf_engine_t* engine, void (*func)(gf_draw_t*)) { gf_draw_set_draw(engine->draw, func); }

/**
 * Writing this so I don't forget
 *
 * 1. Calls gf_draw_step
 * 2. gf_draw_step calls _gf_draw_step (Platform-dependent)
 * 3. _gf_draw_step processes platform-dependent stuffs (e.g. events)
 * 4. _gf_draw_step calls gf_draw_driver_before
 * 4. _gf_draw_step calls gf_draw_frame
 * 5. gf_draw_frame draws frame
 * 4. _gf_draw_step calls gf_draw_driver_after
 * 6. _gf_draw_step swaps buffers
 * 7. Comes back here
 */
void gf_engine_loop(gf_engine_t* engine) {
	while(1) {
		if(engine->draw != NULL) {
			if(gf_draw_step(engine->draw) != 0) break;
		}
	}
}

void gf_engine_destroy(gf_engine_t* engine) {
	if(engine->physics != NULL) gf_physics_destroy(engine->physics);
	if(engine->draw != NULL) gf_draw_destroy(engine->draw);
	free(engine);
	gf_function_log("Destroyed engine", "");
}
