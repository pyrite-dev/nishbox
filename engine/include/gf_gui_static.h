/**
 * @file gf_gui_static.h
 * @~english
 * @brief GUI static stuff
 * @note User should not include this, this header is used internally
 * @warning This file is auto-generated using ./tool/gengui.sh at `Sat Apr 26 11:00:47 JST 2025`
 */

#ifndef __GF_GUI_STATIC_H__
#define __GF_GUI_STATIC_H__

#include <gf_pre.h>
#include <gf_macro.h>

/* Type */

/* Engine */
#include <gf_type/gui.h>
#include <gf_gui_component.h>

/* Standard */
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#define GF_GUI_COMPONENTS 3
/**
 * @~english
 * @brief Initialize GUI component calls
 */
static void gf_gui_init_calls(void) {
	extern gf_gui_call_t gf_gui_calls[3];
	/*** Begin button ***/
	gf_gui_calls[0].name = malloc(512);
	strcpy(gf_gui_calls[0].name, "button");
	gf_gui_calls[0].call = gf_gui_create_button;
	/***  End  button ***/
	/*** Begin frame ***/
	gf_gui_calls[1].name = malloc(512);
	strcpy(gf_gui_calls[1].name, "frame");
	gf_gui_calls[1].call = gf_gui_create_frame;
	/***  End  frame ***/
	/*** Begin window ***/
	gf_gui_calls[2].name = malloc(512);
	strcpy(gf_gui_calls[2].name, "window");
	gf_gui_calls[2].call = gf_gui_create_window;
	/***  End  window ***/
}
/**
 * @~english
 * @brief Run `render` procedure for all components
 * @param gui GUI
 * @param c Component
 */
static void gf_gui_all_render(gf_gui_t* gui, gf_gui_component_t* c) {
	extern void gf_gui_button_render(gf_gui_t * gui, gf_gui_component_t * c);
	extern void gf_gui_frame_render(gf_gui_t * gui, gf_gui_component_t * c);
	extern void gf_gui_window_render(gf_gui_t * gui, gf_gui_component_t * c);
	gf_gui_button_render(gui, c);
	gf_gui_frame_render(gui, c);
	gf_gui_window_render(gui, c);
}

/**
 * @~english
 * @brief Run `drag` procedure for all components
 * @param gui GUI
 * @param c Component
 */
static void gf_gui_all_drag(gf_gui_t* gui, gf_gui_component_t* c) {
	extern void gf_gui_button_drag(gf_gui_t * gui, gf_gui_component_t * c);
	extern void gf_gui_frame_drag(gf_gui_t * gui, gf_gui_component_t * c);
	extern void gf_gui_window_drag(gf_gui_t * gui, gf_gui_component_t * c);
	gf_gui_button_drag(gui, c);
	gf_gui_frame_drag(gui, c);
	gf_gui_window_drag(gui, c);
}

/**
 * @~english
 * @brief Run `click` procedure for all components
 * @param gui GUI
 * @param c Component
 */
static void gf_gui_all_click(gf_gui_t* gui, gf_gui_component_t* c) {
	extern void gf_gui_button_click(gf_gui_t * gui, gf_gui_component_t * c);
	extern void gf_gui_frame_click(gf_gui_t * gui, gf_gui_component_t * c);
	extern void gf_gui_window_click(gf_gui_t * gui, gf_gui_component_t * c);
	gf_gui_button_click(gui, c);
	gf_gui_frame_click(gui, c);
	gf_gui_window_click(gui, c);
}

#ifdef __cplusplus
}
#endif

#endif
