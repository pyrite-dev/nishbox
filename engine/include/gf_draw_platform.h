/**
 * @file gf_draw_platform.h
 * @~english
 * @brief Platform-dependent part of drawing driver
 * @warning You should not use functions written here, since engine does it for you
 */

#ifndef __GF_DRAW_PLATFORM_H__
#define __GF_DRAW_PLATFORM_H__

#include <gf_pre.h>
#include <gf_macro.h>

/* Type */
#include <gf_type/draw_platform.h>

/* Engine */
#include <gf_type/draw.h>

/* Standard */

/**
 * @~english
 * @brief Create platform-dependent part of drawing driver
 * @param draw Drawing interface
 */
GF_EXPORT void gf_draw_platform_create(gf_draw_t* draw);

/**
 * @~english
 * @brief Destroy platform-dependent part of drawing driver
 * @param draw Drawing interface
 */
GF_EXPORT void gf_draw_platform_destroy(gf_draw_t* draw);

/**
 * @~english
 * @brief Do platform-dependent step
 * @param draw Drawing interface
 * @return `0` if successful, otherwise if failed
 */
GF_EXPORT int gf_draw_platform_step(gf_draw_t* draw);

/**
 * @~english
 * @brief Check if renderer has extension
 * @param draw Drawing interface
 * @param query Extension to be checked
 * @return `1` if extension is present, otherwise if it isn't
 */
GF_EXPORT int gf_draw_platform_has_extension(gf_draw_t* draw, const char* query);

/**
 * @~english
 * @brief Initialize platform-dependent part of drawing driver
 */
GF_EXPORT void gf_draw_platform_begin(void);

/**
 * @~english
 * @brief Cleanup platform-dependent part of drawing driver
 */
GF_EXPORT void gf_draw_platform_end(void);

#endif
