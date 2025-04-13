#define GF_EXPOSE_DRAW

/* Engine */
#include <gf_core.h>
#include <gf_draw.h>
#include <gf_graphic.h>
#include <gf_version.h>

/* External library */

/* Standard */
#include <stdio.h>
#include <string.h>

gf_engine_t* engine;

void draw_frame(gf_draw_t* draw) {
	char d[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char str[2];
	int  y, x;
	int  i = 0;
	int  s = 8;

	int r = 0, g = 0, b = 0;
	int max = 5;

	gf_color_t col;

	str[1] = 0;

	for(y = 0; y < draw->height; y += s) {
		for(x = 0; x < draw->width; x += s / 2) {
			str[0] = d[(i++) % strlen(d)];
			col.r  = 255.0f / max * r;
			col.g  = 255.0f / max * g;
			col.b  = 255.0f / max * b;
			col.a  = 255;
			gf_graphic_text(draw, x, y, s, str, col);

			b++;
			if(b == max + 1) {
				b = 0;
				g++;
			}
			if(g == max + 1) {
				g = 0;
				r++;
			}
			if(r == max + 1) {
				r = 0;
			}
		}
	}
}

int main(int argc, char** argv) {
	char	     title[64];
	gf_version_t ver;
	gf_get_version(&ver);
	sprintf(title, "NishBox %s (%s on %s)", ver.full, ver.driver, ver.backend);
	gf_engine_begin();
	engine = gf_engine_create(title, 0);
	if(engine == NULL) {
		fprintf(stderr, "Engine creation failure\n");
		gf_engine_end();
		return 1;
	}
	gf_engine_set_draw(engine, draw_frame);
	gf_engine_loop(engine);
	gf_engine_destroy(engine);
	gf_engine_end();

	return 0;
}
