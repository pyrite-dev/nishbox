#ifndef __NB_TYPE_PHYSICS_H__
#define __NB_TYPE_PHYSICS_H__

#include <nb_pre.h>
#include <nb_macro.h>

#ifdef NB_EXPOSE_PHYSICS
/* External library */
#include <ode/ode.h>

/* NishBox */

/* Standard */

NB_DECLARE_TYPE(physics, { dWorldID id; });
#else
typedef void nb_physics_t;
#endif

#endif
