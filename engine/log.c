#define NB_LOG_EXPOSE

/* External library */

/* Interface */
#include "nb_log.h"

/* NishBox */

/* Standard */
#include <stdio.h>
#include <stdarg.h>

void nb_log(const char* fmt, ...) {
	va_list va;
	va_start(va, fmt);
	vfprintf(stderr, fmt, va);
	va_end(va);
}
