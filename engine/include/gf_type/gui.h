#ifndef __GF_TYPE_GUI_H__
#define __GF_TYPE_GUI_H__

#include <gf_pre.h>
#include <gf_macro.h>

typedef int gf_gui_id_t;

#ifdef GF_EXPOSE_GUI
/* External library */

/* Engine */
#include <gf_type/draw.h>

/* Standard */

#define GF_GUI_MAX_COMPONENTS 64

enum GF_GUI_COMPONENT_TYPES {
	GF_GUI_UNUSED = -1,
	GF_GUI_BUTTON
};

GF_DECLARE_TYPE(gui_button, {
	char* text;
	int   pressed;
});

GF_DECLARE_TYPE(gui_component, {
	int   type;
	float x;
	float y;
	float w;
	float h;
	union {
		gf_gui_button_t button;
	} u;
});

GF_DECLARE_TYPE(gui, {
	gf_draw_t*	   draw;
	gf_gui_component_t area[GF_GUI_MAX_COMPONENTS];
});
#else
typedef void gf_gui_t;
typedef void gf_gui_component_t;
#endif

#endif
