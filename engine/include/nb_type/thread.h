#ifndef __NB_TYPE_THREAD_H__
#define __NB_TYPE_THREAD_H__

#include <nb_pre.h>
#include <nb_macro.h>

#ifdef NB_EXPOSE_THREAD
/* External library */
#if defined(THREAD_POSIX)
#include <pthread.h>
#elif defined(THREAD_WIN32)
#include <windows.h>
#endif

/* NishBox */

/* Standard */

NB_DECLARE_TYPE(thread_context, {
	void (*func)(void*);
	void* data;
});

#if defined(THREAD_POSIX)
NB_DECLARE_TYPE(thread, {
	nb_thread_context_t context;
	pthread_t	    thread;
});
#elif defined(THREAD_WIN32)
NB_DECLARE_TYPE(thread, {
	nb_thread_context_t context;
	HANDLE		    thread;
});
#endif
#else
typedef void nb_thread_t;
typedef void nb_thread_context_t;
#endif

#endif
