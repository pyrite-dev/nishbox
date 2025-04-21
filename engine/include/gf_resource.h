/**
 * @file gf_resource.h
 * @~english
 * @brief Resource
 */

#ifndef __GF_RESOURCE_H__
#define __GF_RESOURCE_H__

#include <gf_pre.h>
#include <gf_macro.h>

/* Type */
#include <gf_type/resource.h>

/* Engine */
#include <gf_type/core.h>

/* Standard */
#include <stddef.h>

/**
 * @~english
 * @brief Create resource
 * @param engine Engine instance
 * @param path Path
 * @return Resource
 */
GF_EXPORT gf_resource_t* gf_resource_create(gf_engine_t* engine, const char* path);

/**
 * @~english
 * @brief Destroy resource
 * @param resource Resource
 */
GF_EXPORT void gf_resource_destroy(gf_resource_t* resource);

/**
 * @~english
 * @brief Get data from resource
 * @param resource Resource
 * @param name Entry name
 * @param data Pointer to data result
 * @param size Pointer to size result
 * @return `0` if successful, otherwise `-1`
 */
GF_EXPORT int gf_resource_get(gf_resource_t* resource, const char* name, void** data, size_t* size);

#endif
