/**
 * @file gf_type/core.h
 * @~english
 * @brief Type definitions related to core
 */

#ifndef __GF_TYPE_CORE_H__
#define __GF_TYPE_CORE_H__

#include <gf_pre.h>
#include <gf_macro.h>

#ifdef GF_EXPOSE_CORE
/* External library */

/* Engine */
#include <gf_type/physics.h>
#include <gf_type/draw.h>

/* Standard */
#include <stdio.h>

/**
 * @struct gf_engine_t
 * @~english
 * @brief Engine instance
 *
 * @var gf_engine_t::physics
 * @brief Physics interface
 * @todo Create gf_server_t and move physics there
 *
 * @var gf_engine_t::draw
 * @brief Drawing interface
 * @todo Create gf_client_t and move draw there
 *
 * @var gf_engine_t::log
 * @brief Log output
 * @note Default is `stderr`
 * @warning This is `NULL` when logger is using graphical console
 * @warning Destroying engien instance **does not** `fclose` this
 */
GF_DECLARE_TYPE(engine, {
	gf_physics_t* physics;
	gf_draw_t*    draw;
	FILE*	      log;
});
#else
typedef void gf_engine_t;
#endif

#endif
