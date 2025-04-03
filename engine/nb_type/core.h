#ifndef __NB_TYPE_CORE_H__
#define __NB_TYPE_CORE_H__

#include <nb_pre.h>
#include <nb_macro.h>

#ifdef NB_EXPOSE_CORE
/* External library */

/* NishBox */
#include <nb_type/physics.h>
#include <nb_type/draw.h>

/* Standard */

NB_DECLARE_TYPE(engine, {
	nb_physics_t* physics;
	nb_draw_t*    draw;
});
#else
typedef void nb_engine_t;
#endif

#endif
