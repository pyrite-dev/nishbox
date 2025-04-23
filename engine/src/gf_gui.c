#define GF_EXPOSE_GUI
#define GF_EXPOSE_DRAW
#define GF_EXPOSE_INPUT

#include <gf_pre.h>

/* External library */
#include <stb_ds.h>

/* Interface */
#include <gf_gui.h>

/* Engine */
#include <gf_gui_static.h>
#include <gf_graphic.h>
#include <gf_draw.h>
#include <gf_log.h>

/* Standard */
#include <stdlib.h>
#include <string.h>

const double gf_gui_border_width      = 2;
const int    gf_gui_border_color_diff = 48;

gf_graphic_color_t gf_gui_base_color;
gf_graphic_color_t gf_gui_font_color;

gf_gui_t* gf_gui_create(gf_engine_t* engine, gf_draw_t* draw) {
	gf_gui_t* gui = malloc(sizeof(*gui));
	memset(gui, 0, sizeof(*gui));
	gui->engine = engine;
	gui->draw   = draw;
	gui->area   = NULL;

	gui->pressed = -1;

	GF_SET_COLOR(gf_gui_base_color, 80, 88, 64, 255);
	GF_SET_COLOR(gf_gui_font_color, 256 - 32, 256 - 32, 256 - 32, 255);

	return gui;
}

void gf_gui_destroy(gf_gui_t* gui) {
	if(gui->area != NULL) {
		while(hmlen(gui->area) > 0) {
			gf_gui_destroy_id(gui, gui->area[0].key);
		}
		hmfree(gui->area);
	}
	gf_log_function(gui->engine, "Destroyed GUI", "");
	free(gui);
}

void gf_gui_destroy_id(gf_gui_t* gui, gf_gui_id_t id) {
	int		    i;
	int		    prop;
	int		    ind = hmgeti(gui->area, id);
	gf_gui_component_t* c;
	if(ind == -1) return;

	c = &gui->area[ind];
	for(i = 0; i < hmlen(gui->area); i++) {
		if(gui->area[i].parent == id) {
			gf_gui_destroy_id(gui, gui->area[i].key);
			i = -1;
		}
	}

	if((prop = gf_gui_get_prop(gui, c->key, "active")) != GF_GUI_NO_SUCH_PROP && prop) {
		for(i = hmlen(gui->area) - 1; i >= 0; i--) {
			gf_gui_component_t* c = &gui->area[i];
			if(c->parent == -1 && c->key != id) {
				gf_gui_set_prop(gui, c->key, "active", 1);
				break;
			}
		}
	}

	if(c->text != NULL) {
		free(c->text);
	}

	if(c->prop != NULL) {
		shfree(c->prop);
	}

	hmdel(gui->area, id);
}

/* note... left top should be the lightest in the border */

void gf_gui_draw_box(gf_gui_t* gui, int mul, double x, double y, double w, double h) {
	gf_graphic_color_t col;

	int cd = mul * gf_gui_border_color_diff;

	col = gf_gui_base_color;
	col.r += cd;
	col.g += cd;
	col.b += cd;
	gf_graphic_fill_rect(gui->draw, x, y, w, h, col);

	col = gf_gui_base_color;
	col.r -= cd;
	col.g -= cd;
	col.b -= cd;
	gf_graphic_fill_polygon(gui->draw, col, GF_GRAPHIC_2D, 5, x + w, y + h, x + w, y, x + w - gf_gui_border_width, y + gf_gui_border_width, x + gf_gui_border_width, y + h - gf_gui_border_width, x, y + h);

	col = gf_gui_base_color;
	gf_graphic_fill_rect(gui->draw, x + gf_gui_border_width, y + gf_gui_border_width, w - gf_gui_border_width * 2, h - gf_gui_border_width * 2, col);
}

