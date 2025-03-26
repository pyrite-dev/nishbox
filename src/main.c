#include <nb_version.h>
#include <nb_core.h>

#include <stdio.h>

nb_engine_t engine;

int main(int argc, char** argv) {
	nb_version_t ver;
	nb_get_version(&ver);
	printf("NishBox engine %s - Powered by Pawn and ODE\n", ver.full);
	nb_engine_init(&engine);
	nb_engine_destroy(&engine);
	return 0;
}
