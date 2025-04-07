#ifndef __NE_TYPE_MESH_H__
#define __NE_TYPE_MESH_H__

#include <ne_pre.h>
#include <ne_macro.h>

#ifdef NE_EXPOSE_MESH
/* External library */

/* NishBox */
#include <ne_type/math.h>

/* Standard */

NE_DECLARE_TYPE(shape, {
	ne_vector_t points[3];
	ne_vector_t color;
});

NE_DECLARE_TYPE(mesh, {
	ne_shape_t* shapes;
	int	    shape_count;
});
#else
typedef void ne_mesh_t;
typedef void ne_shape_t;
#endif

#endif
