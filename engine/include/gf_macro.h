/**
 * Macro
 */

#ifndef __GF_MACRO_H__
#define __GF_MACRO_H__

#ifdef GF_EXPOSE_ALL

#ifndef GF_EXPOSE_CORE
#define GF_EXPOSE_CORE
#endif

#ifndef GF_EXPOSE_DRAW
#define GF_EXPOSE_DRAW
#endif

#ifndef GF_EXPOSE_DRAW_PLATFORM
#define GF_EXPOSE_DRAW_PLATFORM
#endif

#ifndef GF_EXPOSE_MESH
#define GF_EXPOSE_MESH
#endif

#ifndef GF_EXPOSE_MODEL
#define GF_EXPOSE_MODEL
#endif

#ifndef GF_EXPOSE_TEXTURE
#define GF_EXPOSE_TEXTURE
#endif

#ifndef GF_EXPOSE_PHYSICS
#define GF_EXPOSE_PHYSICS
#endif

#ifndef GF_EXPOSE_MATH
#define GF_EXPOSE_MATH
#endif

#ifndef GF_EXPOSE_VERSION
#define GF_EXPOSE_VERSION
#endif

#ifndef GF_EXPOSE_DRAW_DRIVER
#define GF_EXPOSE_DRAW_DRIVER
#endif

#endif

#ifndef __FUNCTION_NAME__
#ifdef _MSC_VER
#define __FUNCTION_NAME__ __FUNCTION__
#else
#define __FUNCTION_NAME__ __func__
#endif
#endif

#define GF_DECLARE_TYPE(n, b) typedef struct _gf_##n b gf_##n##_t;

#if defined(_WIN32) && defined(GF_DLL)
#define GF_EXPORT __declspec(dllexport)
#else
#define GF_EXPORT extern
#endif

/* Expose them by default */
#ifndef GF_EXPOSE_MATH
#define GF_EXPOSE_MATH
#endif

#ifndef GF_EXPOSE_VERSION
#define GF_EXPOSE_VERSION
#endif

#endif
