#ifndef __NB_LOG_H__
#define __NB_LOG_H__

#include <nb_macro.h>

/* External library */

/* NishBox */

/* Standard */

void nb_log(const char* fmt, ...);

#define NB_FORMAT_LOG(fmt, arg...) nb_log("%s: " fmt "\n", __FUNCTION_NAME__, arg)
#define NB_LOG(fmt) nb_log("%s: " fmt "\n", __FUNCTION_NAME__)

#endif
