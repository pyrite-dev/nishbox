#define GF_EXPOSE_GUI

#include <gf_pre.h>

/* External library */

/* Interface */
#include <gf_gui.h>

/* Engine */
#include <gf_graphic.h>
#include <gf_draw.h>

/* Standard */
#include <stdlib.h>
#include <string.h>

gf_graphic_color_t gf_gui_base_color;
gf_graphic_color_t gf_gui_font_color;

gf_gui_t* gf_gui_create(gf_draw_t* draw) {
	gf_gui_t*   gui = malloc(sizeof(*gui));
	gf_gui_id_t i;
	gui->draw = draw;

	GF_SET_COLOR(gf_gui_base_color, 48, 96, 48, 255);
	GF_SET_COLOR(gf_gui_font_color, 256 - 32, 256 - 32, 256 - 32, 255);

	for(i = 0; i < GF_GUI_MAX_COMPONENTS; i++) gui->area[i].type = -1;

	return gui;
}

/* note... left top should be the lightest in the border */

void gf_gui_draw_box(gf_gui_t* gui, int mul, float x, float y, float w, float h) {
	const int	   color_diff = 32; /* color diff */
	const float	   bw	      = 2;  /* border width */
	gf_graphic_color_t col;

	int cd = mul * color_diff;

	col = gf_gui_base_color;
	col.r += cd;
	col.g += cd;
	col.b += cd;
	gf_graphic_fill_rect(gui->draw, x, y, w, h, col);

	col = gf_gui_base_color;
	col.r -= cd;
	col.g -= cd;
	col.b -= cd;
	gf_graphic_fill_polygon(gui->draw, col, GF_GRAPHIC_2D, 5, x + w, y + h, x + w, y, x + w - bw, y + bw, x + bw, y + h - bw, x, y + h);

	col = gf_gui_base_color;
	gf_graphic_fill_rect(gui->draw, x + bw, y + bw, w - bw * 2, h - bw * 2, col);
}

gf_gui_component_t* gf_gui_first_unused(gf_gui_t* gui, gf_gui_id_t* id) {
	gf_gui_id_t i;
	for(i = 0; i < GF_GUI_MAX_COMPONENTS; i++) {
		if(gui->area[i].type == GF_GUI_UNUSED) {
			*id = i;
			return &gui->area[i];
		}
	}
	return NULL;
}

gf_gui_id_t gf_gui_create_button(gf_gui_t* gui, float x, float y, float w, float h, const char* text) {
	gf_gui_id_t	    id;
	gf_gui_component_t* c = gf_gui_first_unused(gui, &id);

	c->type	  = GF_GUI_BUTTON;
	c->x	  = x;
	c->y	  = y;
	c->width  = w;
	c->height = h;

	c->u.button.pressed = 0;
	c->u.button.text    = malloc(strlen(text) + 1);
	strcpy(c->u.button.text, text);
	return id;
}

void gf_gui_render(gf_gui_t* gui) {
	gf_gui_id_t i;
	for(i = 0; i < GF_GUI_MAX_COMPONENTS; i++) {
		gf_gui_component_t* c  = &gui->area[i];
		float		    cx = c->x;
		float		    cy = c->y;
		float		    cw = c->width;
		float		    ch = c->height;
		switch(c->type) {
		case GF_GUI_BUTTON: {
			float x = cx + cw / 2 - gf_graphic_text_width(gui->draw, GF_GUI_FONT_SIZE, c->u.button.text) / 2;
			float y = cy + ch / 2 - GF_GUI_FONT_SIZE / 2;
			gf_gui_draw_box(gui, GF_GUI_NORMAL, cx, cy, cw, ch);
			gf_graphic_text(gui->draw, x, y, GF_GUI_FONT_SIZE, c->u.button.text, gf_gui_font_color);
			break;
		}
		}
	}
}
