/* NishBox */
#include <nb_version.h>
#include <nb_core.h>

/* External library */

/* Standard */
#include <stdio.h>

nb_engine_t* engine;

int main(int argc, char** argv) {
	nb_version_t ver;
	nb_get_version(&ver);
	printf("NishBox engine %s - Powered by Pawn and ODE\n", ver.full);

	nb_engine_begin();
	engine = nb_engine_create();
	if(engine == NULL) {
		fprintf(stderr, "Engine creation failure\n");
		nb_engine_end();
		return 1;
	}
	nb_engine_destroy(engine);
	nb_engine_end();

	return 0;
}
