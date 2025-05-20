/* Engine */
#include <gf_core.h>

/* External library */

/* Standard */
#include <stdio.h>
#include <string.h>

gf_engine_t* engine;

int main(int argc, char** argv) {
	FILE* f;
	gf_engine_begin();
#if 0
	engine = gf_engine_create_ex("unused", 0, "data");
#else
	f = fopen("base.pak", "r");
	if(f != NULL){
		fclose(f);
		engine = gf_engine_create("unused", 0);
	}else{
		engine = gf_engine_create_ex("unused", 0, PREFIX "/share/nishbox/base.pak");
	}
#endif
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
