#ifndef __NE_MATH_H__
#define __NE_MATH_H__

#include <ne_pre.h>
#include <ne_macro.h>

/* Type */
#include <ne_type/math.h>

/* NishBox */

/* Standard */

#define NE_VECTOR_COPY(from, to) \
	to[0] = from[0]; \
	to[1] = from[1]; \
	to[2] = from[2]

float ne_log2(float x);
void  ne_calculate_normal(ne_vector_t* r, ne_vector_t v0, ne_vector_t v1, ne_vector_t v2);

#endif
