#ifndef __NB_MACRO_H__
#define __NB_MACRO_H__

#ifdef NB_EXPOSE_ALL

#ifndef NB_EXPOSE_CORE
#define NB_EXPOSE_CORE
#endif

#ifndef NB_EXPOSE_DRAW
#define NB_EXPOSE_DRAW
#endif

#ifndef NB_EXPOSE_DRAW_PLATFORM
#define NB_EXPOSE_DRAW_PLATFORM
#endif

#ifndef NB_EXPOSE_MESH
#define NB_EXPOSE_MESH
#endif

#ifndef NB_EXPOSE_MODEL
#define NB_EXPOSE_MODEL
#endif

#ifndef NB_EXPOSE_TEXTURE
#define NB_EXPOSE_TEXTURE
#endif

#ifndef NB_EXPOSE_PHYSICS
#define NB_EXPOSE_PHYSICS
#endif

#ifndef NB_EXPOSE_MATH
#define NB_EXPOSE_MATH
#endif

#ifndef NB_EXPOSE_VERSION
#define NB_EXPOSE_VERSION
#endif

#endif

#ifndef __FUNCTION_NAME__
#ifdef _MSC_VER
#define __FUNCTION_NAME__ __FUNCTION__
#else
#define __FUNCTION_NAME__ __func__
#endif
#endif

#define NB_DECLARE_TYPE(n, b) typedef struct _nb_##n b nb_##n##_t;

/* Expose them by default */
#ifndef NB_EXPOSE_MATH
#define NB_EXPOSE_MATH
#endif

#ifndef NB_EXPOSE_VERSION
#define NB_EXPOSE_VERSION
#endif

#endif