void gf_gui_create_component(gf_gui_t* gui, gf_gui_component_t* c, double x, double y, double w, double h) {
	int ind;

	c->key = 0;
	do {
		ind = hmgeti(gui->area, c->key);
		if(ind != -1) {
			c->key++;
		}
	} while(ind != -1);
	c->x	    = x;
	c->y	    = y;
	c->width    = w;
	c->height   = h;
	c->parent   = -1;
	c->pressed  = 0;
	c->prop	    = NULL;
	c->callback = NULL;
	c->text	    = NULL;
	sh_new_strdup(c->prop);
	shdefault(c->prop, GF_GUI_NO_SUCH_PROP);

	shput(c->prop, "min-width", 0);
	shput(c->prop, "min-height", 0);
}

void gf_gui_calc_xywh_noset(gf_gui_t* gui, gf_gui_component_t* c, double* x, double* y, double* w, double* h) {
	double pw = 0;
	double ph = 0;
	double bx = 0;
	double by = 0;

	if(c->parent != -1) {
		double x2  = 0;
		double y2  = 0;
		double w2  = 0;
		double h2  = 0;
		int    ind = hmgeti(gui->area, c->parent);
		if(ind != -1) {
			gf_gui_calc_xywh_noset(gui, &gui->area[ind], &x2, &y2, &w2, &h2);
		}

		pw = w2;
		ph = h2;

		bx = x2;
		by = y2;
	}

	*x += bx;
	if(c->x < 0) {
		*x += pw;
	}
	*x += c->x;

	*y += by;
	if(c->y < 0) {
		*y += ph;
	}
	*y += c->y;

	if((*w) < c->width) {
		*w = c->width;
	}

	if((*h) < c->height) {
		*h = c->height;
	}
}

void gf_gui_calc_xywh(gf_gui_t* gui, gf_gui_component_t* c, double* x, double* y, double* w, double* h) {
	*x = 0;
	*y = 0;
	*w = 0;
	*h = 0;
	gf_gui_calc_xywh_noset(gui, c, x, y, w, h);
}

