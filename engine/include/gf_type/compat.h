/**
 * @file gf_type/compat.h
 * @~english
 * @brief Type definitions for C99 types in C89
 */

#ifndef __GF_TYPE_COMPAT_H__
#define __GF_TYPE_COMPAT_H__

#ifdef __STDC_VERSION__
#if __STDC_VERSION__ >= 199901L
#define GF_IS_C99
#endif
#endif

#ifdef GF_IS_C99
#include <stdbool.h>
#include <stdint.h>

#define gf_true true
#define gf_false false
typedef bool	 gf_bool_t;
typedef uint8_t	 gf_uint8_t;
typedef uint16_t gf_uint16_t;
typedef uint32_t gf_uint32_t;
typedef uint64_t gf_uint64_t;
typedef int8_t	 gf_int8_t;
typedef int16_t	 gf_int16_t;
typedef int32_t	 gf_int32_t;
typedef int64_t	 gf_int64_t;
#else
#endif

#endif
