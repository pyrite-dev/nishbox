#define GF_EXPOSE_GUI

#include <gf_pre.h>

/* External library */
#include <stb_ds.h>

/* Interface */
#include <gf_gui.h>

/* Engine */

/* Standard */

gf_gui_id_t gf_gui_create_frame(gf_gui_t* gui, double x, double y, double w, double h) {
	gf_gui_component_t c;

	gf_gui_create_component(gui, &c, x, y, w, h);

	c.type = GF_GUI_FRAME;

	hmputs(gui->area, c);

	return c.key;
}

void gf_gui_frame_render(gf_gui_t* gui, gf_gui_component_t* c) {
	if(c->type != GF_GUI_FRAME) return;
}

void gf_gui_frame_drag(gf_gui_t* gui, gf_gui_component_t* c) {
	if(c->type != GF_GUI_FRAME) return;
}

void gf_gui_frame_click(gf_gui_t* gui, gf_gui_component_t* c) {
	if(c->type != GF_GUI_FRAME) return;
}
