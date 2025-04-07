#define NB_EXPOSE_THREAD

#include <nb_pre.h>

/* External library */
#include <windows.h>

/* Interface */
#include <nb_thread.h>

/* NishBox */

/* Standard */
#include <stdlib.h>

DWORD WINAPI nb_wrap_thread(void* arg) {
	nb_thread_context_t* ctx = (nb_thread_context_t*)arg;
	ctx->func(ctx->data);
	return 0;
}

nb_thread_t* nb_create_thread(void (*func)(void*), void* userdata) {
	nb_thread_t* thread  = malloc(sizeof(*thread));
	thread->context.func = func;
	thread->context.data = userdata;
	if((thread->thread = CreateThread(NULL, 0, nb_wrap_thread, &thread->context, 0, NULL)) != NULL) return thread;
	free(thread);
	return NULL;
}

void nb_join_thread(nb_thread_t* thread) { WaitForSingleObject(thread->thread, INFINITE); }

void nb_destroy_thread(nb_thread_t* thread) {
	CloseHandle(thread->thread);
	free(thread);
}
