#ifndef __GF_TYPE_VERSION_H__
#define __GF_TYPE_VERSION_H__

#include <gf_pre.h>
#include <gf_macro.h>

#ifdef GF_EXPOSE_VERSION
/* External library */

/* Engine */

/* Standard */

GF_DECLARE_TYPE(version, {
	int  major;
	int  minor;
	int  patch;
	char full[64];
	char backend[32];
	char driver[32];
	char lua[32];
	char zlib[32];
	char thread[32];
});
#else
#error "should not happen!"
#endif

#endif
