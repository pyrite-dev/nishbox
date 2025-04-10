#define GF_EXPOSE_THREAD

#include <gf_pre.h>

/* External library */
#include <pthread.h>

/* Interface */
#include <gf_thread.h>

/* Engine */

/* Standard */
#include <stdlib.h>

GF_EXPORT void* gf_wrap_thread(void* arg) {
	gf_thread_context_t* ctx = (gf_thread_context_t*)arg;
	ctx->func(ctx->data);
	return NULL;
}

GF_EXPORT gf_thread_t* gf_create_thread(void (*func)(void*), void* userdata) {
	gf_thread_t* thread  = malloc(sizeof(*thread));
	thread->context.func = func;
	thread->context.data = userdata;
	if(pthread_create(&thread->thread, NULL, gf_wrap_thread, &thread->context) == 0) return thread;
	free(thread);
	return NULL;
}

GF_EXPORT void gf_join_thread(gf_thread_t* thread) {
	void* value;
	pthread_join(thread->thread, &value);
}

GF_EXPORT void gf_destroy_thread(gf_thread_t* thread) { free(thread); }
