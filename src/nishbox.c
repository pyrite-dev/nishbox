#include "macro.h"

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

#ifdef _WIN32
char* get_registry(const char* main, const char* sub){
	DWORD bufsize = 512;
	HKEY handle;
	char* value = malloc(513);
	int err = RegOpenKeyEx(HKEY_LOCAL_MACHINE, main, 0, KEY_QUERY_VALUE, &handle);
	if(err = ERROR_SUCCESS){
		err = RegQueryValueEx(handle, sub, NULL, NULL, value, &bufsize);
		if(err != ERROR_SUCCESS){
			free(value);
			RegCloseKey(handle);
			return NULL;
		}
		RegCloseKey(handle);
		return value;
	}else{
		free(value);
		return NULL;
	}
}
#else
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
	FILE*	     f;
	int	     nogui = 0;
	int	     i;
#ifdef _WIN32
	char* regpath = get_registry("Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\NishBox", "InstallDir");
#endif

	for(i = 1; i < argc; i++) {
		if(strcmp(argv[i], "-dedicated") == 0) {
			nogui = 1;
		}
	}

	gf_version_get(&ver);
#ifndef _WIN32
	signal(SIGINT, handle_signal);
#else
	if(!nogui) {
		FreeConsole();
		gf_log_default = fopen("nishbox.log", "w");
	}
#endif
	gf_engine_begin();
#ifdef DEBUG
	engine = gf_engine_create_ex("NishBox", nogui, "data", argv, argc);
#else
	f = fopen("base.pak", "r");
	if(f != NULL) {
		fclose(f);
		engine = gf_engine_create_ex("NishBox", nogui, NULL, argv, argc);
	} else {
		engine = gf_engine_create_ex("NishBox", nogui, PREFIX "/share/nishbox/base.pak", argv, argc);
	}
#endif
	if(engine == NULL) {
		fprintf(stderr, "Engine creation failure\n");
		gf_engine_end();
		return 1;
	}
#ifdef _WIN32
	if(regpath == NULL){
		gf_engine_prefix(engine, PREFIX);
	}else{
		gf_engine_prefix(engine, regpath);
	}
#else
	gf_engine_prefix(engine, PREFIX "/share");
#endif
	gf_engine_name(engine, "NishBox");
	gf_engine_loop(engine);
	gf_engine_destroy(engine);
	gf_engine_end();

#ifdef _WIN32
	if(gf_log_default != NULL && !nogui) fclose(gf_log_default);
	if(regpath != NULL) free(regpath);
#endif

	return 0;
}
