#define GF_EXPOSE_CLIENT
#define GF_EXPOSE_DRAW

#include <gf_pre.h>

/* External library */

/* Interface */
#include <gf_client.h>

/* Engine */
#include <gf_draw.h>
#include <gf_log.h>
#include <gf_input.h>
#include <gf_audio.h>
#include <gf_font.h>
#include <gf_resource.h>

/* Standard */
#include <stdlib.h>
#include <string.h>

void gf_client_begin(void) { gf_draw_begin(); }

void gf_client_end(void) { gf_draw_end(); }

gf_client_t* gf_client_create(gf_engine_t* engine, const char* title) {
	size_t	     sz;
	void*	     fontdata;
	gf_client_t* client = malloc(sizeof(*client));
	memset(client, 0, sizeof(*client));
	client->engine = engine;
	client->draw   = gf_draw_create(engine, title);
	if(client->draw == NULL) {
		gf_log_function(engine, "Failed to create drawing interface", "");
		gf_client_destroy(client);
		return NULL;
	}
	client->audio = gf_audio_create(engine);
	if(client->audio == NULL) {
		gf_log_function(engine, "Failed to create audio interface", "");
		gf_client_destroy(client);
		return NULL;
	}
	client->input = gf_input_create(engine);
	gf_draw_set_input(client->draw, client->input);

	client->base = gf_resource_create(engine, "base.pak");

	client->draw->font = gf_font_create_file(client->draw, "base:font/default.bdf");

	return client;
}

void gf_client_destroy(gf_client_t* client) {
	if(client->draw != NULL) gf_draw_destroy(client->draw);
	if(client->audio != NULL) gf_audio_destroy(client->audio);
	if(client->input != NULL) gf_input_destroy(client->input);

	if(client->base != NULL) gf_resource_destroy(client->base);
	gf_log_function(client->engine, "Destroyed client interface", "");
	free(client);
}

int gf_client_step(gf_client_t* client) {
	int s = gf_draw_step(client->draw);
	return s;
}
