#ifndef __NE_TYPE_PHYSICS_H__
#define __NE_TYPE_PHYSICS_H__

#include <ne_pre.h>
#include <ne_macro.h>

#ifdef NE_EXPOSE_PHYSICS
/* External library */
#include <ode/ode.h>

/* NishBox */

/* Standard */

NE_DECLARE_TYPE(physics, { dWorldID id; });
#else
typedef void ne_physics_t;
#endif

#endif
