#ifndef __NB_CORE_H__
#define __NB_CORE_H__

#include <nb_pre.h>
#include <nb_macro.h>

/* Type */
#include <nb_type/core.h>

/* NishBox */

/* Standard */

void	     nb_engine_begin(void);
void	     nb_engine_end(void);
nb_engine_t* nb_engine_create(int nogui);
void	     nb_engine_loop(nb_engine_t* engine);
void	     nb_engine_destroy(nb_engine_t* engine);

#endif
