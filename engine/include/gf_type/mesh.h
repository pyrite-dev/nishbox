#ifndef __GF_TYPE_MESH_H__
#define __GF_TYPE_MESH_H__

#include <gf_pre.h>
#include <gf_macro.h>

#ifdef GF_EXPOSE_MESH
/* External library */

/* Engine */
#include <gf_type/math.h>

/* Standard */

GF_DECLARE_TYPE(shape, {
	gf_vector_t points[3];
	gf_vector_t color;
});

GF_DECLARE_TYPE(mesh, {
	gf_shape_t* shapes;
	int	    shape_count;
});
#else
typedef void gf_mesh_t;
typedef void gf_shape_t;
#endif

#endif
