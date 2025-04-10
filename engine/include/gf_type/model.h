#ifndef __GF_TYPE_MODEL_H__
#define __GF_TYPE_MODEL_H__

#include <gf_pre.h>
#include <gf_macro.h>

#ifdef GF_EXPOSE_MODEL
/* External library */

/* Engine */
#include <gf_type/mesh.h>
#include <gf_type/texture.h>

/* Standard */

GF_DECLARE_TYPE(model, {
	gf_mesh_t*    mesh;
	gf_texture_t* texture;
});
#else
typedef void gf_model_t;
#endif

#endif
