/**
 * @file gf_core.h
 * @~english
 * @brief Core
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

/**
 * @~english
 * @brief Initialize engine
 */
GF_EXPORT void	       gf_engine_begin(void);

/**
 * @~english
 * @brief Cleanup engine
 */
GF_EXPORT void	       gf_engine_end(void);

/**
 * @~english
 * @brief Create engine instance
 * @param title Title to be shown on the window
 * @param nogui `0` to enable client-part, otherwise disable client-part
 */
GF_EXPORT gf_engine_t* gf_engine_create(const char* title, int nogui);

/**
 * @~english
 * @brief Start engine main loop
 * @param engine Engine instance
 */
GF_EXPORT void	       gf_engine_loop(gf_engine_t* engine);

/**
 * @~english
 * @brief Set user-drawing callback
 * @param engine Engine instance
 * @param func Callback
 */
GF_EXPORT void	       gf_engine_set_draw(gf_engine_t* engine, void (*func)(gf_draw_t*));

/**
 * @~english
 * @brief Destroy engine instance
 * @param engine Engine instance
 */
GF_EXPORT void	       gf_engine_destroy(gf_engine_t* engine);

#endif
