/* Engine */
#include <gf_core.h>
#include <gf_version.h>

/* External library */

/* Standard */
#include <stdio.h>
#include <string.h>
#ifndef _WIN32
#include <signal.h>
#endif

gf_engine_t* engine = NULL;

#ifndef _WIN32
void handle_signal(int sig) {
	if(sig == SIGINT) {
		if(engine != NULL) {
			gf_engine_shutdown(engine);
		}
	}
}
#endif

int main(int argc, char** argv) {
	gf_version_t ver;
	gf_version_get(&ver);
#ifndef _WIN32
	signal(SIGINT, handle_signal);
#endif
	gf_engine_begin();
	engine = gf_engine_create("NishBox", 0);
	if(engine == NULL) {
		fprintf(stderr, "Engine creation failure\n");
		gf_engine_end();
		return 1;
	}
	gf_engine_loop(engine);
	gf_engine_destroy(engine);
	gf_engine_end();

	return 0;
}