void gf_gui_render(gf_gui_t* gui) {
	int	    i;
	gf_input_t* input = gui->draw->input;
	double	    cx;
	double	    cy;
	double	    cw;
	double	    ch;
	int	    prop;
	for(i = hmlen(gui->area) - 1; i >= 0; i--) {
		gf_gui_component_t* c = &gui->area[i];
		gf_gui_calc_xywh(gui, c, &cx, &cy, &cw, &ch);
		if(input->mouse_x != -1 && input->mouse_y != -1 && gui->pressed == -1 && (input->mouse_flag & GF_INPUT_MOUSE_LEFT_MASK) && (cx <= input->mouse_x && input->mouse_x <= cx + cw) && (cy <= input->mouse_y && input->mouse_y <= cy + ch)) {
			gui->pressed = c->key;
			gf_gui_set_prop(gui, c->key, "clicked-x", input->mouse_x);
			gf_gui_set_prop(gui, c->key, "clicked-y", input->mouse_y);
			gf_gui_set_prop(gui, c->key, "diff-x", input->mouse_x - cx);
			gf_gui_set_prop(gui, c->key, "diff-y", input->mouse_y - cy);
			if((prop = gf_gui_get_prop(gui, c->key, "resizable")) != GF_GUI_NO_SUCH_PROP && prop) {
				gf_gui_set_prop(gui, c->key, "old-width", cw);
				gf_gui_set_prop(gui, c->key, "old-height", ch);
			}
		} else if(gui->pressed == -1) {
			c->pressed = 0;
		}
	}
	if(gui->pressed == -1 && (input->mouse_flag & GF_INPUT_MOUSE_LEFT_MASK)) {
		/* dummy value for "background" */
		gui->pressed = -2;
	}
	for(i = 0; i < hmlen(gui->area); i++) {
		gf_gui_component_t* c = &gui->area[i];
		gf_gui_calc_xywh(gui, c, &cx, &cy, &cw, &ch);

		gf_gui_all_render(gui, c);

		if((prop = gf_gui_get_prop(gui, c->key, "resizable")) != GF_GUI_NO_SUCH_PROP && prop) {
			int j;
			for(j = 0; j < 3; j++) {
				double		   sp  = gf_gui_border_width / 2 + 5;
				double		   bw  = gf_gui_border_width * 1.5;
				double		   rx  = cx + cw - sp - (j + 1) * (bw + 1);
				double		   ry  = cy + ch - sp - (j + 1) * (bw + 1);
				gf_graphic_color_t col = gf_gui_base_color;

				col.r -= gf_gui_border_color_diff;
				col.g -= gf_gui_border_color_diff;
				col.b -= gf_gui_border_color_diff;

				gf_graphic_fill_polygon(gui->draw, col, GF_GRAPHIC_2D, 4, cx + cw - sp, ry - bw, rx - bw, cy + ch - sp, rx - bw / 2.0, cy + ch - sp, cx + cw - sp, ry - bw / 2.0);

				col = gf_gui_base_color;
				col.r += gf_gui_border_color_diff;
				col.g += gf_gui_border_color_diff;
				col.b += gf_gui_border_color_diff;

				gf_graphic_fill_polygon(gui->draw, col, GF_GRAPHIC_2D, 4, cx + cw - sp, ry - bw / 2.0, rx - bw / 2.0, cy + ch - sp, rx, cy + ch - sp, cx + cw - sp, ry);
			}
		}
	}

	/* drag */
	if(gui->pressed != -1 && (input->mouse_flag & GF_INPUT_MOUSE_LEFT_MASK)) {
		int ind;
		ind = hmgeti(gui->area, gui->pressed);
		if(ind != -1) {
			gf_gui_component_t* c	   = &gui->area[ind];
			int		    cancel = 0;
			if((prop = gf_gui_get_prop(gui, c->key, "resizable")) != GF_GUI_NO_SUCH_PROP && prop) {
				double sp = gf_gui_border_width / 2 + 5;
				double sz = sp * 3;
				c->width  = gf_gui_get_prop(gui, c->key, "old-width");
				c->height = gf_gui_get_prop(gui, c->key, "old-height");
				gf_gui_calc_xywh(gui, c, &cx, &cy, &cw, &ch);
				cancel = 1;
				cancel = cancel && ((cx + cw - sp - sz) <= gf_gui_get_prop(gui, c->key, "clicked-x"));
				cancel = cancel && ((cx + cw - sp) >= gf_gui_get_prop(gui, c->key, "clicked-x"));
				cancel = cancel && ((cy + ch - sp - sz) <= gf_gui_get_prop(gui, c->key, "clicked-y"));
				cancel = cancel && ((cy + ch - sp) >= gf_gui_get_prop(gui, c->key, "clicked-y"));
				if(cancel) {
					c->width  = input->mouse_x - gf_gui_get_prop(gui, c->key, "clicked-x") + gf_gui_get_prop(gui, c->key, "old-width");
					c->height = input->mouse_y - gf_gui_get_prop(gui, c->key, "clicked-y") + gf_gui_get_prop(gui, c->key, "old-height");
					if((prop = gf_gui_get_prop(gui, c->key, "min-width")) != GF_GUI_NO_SUCH_PROP && c->width < GF_GUI_SMALL_FONT_SIZE + 10 + sz + prop) {
						c->width = GF_GUI_SMALL_FONT_SIZE + 10 + sz + prop;
					}
					if((prop = gf_gui_get_prop(gui, c->key, "min-height")) != GF_GUI_NO_SUCH_PROP && c->height < GF_GUI_SMALL_FONT_SIZE + 10 + sz + prop) {
						c->height = GF_GUI_SMALL_FONT_SIZE + 10 + sz + prop;
					}
				}
			}
			if(!cancel) {
				gf_gui_all_drag(gui, c);
			}
			gf_gui_move_topmost(gui, c->key);
		}
	}

	/* click */
	if((gui->pressed != -1) && !(input->mouse_flag & GF_INPUT_MOUSE_LEFT_MASK)) {
		int ind;
		ind = hmgeti(gui->area, gui->pressed);
		if(ind != -1) {
			gf_gui_component_t* c = &gui->area[ind];

			gf_gui_all_click(gui, c);
		}
		gui->pressed = -1;
	}
}

