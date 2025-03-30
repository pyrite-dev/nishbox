#include "nb_pre.h"

/* External library */

/* Interface */
#include "nb_version.h"

/* NishBox */

/* Standard */
#include <string.h>
#include <stdlib.h>

#define NB_VERSION "1.0.0"

void nb_get_version(nb_version_t* version) {
	char* cpstr = malloc(strlen(NB_VERSION) + 1);
	int   i;
	int   incr = 0;
	int   old  = 0;
	strcpy(cpstr, NB_VERSION);
	strcpy(version->full, NB_VERSION);
#if defined(USE_GLX)
	strcpy(version->opengl, "GLX");
#elif defined(USE_WGL)
	strcpy(version->opengl, "WGL");
#endif
	for(i = 0;; i++) {
		if(cpstr[i] == '.' || cpstr[i] == 0) {
			int num;
			cpstr[i] = 0;
			num	 = atoi(cpstr + old);
			if(incr == 0) {
				version->major = num;
			} else if(incr == 1) {
				version->minor = num;
			} else if(incr == 2) {
				version->patch = num;
			}
			old = i + 1;
			incr++;
			if(incr == 3) break;
		}
	}
}
