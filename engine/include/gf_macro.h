/**
 * @file gf_macro.h
 * @~english
 * @brief Macro
 */

#ifndef __GF_MACRO_H__
#define __GF_MACRO_H__

#ifdef GF_EXPOSE_ALL

#ifndef GF_EXPOSE_CORE
/**
 * @~english
 * @brief Expose core properties
 */
#define GF_EXPOSE_CORE
#endif

#ifndef GF_EXPOSE_DRAW
/**
 * @~english
 * @brief Expose drawing interface properties
 */
#define GF_EXPOSE_DRAW
#endif

#ifndef GF_EXPOSE_DRAW_PLATFORM
/**
 * @~english
 * @brief Expose platform-dependent part of drawing driver properties
 */
#define GF_EXPOSE_DRAW_PLATFORM
#endif

#ifndef GF_EXPOSE_DRAW_DRIVER
/**
 * @~english
 * @brief Expose drawing driver properties
 */
#define GF_EXPOSE_DRAW_DRIVER
#endif

#ifndef GF_EXPOSE_MESH
/**
 * @~english
 * @brief Expose mesh properties
 */
#define GF_EXPOSE_MESH
#endif

#ifndef GF_EXPOSE_MODEL
/**
 * @~english
 * @brief Expose model properties
 */
#define GF_EXPOSE_MODEL
#endif

#ifndef GF_EXPOSE_TEXTURE
/**
 * @~english
 * @brief Expose texture properties
 */
#define GF_EXPOSE_TEXTURE
#endif

#ifndef GF_EXPOSE_PHYSICS
/**
 * @~english
 * @brief Expose physics interface properties
 */
#define GF_EXPOSE_PHYSICS
#endif

#ifndef GF_EXPOSE_GUI
/**
 * @~english
 * @brief Expose GUI properties
 */
#define GF_EXPOSE_GUI
#endif

#ifndef GF_EXPOSE_THREAD
/**
 * @~english
 * @brief Expose thread interface properties
 */
#define GF_EXPOSE_THREAD
#endif

#ifndef GF_EXPOSE_GRAPHIC
/**
 * @~english
 * @brief Expose graphic interface properties
 * @note Exposed by default
 */
#define GF_EXPOSE_GRAPHIC
#endif

#ifndef GF_EXPOSE_MATH
/**
 * @~english
 * @brief Expose math properties
 * @note Exposed by default
 */
#define GF_EXPOSE_MATH
#endif

#ifndef GF_EXPOSE_VERSION
/**
 * @~english
 * @brief Expose version properties
 * @note Exposed by default
 */
#define GF_EXPOSE_VERSION
#endif

#endif

/**
 * @def __FUNCTION_NAME__
 * @~english
 * @brief Defined as `__FUNCTION__` on MSVC, otherwise defined as `__func__`
 */
#ifndef __FUNCTION_NAME__
#ifdef _MSC_VER
#define __FUNCTION_NAME__ __FUNCTION__
#else
#define __FUNCTION_NAME__ __func__
#endif
#endif

/**
 * @~english
 * @brief Macro to define engine type shorter
 * @param n Name
 * @param b Body
 */
#define GF_DECLARE_TYPE(n, b) typedef struct gf_##n##_t b gf_##n##_t;

#if defined(_WIN32) && defined(GF_DLL)
#define GF_EXPORT __declspec(dllexport)
#else
#define GF_EXPORT extern
#endif

/* Expose them by default */
#ifndef GF_EXPOSE_GRAPHIC
#define GF_EXPOSE_GRAPHIC
#endif

#ifndef GF_EXPOSE_MATH
#define GF_EXPOSE_MATH
#endif

#ifndef GF_EXPOSE_VERSION
#define GF_EXPOSE_VERSION
#endif

#endif
