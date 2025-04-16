#define GF_EXPOSE_DRAW

/* Engine */
#include <gf_core.h>
#include <gf_gui.h>
#include <gf_version.h>

/* External library */

/* Standard */
#include <stdio.h>
#include <string.h>

gf_engine_t* engine;

int main(int argc, char** argv) {
	char	     title[64];
	gf_version_t ver;
	gf_version_get(&ver);
	sprintf(title, "NishBox %s (%s on %s)", ver.full, ver.driver, ver.backend);
	gf_engine_begin();
	engine = gf_engine_create(title, 0);
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