void gf_gui_set_callback(gf_gui_t* gui, gf_gui_id_t id, gf_gui_callback_t callback) {
	int ind = hmgeti(gui->area, id);
	if(ind == -1) return;

	gui->area[ind].callback = callback;
}

void gf_gui_set_parent(gf_gui_t* gui, gf_gui_id_t id, gf_gui_id_t parent) {
	int ind = hmgeti(gui->area, id);
	if(ind == -1) return;

	gui->area[ind].parent = parent;
}

void gf_gui_set_text(gf_gui_t* gui, gf_gui_id_t id, const char* text) {
	int ind = hmgeti(gui->area, id);
	if(ind == -1) return;

	if(gui->area[ind].text != NULL) free(gui->area[ind].text);
	gui->area[ind].text = malloc(strlen(text) + 1);
	strcpy(gui->area[ind].text, text);
}

void gf_gui_set_prop(gf_gui_t* gui, gf_gui_id_t id, const char* key, int value) {
	int ind = hmgeti(gui->area, id);
	if(ind == -1) return;

	shput(gui->area[ind].prop, key, value);
}

void gf_gui_delete_prop(gf_gui_t* gui, gf_gui_id_t id, const char* key) {
	int ind = hmgeti(gui->area, id);
	if(ind == -1) return;

	shdel(gui->area[ind].prop, key);
}

int gf_gui_get_prop(gf_gui_t* gui, gf_gui_id_t id, const char* key) {
	int ind = hmgeti(gui->area, id);
	if(ind == -1) return GF_GUI_NO_SUCH_PROP;

	return shget(gui->area[ind].prop, key);
}

void gf_gui_add_recursive(gf_gui_t* gui, gf_gui_component_t** pnew, gf_gui_id_t parent) {
	int i;

	for(i = 0; i < hmlen(gui->area); i++) {
		gf_gui_component_t* c = &gui->area[i];
		if(c->parent == parent) {
			hmputs(*pnew, *c);
			gf_gui_add_recursive(gui, pnew, c->key);
		}
	}
}

void gf_gui_sort_component(gf_gui_t* gui) {
	int i;
	gf_gui_component_t* new = NULL;

	for(i = 0; i < hmlen(gui->area); i++) {
		gf_gui_component_t* c = &gui->area[i];
		if(c->parent == -1) {
			gf_gui_set_prop(gui, c->key, "active", 0);
			hmputs(new, *c);
			gf_gui_add_recursive(gui, &new, c->key);
		}
	}

	hmfree(gui->area);
	gui->area = new;

	for(i = hmlen(gui->area) - 1; i >= 0; i--) {
		gf_gui_component_t* c = &gui->area[i];
		if(c->parent == -1) {
			gf_gui_set_prop(gui, c->key, "active", 1);
			break;
		}
	}
}

void gf_gui_move_topmost(gf_gui_t* gui, gf_gui_id_t id) {
	int i;
	int ind;
	gf_gui_component_t* new = NULL;

	for(i = 0; i < hmlen(gui->area); i++) {
		gf_gui_component_t* c = &gui->area[i];
		if(c->parent == -1 && c->key != id) {
			gf_gui_set_prop(gui, c->key, "active", 0);
			hmputs(new, *c);
			gf_gui_add_recursive(gui, &new, c->key);
		}
	}

	ind = hmgeti(gui->area, id);
	if(ind != -1) {
		gf_gui_component_t* c = &gui->area[ind];
		if(c->parent == -1) {
			gf_gui_set_prop(gui, c->key, "active", 1);
			hmputs(new, *c);
			gf_gui_add_recursive(gui, &new, c->key);
		}
	}

	hmfree(gui->area);
	gui->area = new;

	ind = hmgeti(gui->area, id);
	if(ind != -1) {
		gf_gui_component_t* c = &gui->area[ind];
		gf_gui_id_t	    p;
		if(c->parent == -1) return;
		while(1) {
			p = c->parent;

			ind = hmgeti(gui->area, p);
			if(ind != -1) {
				c = &gui->area[ind];
			}
			if(c->parent == -1) break;
		}
		gf_gui_move_topmost(gui, p);
	}
}
