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
#include <stdio.h>

void gf_engine_begin(void) {
	gf_version_t ver;
#ifdef _WIN32
	WSADATA wsa;
#endif
	gf_version_get(&ver);
	gf_log_function(NULL, "GoldFish Engine %s", ver.full);
	gf_log_function(NULL, "Build date: %s", ver.date);
	gf_log_function(NULL, "Lua %s", ver.lua);
	gf_log_function(NULL, "zlib %s", ver.zlib);
	gf_log_function(NULL, "Thread model: %s", ver.thread);
	gf_log_function(NULL, "Renderer: %s on %s", ver.driver, ver.backend);
#ifdef _WIN32
	WSAStartup(MAKEWORD(1, 1), &wsa);
	gf_log_function(NULL, "Winsock ready", "");
#endif
	gf_draw_begin();
	gf_physics_begin();
}

void gf_engine_end(void) {
	gf_physics_end();
	gf_draw_end();
}

gf_engine_t* gf_engine_create(const char* title, int nogui) {
	gf_engine_t* engine = malloc(sizeof(*engine));
	memset(engine, 0, sizeof(*engine));
	engine->log = stderr;
	if(nogui) {
		gf_log_function(NULL, "No GUI mode", "");
		engine->draw = NULL;
	} else {
		gf_log_function(NULL, "GUI mode", "");
		engine->draw = gf_draw_create(engine, title);
		if(engine->draw == NULL) {
			gf_log_function(NULL, "Failed to create drawing interface", "");
			free(engine);
			return NULL;
		}
		gf_log_function(engine, "Switching to graphical console", "");
	}
	engine->physics = gf_physics_create();
	return engine;
}

void gf_engine_set_draw(gf_engine_t* engine, void (*func)(gf_draw_t*)) { gf_draw_set_draw(engine->draw, func); }

/**
 * Writing this so I don't forget
 *
 * 1. Calls gf_draw_step
 * 2. gf_draw_step calls gf_draw_platform_step (Platform-dependent)
 * 3. gf_draw_platform_step processes platform-dependent stuffs (e.g. events)
 * 4. gf_draw_platform_step calls gf_draw_driver_before
 * 5. gf_draw_platform_step calls gf_draw_frame
 * 6. gf_draw_frame calls gf_draw_t.draw to draw frame
 * 7. gf_draw_frame draws more stuffs if required
 * 8. gf_draw_platform_step calls gf_draw_driver_after
 * 9. gf_draw_platform_step swaps buffers
 *10. Comes back here
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
	gf_log_function(NULL, "Destroyed engine", "");
}
