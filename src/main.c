/* NishBox */
#include <ne_core.h>
#include <ne_graphic.h>

/* External library */

/* Standard */
#include <stdio.h>

ne_engine_t* engine;

void draw_frame(ne_draw_t* draw) {
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
