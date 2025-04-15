/**
 * @file gf_type/graphic.h
 * @~english
 * @brief Type definitions related to graphic interface
 */

#ifndef __GF_TYPE_GRAPHIC_H__
#define __GF_TYPE_GRAPHIC_H__

#include <gf_pre.h>
#include <gf_macro.h>

#ifdef GF_EXPOSE_GRAPHIC
/* External library */

/* Engine */

/* Standard */

/**
 * @struct gf_color_t
 * @~english
 * @brief Color
 *
 * @var gf_color_t::r
 * @brief Red
 *
 * @var gf_color_t::g
 * @brief Green
 *
 * @var gf_color_t::b
 * @brief Blue
 *
 * @var gf_color_t::a
 * @brief Alpha
 */
GF_DECLARE_TYPE(color, {
	double r;
	double g;
	double b;
	double a;
});
#else
#error "should not happen!"
#endif

#endif
