#ifndef __NB_THREAD_H__
#define __NB_THREAD_H__

#include <nb_pre.h>
#include <nb_macro.h>

/* Type */
#include <nb_type/thread.h>

/* NishBox */

/* Standard */

nb_thread_t* nb_create_thread(void (*func)(void*), void* userdata);
void	     nb_join_thread(nb_thread_t* thread);
void	     nb_destroy_thread(nb_thread_t* thread);

#endif
