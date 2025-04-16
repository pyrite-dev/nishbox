#define GF_EXPOSE_FONT

#include <gf_pre.h>

/* External library */

/* Interface */
#include <gf_font.h>

/* Engine */
#include <gf_log.h>

/* Standard */
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

gf_font_glyph_t* gf_font_get(gf_font_t* font, int code) {
	int i;
	if(code < 0x20) return NULL;
	for(i = 0; i < font->count; i++) {
		if(font->glyph[i]->code == code) {
			return font->glyph[i];
		}
	}
	return NULL;
}

#ifdef _MSC_VER
#define gf_stat _stat
#else
#define gf_stat stat
#endif

gf_font_t* gf_font_create(const char* path) {
	gf_font_t*     font = malloc(sizeof(*font));
	struct gf_stat s;
	memset(font, 0, sizeof(*font));
	if(gf_stat(path, &s) != 0) {
		free(font);
		return NULL;
	}
	gf_log_function(NULL, "%s: %lu bytes", path, (unsigned long)s.st_size);
	return font;
}
