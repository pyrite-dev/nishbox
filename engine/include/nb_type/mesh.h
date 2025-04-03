#ifndef __NB_TYPE_MESH_H__
#define __NB_TYPE_MESH_H__

#include <nb_pre.h>
#include <nb_macro.h>

#ifdef NB_EXPOSE_MESH
/* External library */

/* NishBox */
#include <nb_type/math.h>

/* Standard */

NB_DECLARE_TYPE(shape, {
	nb_vector_t points[3];
	nb_vector_t color;
});

NB_DECLARE_TYPE(mesh, {
	nb_shape_t* shapes;
	int	    shape_count;
});
#else
typedef void nb_mesh_t;
typedef void nb_shape_t;
#endif

#endif
