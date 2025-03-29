#ifndef __NB_VERSION_H__
#define __NB_VERSION_H__

#include <nb_macro.h>

/* External library */

/* NishBox */

/* Standard */

typedef struct nb_version {
	int  major;
	int  minor;
	int  patch;
	char full[64];
	char opengl[32];
} nb_version_t;

void nb_get_version(nb_version_t* version);

#endif
