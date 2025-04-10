#ifndef __GF_CORE_H__
#define __GF_CORE_H__

#include <gf_pre.h>
#include <gf_macro.h>

/* Type */
#include <gf_type/core.h>

/* Engine */
#include <gf_type/draw.h>

/* Standard */

void	     gf_engine_begin(void);
void	     gf_engine_end(void);
gf_engine_t* gf_engine_create(int nogui);
void	     gf_engine_loop(gf_engine_t* engine);
void	     gf_engine_set_draw(gf_engine_t* engine, void (*func)(gf_draw_t*));
void	     gf_engine_destroy(gf_engine_t* engine);

#endif
