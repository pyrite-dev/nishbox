#ifndef __NE_CORE_H__
#define __NE_CORE_H__

#include <ne_pre.h>
#include <ne_macro.h>

/* Type */
#include <ne_type/core.h>

/* NishBox */

/* Standard */

void	     ne_engine_begin(void);
void	     ne_engine_end(void);
ne_engine_t* ne_engine_create(int nogui);
void	     ne_engine_loop(ne_engine_t* engine);
void	     ne_engine_destroy(ne_engine_t* engine);

#endif
