#ifndef __NE_LOG_H__
#define __NE_LOG_H__

#include <ne_pre.h>
#include <ne_macro.h>

/* Type */

/* NishBox */

/* Standard */

#define ne_function_log(fmt, arg, ...) ne_log("%6d %24s: " fmt "\n", __LINE__, __FUNCTION_NAME__, arg)

void ne_log(const char* fmt, ...);

#endif
