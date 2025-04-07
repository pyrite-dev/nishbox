#ifndef __NE_TYPE_CORE_H__
#define __NE_TYPE_CORE_H__

#include <ne_pre.h>
#include <ne_macro.h>

#ifdef NE_EXPOSE_CORE
/* External library */

/* NishBox */
#include <ne_type/physics.h>
#include <ne_type/draw.h>

/* Standard */

NE_DECLARE_TYPE(engine, {
	ne_physics_t* physics;
	ne_draw_t*    draw;
});
#else
typedef void ne_engine_t;
#endif

#endif
