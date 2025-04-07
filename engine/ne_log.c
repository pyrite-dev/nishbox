#include <ne_pre.h>

/* External library */

/* Interface */
#include <ne_log.h>

/* NishBox */

/* Standard */
#include <stdio.h>
#include <stdarg.h>

void ne_log(const char* fmt, ...) {
	va_list va;
	va_start(va, fmt);
	vfprintf(stderr, fmt, va);
	va_end(va);
}
