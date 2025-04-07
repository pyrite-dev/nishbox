#ifndef __NE_TYPE_VERSION_H__
#define __NE_TYPE_VERSION_H__

#include <ne_pre.h>
#include <ne_macro.h>

#ifdef NE_EXPOSE_VERSION
/* External library */

/* NishBox */

/* Standard */

NE_DECLARE_TYPE(version, {
	int  major;
	int  minor;
	int  patch;
	char full[64];
	char opengl[32];
	char lua[32];
	char zlib[32];
	char thread[32];
});
#else
#error "should not happen!"
#endif

#endif
