#ifndef __NE_THREAD_H__
#define __NE_THREAD_H__

#include <ne_pre.h>
#include <ne_macro.h>

/* Type */
#include <ne_type/thread.h>

/* NishBox */

/* Standard */

ne_thread_t* ne_create_thread(void (*func)(void*), void* userdata);
void	     ne_join_thread(ne_thread_t* thread);
void	     ne_destroy_thread(ne_thread_t* thread);

#endif
