#ifndef __GF_TYPE_PHYSICS_H__
#define __GF_TYPE_PHYSICS_H__

#include <gf_pre.h>
#include <gf_macro.h>

#ifdef GF_EXPOSE_PHYSICS
/* External library */
#include <ode/ode.h>

/* Engine */

/* Standard */

GF_DECLARE_TYPE(physics, { dWorldID id; });
#else
typedef void gf_physics_t;
#endif

#endif
