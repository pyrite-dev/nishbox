#include <ne_pre.h>

/* External library */
#include <lua.h>
#include <zlib.h>

/* Interface */
#include <ne_version.h>

/* NishBox */

/* Standard */
#include <string.h>
#include <stdlib.h>

#define NE_VERSION PACKAGE_VERSION

void ne_get_version(ne_version_t* version) {
	char* cpstr = malloc(512);
	int   i;
	int   incr = 0;
	int   old  = 0;

	strcpy(version->full, NE_VERSION);
	strcpy(version->zlib, ZLIB_VERSION);

	strcpy(cpstr, LUA_RELEASE);
	strcpy(version->lua, cpstr + 4);

#if defined(USE_GLX)
	strcpy(version->opengl, "GLX");
#elif defined(USE_WGL)
	strcpy(version->opengl, "WGL");
#elif defined(USE_GLFW)
	strcpy(version->opengl, "GLFW");
#endif

#if defined(THREAD_WIN32)
	strcpy(version->thread, "Win32");
#elif defined(THREAD_POSIX)
	strcpy(version->thread, "POSIX");
#endif

	strcpy(cpstr, NE_VERSION);
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
