#ifndef __NE_TYPE_MODEL_H__
#define __NE_TYPE_MODEL_H__

#include <ne_pre.h>
#include <ne_macro.h>

#ifdef NE_EXPOSE_MODEL
/* External library */

/* NishBox */
#include <ne_type/mesh.h>
#include <ne_type/texture.h>

/* Standard */

NE_DECLARE_TYPE(model, {
	ne_mesh_t*    mesh;
	ne_texture_t* texture;
});
#else
typedef void ne_model_t;
#endif

#endif
