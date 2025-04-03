#ifndef __NB_PHYSICS_H__
#define __NB_PHYSICS_H__

#include <nb_pre.h>
#include <nb_macro.h>

/* Type */
#include <nb_type/physics.h>

/* NishBox */

/* Standard */

void	      nb_physics_begin(void);
void	      nb_physics_end(void);
nb_physics_t* nb_physics_create(void);
void	      nb_physics_destroy(nb_physics_t* physics);

#endif
