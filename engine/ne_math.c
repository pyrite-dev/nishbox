#include <ne_pre.h>

/* External library */
#include <ode/odemath.h>

/* Interface */
#include <ne_math.h>

/* NishBox */

/* Standard */
#include <string.h>
#include <stdlib.h>
#include <math.h>

float ne_log2(float x) { return log(x) / log(2); }

void ne_calculate_normal(ne_vector_t* r, ne_vector_t v0, ne_vector_t v1, ne_vector_t v2) {
	int	    i;
	dReal	    length;
	ne_vector_t vec;
	dReal	    res[3];
	dReal	    tmp0[3];
	dReal	    tmp1[3];
	dReal	    a[3]; /* v1 - v0 */
	dReal	    b[3]; /* v2 - v0 */

	NE_VECTOR_COPY(tmp0, v1);
	NE_VECTOR_COPY(tmp1, v0);
	dSubtractVectors3(a, tmp0, tmp1); /* v1 - v0 */

	NE_VECTOR_COPY(tmp0, v2);
	NE_VECTOR_COPY(tmp1, v0);
	dSubtractVectors3(b, tmp0, tmp1); /* v2 - v0 */

	dCalcVectorCross3(res, a, b);

	length = dCalcVectorLength3(res);
	NE_VECTOR_COPY(res, vec);

	vec[0] /= length;
	vec[1] /= length;
	vec[2] /= length;

	memcpy(*r, vec, sizeof(vec));
}
