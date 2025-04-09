#define NE_EXPOSE_THREAD

#include <ne_pre.h>

/* External library */
#include <pthread.h>

/* Interface */
#include <ne_thread.h>

/* NishBox */

/* Standard */
#include <stdlib.h>

void* ne_wrap_thread(void* arg) {
	ne_thread_context_t* ctx = (ne_thread_context_t*)arg;
	ctx->func(ctx->data);
	return NULL;
}

ne_thread_t* ne_create_thread(void (*func)(void*), void* userdata) {
	ne_thread_t* thread  = malloc(sizeof(*thread));
	thread->context.func = func;
	thread->context.data = userdata;
	if(pthread_create(&thread->thread, NULL, ne_wrap_thread, &thread->context) == 0) return thread;
	free(thread);
	return NULL;
}

void ne_join_thread(ne_thread_t* thread) {
	void* value;
	pthread_join(thread->thread, &value);
}

void ne_destroy_thread(ne_thread_t* thread) { free(thread); }
