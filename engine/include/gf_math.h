/**
 * Math
 *
 * Provides the functions missing in C89, and ones useful
 * for 3D stuffs.
 */

#ifndef __GF_MATH_H__
#define __GF_MATH_H__

#include <gf_pre.h>
#include <gf_macro.h>

/* Type */
#include <gf_type/math.h>

/* Engine */

/* Standard */

#define GF_VECTOR_COPY(from, to) \
	to[0] = from[0]; \
	to[1] = from[1]; \
	to[2] = from[2]

GF_EXPORT float gf_math_log2(float x);
GF_EXPORT void	gf_math_normal(gf_vector_t* r, gf_vector_t v0, gf_vector_t v1, gf_vector_t v2);

#endif
