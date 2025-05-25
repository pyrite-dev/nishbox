/* Engine */
#include <gf_core.h>
#include <gf_version.h>
#include <gf_log.h>

/* External library */

/* Standard */
#include <stdio.h>
#include <string.h>
#ifndef _WIN32
#include <signal.h>
#else
#include <windows.h>
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
	FILE* f;
	int nogui = 0;
	int i;

	for(i = 1; i < argc; i++){
		if(strcmp(argv[i], "-dedicated") == 0){
			nogui = 1;
		}
	}

	gf_version_get(&ver);
#ifndef _WIN32
	signal(SIGINT, handle_signal);
#else
	if(!nogui){
		FreeConsole();
		gf_log_default = fopen("nishbox.log", "w");
	}
#endif
	gf_engine_begin();
#if 0
	engine = gf_engine_create_ex("NishBox", nogui, "data", argv, argc);
#else
	f = fopen("base.pak", "r");
	if(f != NULL){
		fclose(f);
		engine = gf_engine_create_ex("NishBox", nogui, NULL, argv, argc);
	}else{
		engine = gf_engine_create_ex("NishBox", nogui, PREFIX "/share/nishbox/base.pak", argv, argc);
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

#ifdef _WIN32
	if(gf_log_default != NULL && !nogui) fclose(gf_log_default);
#endif

	return 0;
}
