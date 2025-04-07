#define NB_EXPOSE_THREAD

#include <nb_pre.h>

/* External library */
#include <pthread.h>

/* Interface */
#include <nb_thread.h>

/* NishBox */

/* Standard */
#include <stdlib.h>

void* nb_wrap_thread(void* arg) {
	nb_thread_context_t* ctx = (nb_thread_context_t*)arg;
	ctx->func(ctx->data);
	return NULL;
}

nb_thread_t* nb_create_thread(void (*func)(void*), void* userdata) {
	nb_thread_t* thread  = malloc(sizeof(*thread));
	thread->context.func = func;
	thread->context.data = userdata;
	if(pthread_create(&thread->thread, NULL, nb_wrap_thread, &thread->context) == 0) return thread;
	free(thread);
	return NULL;
}
