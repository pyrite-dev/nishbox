/**
 * @file gf_type/resource.h
 * @~english
 * @brief Type definitions related to resource
 */

#ifndef __GF_TYPE_RESOURCE_H__
#define __GF_TYPE_RESOURCE_H__

#include <gf_pre.h>
#include <gf_macro.h>

#ifdef GF_EXPOSE_RESOURCE
typedef struct gf_resource_t gf_resource_t;

/* External library */

/* Engine */
#include <gf_type/core.h>

/* Standard */
#include <stdio.h>

/**
 * @struct gf_resource_entry_t
 * @~english
 * @brief Resource entry
 *
 * @var gf_resource_entry_t::key
 * @brief Entry name
 *
 * @var gf_resource_entry_t::address
 * @brief Location in file
 *
 * @var gf_resource_entry_t::address
 * @brief Location in file
 *
 * @var gf_resource_entry_t::size
 * @brief Size
 */
GF_DECLARE_TYPE(resource_entry, {
	char*	     key;
	unsigned int address;
	unsigned int size;
});

/**
 * @struct gf_resource_t
 * @~english
 * @brief Resource
 *
 * @var gf_resource_t::engine
 * @brief Engine instance
 *
 * @var gf_resource_t::entries
 * @brief Resource entries
 *
 * @var gf_resource_t::data
 * @brief Data
 */
GF_DECLARE_TYPE(resource, {
	gf_engine_t*	     engine;
	gf_resource_entry_t* entries;
	unsigned char*	     data;
});
#else
typedef void gf_resource_entry_t;
typedef void gf_resource_t;
#endif

#endif
