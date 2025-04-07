#ifndef __NE_TYPE_THREAD_H__
#define __NE_TYPE_THREAD_H__

#include <ne_pre.h>
#include <ne_macro.h>

#ifdef NE_EXPOSE_THREAD
/* External library */
#if defined(THREAD_POSIX)
#include <pthread.h>
#elif defined(THREAD_WIN32)
#include <windows.h>
#endif

/* NishBox */

/* Standard */

NE_DECLARE_TYPE(thread_context, {
	void (*func)(void*);
	void* data;
});

#if defined(THREAD_POSIX)
NE_DECLARE_TYPE(thread, {
	ne_thread_context_t context;
	pthread_t	    thread;
});
#elif defined(THREAD_WIN32)
NE_DECLARE_TYPE(thread, {
	ne_thread_context_t context;
	HANDLE		    thread;
});
#endif
#else
typedef void ne_thread_t;
typedef void ne_thread_context_t;
#endif

#endif
