#ifndef __NB_TYPE_THREAD_H__
#define __NB_TYPE_THREAD_H__

#include <nb_pre.h>
#include <nb_macro.h>

#ifdef NB_EXPOSE_THREAD
/* External library */

/* NishBox */

/* Standard */

NB_DECLARE_TYPE(thread, {
});
#else
typedef void nb_thread_t;
#endif

#endif
