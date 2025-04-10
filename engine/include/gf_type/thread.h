#ifndef __GF_TYPE_THREAD_H__
#define __GF_TYPE_THREAD_H__

#include <gf_pre.h>
#include <gf_macro.h>

#ifdef GF_EXPOSE_THREAD
/* External library */
#if defined(THREAD_POSIX)
#include <pthread.h>
#elif defined(THREAD_WIN32)
#include <windows.h>
#endif

/* Engine */

/* Standard */

GF_DECLARE_TYPE(thread_context, {
	void (*func)(void*);
	void* data;
});

#if defined(THREAD_POSIX)
GF_DECLARE_TYPE(thread, {
	gf_thread_context_t context;
	pthread_t	    thread;
});
#elif defined(THREAD_WIN32)
GF_DECLARE_TYPE(thread, {
	gf_thread_context_t context;
	HANDLE		    thread;
});
#endif
#else
typedef void gf_thread_t;
typedef void gf_thread_context_t;
#endif

#endif
