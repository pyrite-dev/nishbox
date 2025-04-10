#include <gf_pre.h>

/* External library */

/* Interface */
#include <gf_log.h>

/* Engine */

/* Standard */
#include <stdio.h>
#include <stdarg.h>

void gf_log(const char* fmt, ...) {
	va_list va;
	va_start(va, fmt);
	vfprintf(stderr, fmt, va);
	va_end(va);
}
