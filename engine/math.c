#define NB_EXPOSE_MATH

#include "nb_pre.h"

/* External library */
#include <ode/odemath.h>

/* Interface */
#include "nb_math.h"

/* NishBox */

/* Standard */
#include <stdlib.h>
#include <math.h>

float nb_log2(float x) { return log(x) / log(2); }

nb_vector_t nb_calculate_normal(nb_vector_t v0, nb_vector_t v1, nb_vector_t v2) {
	int	    i;
	dReal	    length;
	nb_vector_t vec = malloc(sizeof(*vec) * 3);
	dReal	    res[3];
	dReal	    tmp0[3];
	dReal	    tmp1[3];
	dReal	    a[3]; /* v1 - v0 */
	dReal	    b[3]; /* v2 - v0 */

	NB_VECTOR_COPY(tmp0, v1);
	NB_VECTOR_COPY(tmp1, v0);
	dSubtractVectors3(a, tmp0, tmp1); /* v1 - v0 */

	NB_VECTOR_COPY(tmp0, v2);
	NB_VECTOR_COPY(tmp1, v0);
	dSubtractVectors3(b, tmp0, tmp1); /* v2 - v0 */

	dCalcVectorCross3(res, a, b);

	length = dCalcVectorLength3(res);
	NB_VECTOR_COPY(res, vec);

	vec[0] /= length;
	vec[1] /= length;
	vec[2] /= length;

	return vec;
}
