#ifndef __GF_PHYSICS_H__
#define __GF_PHYSICS_H__

#include <gf_pre.h>
#include <gf_macro.h>

/* Type */
#include <gf_type/physics.h>

/* Engine */

/* Standard */

void	      gf_physics_begin(void);
void	      gf_physics_end(void);
gf_physics_t* gf_physics_create(void);
void	      gf_physics_destroy(gf_physics_t* physics);

#endif
