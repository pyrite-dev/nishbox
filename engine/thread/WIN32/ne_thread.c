#define NE_EXPOSE_THREAD

#include <ne_pre.h>

/* External library */
#include <windows.h>

/* Interface */
#include <ne_thread.h>

/* NishBox */

/* Standard */
#include <stdlib.h>

DWORD WINAPI ne_wrap_thread(void* arg) {
	ne_thread_context_t* ctx = (ne_thread_context_t*)arg;
	ctx->func(ctx->data);
	return 0;
}

ne_thread_t* ne_create_thread(void (*func)(void*), void* userdata) {
	ne_thread_t* thread  = malloc(sizeof(*thread));
	thread->context.func = func;
	thread->context.data = userdata;
	if((thread->thread = CreateThread(NULL, 0, ne_wrap_thread, &thread->context, 0, NULL)) != NULL) return thread;
	free(thread);
	return NULL;
}

void ne_join_thread(ne_thread_t* thread) { WaitForSingleObject(thread->thread, INFINITE); }

void ne_destroy_thread(ne_thread_t* thread) {
	CloseHandle(thread->thread);
	free(thread);
}
