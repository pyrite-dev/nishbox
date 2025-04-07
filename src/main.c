/* NishBox */
#include <ne_core.h>

/* External library */

/* Standard */
#include <stdio.h>

ne_engine_t* engine;

int main(int argc, char** argv) {
	ne_engine_begin();
	engine = ne_engine_create(0);
	if(engine == NULL) {
		fprintf(stderr, "Engine creation failure\n");
		ne_engine_end();
		return 1;
	}
	ne_engine_loop(engine);
	ne_engine_destroy(engine);
	ne_engine_end();

	return 0;
}
