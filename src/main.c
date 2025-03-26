#include <nb_version.h>

#include <stdio.h>

int main(int argc, char** argv) {
	nb_version_t ver;
	nb_get_version(&ver);
	printf("NishBox engine %s - Powered by Pawn and ODE\n", ver.full);

	return 0;
}
