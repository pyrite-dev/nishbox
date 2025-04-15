/**
 * @file gf_physics.h
 * @~english
 * @brief Physics interface
 */

#ifndef __GF_PHYSICS_H__
#define __GF_PHYSICS_H__

#include <gf_pre.h>
#include <gf_macro.h>

/* Type */
#include <gf_type/physics.h>

/* Engine */

/* Standard */

/**
 * @~english
 * @brief Initialize physics interface
 */
GF_EXPORT void gf_physics_begin(void);

/**
 * @~english
 * @brief Cleanup physics interface
 */
GF_EXPORT void gf_physics_end(void);

/**
 * @~english
 * @brief Create physics interface
 * @return Physics interface
 */
GF_EXPORT gf_physics_t* gf_physics_create(void);

/**
 * @~english
 * @brief Destroy physics interface
 * @param physics Physics interface
 */
GF_EXPORT void gf_physics_destroy(gf_physics_t* physics);

#endif
