/* Engine */
#include <gf_version.h>

/* External library */

/* Standard */
#include <stdio.h>

int main(int argc, char** argv) {
	gf_version_t ver;
	gf_get_version(&ver);

	printf("GoldFish Engine version: %s\n", ver.full);

	return 0;
}
