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

float gf_log2(float x);
void  gf_calculate_normal(gf_vector_t* r, gf_vector_t v0, gf_vector_t v1, gf_vector_t v2);

#endif
