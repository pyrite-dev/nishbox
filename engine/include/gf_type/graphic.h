#ifndef __GF_TYPE_GRAPHIC_H__
#define __GF_TYPE_GRAPHIC_H__

#include <gf_pre.h>
#include <gf_macro.h>

#ifdef GF_EXPOSE_GRAPHIC
/* External library */

/* Engine */

/* Standard */

GF_DECLARE_TYPE(color, {
	double r;
	double g;
	double b;
	double a;
});
#else
#error "should not happen!"
#endif

#endif
