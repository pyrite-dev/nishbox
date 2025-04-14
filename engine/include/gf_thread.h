/**
 * Thread
 *
 * Wrapper for platform-dependent thread.
 */

#ifndef __GF_THREAD_H__
#define __GF_THREAD_H__

#include <gf_pre.h>
#include <gf_macro.h>

/* Type */
#include <gf_type/thread.h>

/* Engine */

/* Standard */

GF_EXPORT gf_thread_t* gf_thread_create(void (*func)(void*), void* userdata);
GF_EXPORT void	       gf_thread_join(gf_thread_t* thread);
GF_EXPORT void	       gf_thread_destroy(gf_thread_t* thread);

#endif
