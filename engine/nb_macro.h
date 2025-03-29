#ifndef __NB_MACRO_H__
#define __NB_MACRO_H__

#ifdef NB_EXPOSE_ALL

#ifndef NB_EXPOSE_CORE
#define NB_EXPOSE_CORE
#endif

#ifndef NB_EXPOSE_DRAW
#define NB_EXPOSE_DRAW
#endif

#endif

#ifndef __FUNCTION_NAME__
#ifdef _MSC_VER
#define __FUNCTION_NAME__ __FUNCTION__
#else
#define __FUNCTION_NAME__ __func__
#endif
#endif

#endif
