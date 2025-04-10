#include <gf_pre.h>

/* External library */
#include <ode/odemath.h>

/* Interface */
#include <gf_math.h>

/* Engine */

/* Standard */
#include <string.h>
#include <stdlib.h>
#include <math.h>

GF_EXPORT float gf_log2(float x) { return log(x) / log(2); }

GF_EXPORT void gf_calculate_normal(gf_vector_t* r, gf_vector_t v0, gf_vector_t v1, gf_vector_t v2) {
	int	    i;
	dReal	    length;
	gf_vector_t vec;
	dReal	    res[3];
	dReal	    tmp0[3];
	dReal	    tmp1[3];
	dReal	    a[3]; /* v1 - v0 */
	dReal	    b[3]; /* v2 - v0 */

	GF_VECTOR_COPY(tmp0, v1);
	GF_VECTOR_COPY(tmp1, v0);
	dSubtractVectors3(a, tmp0, tmp1); /* v1 - v0 */

	GF_VECTOR_COPY(tmp0, v2);
	GF_VECTOR_COPY(tmp1, v0);
	dSubtractVectors3(b, tmp0, tmp1); /* v2 - v0 */

	dCalcVectorCross3(res, a, b);

	length = dCalcVectorLength3(res);
	GF_VECTOR_COPY(res, vec);

	vec[0] /= length;
	vec[1] /= length;
	vec[2] /= length;

	memcpy(*r, vec, sizeof(vec));
}
