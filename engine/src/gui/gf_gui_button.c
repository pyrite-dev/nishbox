#define GF_EXPOSE_GUI
#define GF_EXPOSE_DRAW
#define GF_EXPOSE_INPUT

#include <gf_pre.h>

/* External library */
#include <stb_ds.h>

/* Interface */
#include <gf_gui.h>

/* Engine */
#include <gf_graphic.h>
#include <gf_draw.h>
#include <gf_log.h>

/* Standard */
#include <stdlib.h>
#include <string.h>

extern const double gf_gui_border_width;
extern const int    gf_gui_border_color_diff;

extern gf_graphic_color_t gf_gui_base_color;
extern gf_graphic_color_t gf_gui_font_color;

gf_gui_id_t gf_gui_create_button(gf_gui_t* gui, double x, double y, double w, double h) {
	gf_gui_component_t c;

	gf_gui_create_component(gui, &c, x, y, w, h);

	c.type = GF_GUI_BUTTON;

	hmputs(gui->area, c);

	return c.key;
}

void gf_gui_button_render(gf_gui_t* gui, gf_gui_component_t* c) {
	gf_input_t* input = gui->draw->input;
	double	    cx;
	double	    cy;
	double	    cw;
	double	    ch;
	double	    x;
	double	    y;
	int	    prop;
	if(c->type != GF_GUI_BUTTON) return;

	gf_gui_calc_xywh(gui, c, &cx, &cy, &cw, &ch);

	gf_gui_draw_box(gui, (gui->pressed == c->key) ? GF_GUI_INVERT : GF_GUI_NORMAL, cx, cy, cw, ch);

	if(c->text != NULL) {
		x = cx + cw / 2 - gf_graphic_text_width(gui->draw, GF_GUI_SMALL_FONT_SIZE, c->text) / 2;
		y = cy + ch / 2 - GF_GUI_SMALL_FONT_SIZE / 2;
		if(gui->pressed == c->key) {
			x += gf_gui_border_width / 2;
			y += gf_gui_border_width / 2;
		}
		gf_graphic_clip_push(gui->draw, cx, cy, cw, ch);
		gf_graphic_text(gui->draw, x, y, GF_GUI_SMALL_FONT_SIZE, c->text, gf_gui_font_color);
		gf_graphic_clip_pop(gui->draw);
	}
}

void gf_gui_button_drag(gf_gui_t* gui, gf_gui_component_t* c) {
	gf_input_t* input = gui->draw->input;
	int	    prop;
	if(c->type != GF_GUI_BUTTON) return;
}

void gf_gui_button_click(gf_gui_t* gui, gf_gui_component_t* c) {
	gf_input_t* input = gui->draw->input;
	int	    prop;
	if(c->type != GF_GUI_BUTTON) return;
	if(c->callback != NULL) {
		c->callback(gui->engine, gui->draw, gui->pressed, GF_GUI_PRESS_EVENT);
	}
	c->pressed = 1;
	if((prop = gf_gui_get_prop(gui, c->key, "close-parent")) != GF_GUI_NO_SUCH_PROP && prop) {
		gf_gui_destroy_id(gui, c->parent);
	}
}
