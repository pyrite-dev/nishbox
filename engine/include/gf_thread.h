#ifndef __GF_THREAD_H__
#define __GF_THREAD_H__

#include <gf_pre.h>
#include <gf_macro.h>

/* Type */
#include <gf_type/thread.h>

/* Engine */

/* Standard */

gf_thread_t* gf_create_thread(void (*func)(void*), void* userdata);
void	     gf_join_thread(gf_thread_t* thread);
void	     gf_destroy_thread(gf_thread_t* thread);

#endif
