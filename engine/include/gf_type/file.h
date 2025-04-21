/**
 * @file gf_type/file.h
 * @~english
 * @brief Type definitions related to file I/O
 */

#ifndef __GF_TYPE_FILE_H__
#define __GF_TYPE_FILE_H__

#include <gf_pre.h>
#include <gf_macro.h>

#ifdef GF_EXPOSE_FILE
typedef struct gf_file_t gf_file_t;

/* External library */

/* Engine */

/* Standard */

/**
 * @struct gf_file_t
 * @~english
 * @brief File
 */
GF_DECLARE_TYPE(file, {});
#else
typedef void gf_file_t;
#endif

#endif
