#define NE_EXPOSE_DRAW

/* NishBox */
#include <ne_core.h>
#include <ne_graphic.h>

/* External library */

/* Standard */
#include <stdio.h>
#include <string.h>

ne_engine_t* engine;

void draw_frame(ne_draw_t* draw) {
	char d[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char str[2];
	str[1] = 0;
	int y, x;
	int i = 0;
	int s = 8;

	int r = 0, g = 0, b = 0;
	int max = 5;

	for(y = 0; y < draw->height; y += s) {
		for(x = 0; x < draw->width; x += s / 2) {
			str[0] = d[(i++) % strlen(d)];
			ne_graphic_text(draw, x, y, s, str, 255 / max * r, 255 / max * g, 255 / max * b, 255);

			b++;
			if(b == max + 1){
				b = 0;
				g++;
			}
			if(g == max + 1){
				g = 0;
				r++;
			}
			if(r == max + 1){
				r = 0;
			}
		}
	}
}

int main(int argc, char** argv) {
	ne_engine_begin();
	engine = ne_engine_create(0);
	if(engine == NULL) {
		fprintf(stderr, "Engine creation failure\n");
		ne_engine_end();
		return 1;
	}
	ne_engine_set_draw(engine, draw_frame);
	ne_engine_loop(engine);
	ne_engine_destroy(engine);
	ne_engine_end();

	return 0;
}
