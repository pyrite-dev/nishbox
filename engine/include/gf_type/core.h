#ifndef __GF_TYPE_CORE_H__
#define __GF_TYPE_CORE_H__

#include <gf_pre.h>
#include <gf_macro.h>

#ifdef GF_EXPOSE_CORE
/* External library */

/* Engine */
#include <gf_type/physics.h>
#include <gf_type/draw.h>

/* Standard */

GF_DECLARE_TYPE(engine, {
	gf_physics_t* physics;
	gf_draw_t*    draw;
});
#else
typedef void gf_engine_t;
#endif

#endif
