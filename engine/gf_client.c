#define GF_EXPOSE_CLIENT

#include <gf_pre.h>

/* External library */

/* Interface */
#include <gf_client.h>

/* Engine */
#include <gf_draw.h>
#include <gf_log.h>

/* Standard */
#include <stdlib.h>
#include <string.h>

void gf_client_begin(void) { gf_draw_begin(); }

void gf_client_end(void) { gf_draw_end(); }

gf_client_t* gf_client_create(gf_engine_t* engine, const char* title) {
	gf_client_t* client = malloc(sizeof(*client));
	memset(client, 0, sizeof(*client));
	client->engine = engine;
	client->draw   = gf_draw_create(engine, title);
	if(client->draw == NULL) {
		gf_log_function(engine, "Failed to create drawing interface", "");
		gf_client_destroy(client);
		return NULL;
	}
	return client;
}

void gf_client_destroy(gf_client_t* client) {
	if(client->draw != NULL) gf_draw_destroy(client->draw);
	gf_log_function(client->engine, "Destroyed client interface", "");
	free(client);
}

int gf_client_step(gf_client_t* client) {
	int s = gf_draw_step(client->draw);
	return s;
}
