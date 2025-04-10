#ifndef __GF_LOG_H__
#define __GF_LOG_H__

#include <gf_pre.h>
#include <gf_macro.h>

/* Type */

/* Engine */

/* Standard */

#define gf_function_log(fmt, arg, ...) gf_log("%6d %24s: " fmt "\n", __LINE__, __FUNCTION_NAME__, arg)

void gf_log(const char* fmt, ...);

#endif
