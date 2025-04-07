#ifndef __NE_MACRO_H__
#define __NE_MACRO_H__

#ifdef NE_EXPOSE_ALL

#ifndef NE_EXPOSE_CORE
#define NE_EXPOSE_CORE
#endif

#ifndef NE_EXPOSE_DRAW
#define NE_EXPOSE_DRAW
#endif

#ifndef NE_EXPOSE_DRAW_PLATFORM
#define NE_EXPOSE_DRAW_PLATFORM
#endif

#ifndef NE_EXPOSE_MESH
#define NE_EXPOSE_MESH
#endif

#ifndef NE_EXPOSE_MODEL
#define NE_EXPOSE_MODEL
#endif

#ifndef NE_EXPOSE_TEXTURE
#define NE_EXPOSE_TEXTURE
#endif

#ifndef NE_EXPOSE_PHYSICS
#define NE_EXPOSE_PHYSICS
#endif

#ifndef NE_EXPOSE_MATH
#define NE_EXPOSE_MATH
#endif

#ifndef NE_EXPOSE_VERSION
#define NE_EXPOSE_VERSION
#endif

#ifndef NE_EXPOSE_DRAW_DRIVER
#define NE_EXPOSE_DRAW_DRIVER
#endif

#endif

#ifndef __FUNCTION_NAME__
#ifdef _MSC_VER
#define __FUNCTION_NAME__ __FUNCTION__
#else
#define __FUNCTION_NAME__ __func__
#endif
#endif

#define NE_DECLARE_TYPE(n, b) typedef struct _ne_##n b ne_##n##_t;

/* Expose them by default */
#ifndef NE_EXPOSE_MATH
#define NE_EXPOSE_MATH
#endif

#ifndef NE_EXPOSE_VERSION
#define NE_EXPOSE_VERSION
#endif

#endif
