#ifndef __NE_PHYSICS_H__
#define __NE_PHYSICS_H__

#include <ne_pre.h>
#include <ne_macro.h>

/* Type */
#include <ne_type/physics.h>

/* NishBox */

/* Standard */

void	      ne_physics_begin(void);
void	      ne_physics_end(void);
ne_physics_t* ne_physics_create(void);
void	      ne_physics_destroy(ne_physics_t* physics);

#endif
