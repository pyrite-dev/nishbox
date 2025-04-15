/**
 * @file gf_math.h
 * @~english
 * @brief Math
 */

#ifndef __GF_MATH_H__
#define __GF_MATH_H__

#include <gf_pre.h>
#include <gf_macro.h>

/* Type */
#include <gf_type/math.h>

/* Engine */

/* Standard */

/**
 * @~english
 * @brief Copy vector
 * @param from Source
 * @param to Destination
 */
#define GF_VECTOR_COPY(from, to) \
	to[0] = from[0]; \
	to[1] = from[1]; \
	to[2] = from[2]

/**
 * @~english
 * @brief Calculate log2(x)
 * @param x Input
 */
GF_EXPORT float gf_math_log2(float x);

/**
 * @~english
 * @brief Calculate normal of triangle v0,v1,v2
 * @param r Result
 * @param v0 Input
 * @param v1 Input
 * @param v2 Input
 */
GF_EXPORT void gf_math_normal(gf_vector_t* r, gf_vector_t v0, gf_vector_t v1, gf_vector_t v2);

#endif
