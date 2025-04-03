#ifndef __NB_TYPE_MODEL_H__
#define __NB_TYPE_MODEL_H__

#include <nb_pre.h>
#include <nb_macro.h>

#ifdef NB_EXPOSE_MODEL
/* External library */

/* NishBox */
#include <nb_type/mesh.h>
#include <nb_type/texture.h>

/* Standard */

NB_DECLARE_TYPE(model, {
	nb_mesh_t*    mesh;
	nb_texture_t* texture;
});
#else
typedef void nb_model_t;
#endif

#endif
