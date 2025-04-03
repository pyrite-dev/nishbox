#ifndef __NB_TYPE_VERSION_H__
#define __NB_TYPE_VERSION_H__

#include <nb_pre.h>
#include <nb_macro.h>

#ifdef NB_EXPOSE_VERSION
/* External library */

/* NishBox */

/* Standard */

NB_DECLARE_TYPE(version, {
	int  major;
	int  minor;
	int  patch;
	char full[64];
	char opengl[32];
	char lua[32];
	char zlib[32];
});
#else
#error "should not happen!"
#endif

#endif
