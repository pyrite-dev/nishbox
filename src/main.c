/* NishBox */
#include <ne_core.h>
#include <ne_graphic.h>

/* External library */

/* Standard */
#include <stdio.h>

ne_engine_t* engine;

void draw_frame(ne_draw_t* draw) {
	ne_graphic_text(draw, 0, 0, 32, "test text", 255, 0, 0, 128);
	ne_graphic_text(draw, 8, 8, 32, "test text", 0, 255, 0, 128);
	ne_graphic_text(draw, 16, 16, 32, "test text", 0, 0, 255, 128);
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
