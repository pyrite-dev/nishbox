#ifndef __NB_LOG_H__
#define __NB_LOG_H__

#include <nb_pre.h>
#include <nb_macro.h>

/* Type */

/* NishBox */

/* Standard */

#define nb_function_log(fmt, arg, ...) nb_log("%6d %24s: " fmt "\n", __LINE__, __FUNCTION_NAME__, arg)

void nb_log(const char* fmt, ...);

#endif
