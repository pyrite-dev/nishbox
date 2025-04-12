/**
 * Core of the engine
 *
 * Including this should (will) be enough for usual case,
 * at least in the future.
 */

#ifndef __GF_CORE_H__
#define __GF_CORE_H__

#include <gf_pre.h>
#include <gf_macro.h>

/* Type */
#include <gf_type/core.h>

/* Engine */
#include <gf_type/draw.h>

/* Standard */

GF_EXPORT void	       gf_engine_begin(void);
GF_EXPORT void	       gf_engine_end(void);
GF_EXPORT gf_engine_t* gf_engine_create(const char* title, int nogui);
GF_EXPORT void	       gf_engine_loop(gf_engine_t* engine);
GF_EXPORT void	       gf_engine_set_draw(gf_engine_t* engine, void (*func)(gf_draw_t*));
GF_EXPORT void	       gf_engine_destroy(gf_engine_t* engine);

#endif
