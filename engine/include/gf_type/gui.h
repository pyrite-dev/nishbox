/**
 * @file gf_type/gui.h
 * @~english
 * @brief Type definitions related to GUI
 */

#ifndef __GF_TYPE_GUI_H__
#define __GF_TYPE_GUI_H__

#include <gf_pre.h>
#include <gf_macro.h>

/**
 * @~english
 * @brief Component ID
 */
typedef int gf_gui_id_t;

/**
 * @~english
 * @brief GUI events
 */
enum GF_GUI_EVENTS {
	GF_GUI_PRESS_EVENT = 0
};

#ifdef GF_EXPOSE_GUI
typedef struct gf_gui_button_t gf_gui_button_t;

typedef struct gf_gui_t		  gf_gui_t;
typedef struct gf_gui_component_t gf_gui_component_t;
typedef union gf_gui_union_t	  gf_gui_union_t;

/* External library */

/* Engine */
#include <gf_type/draw.h>
#include <gf_type/core.h>

/* Standard */

typedef void (*gf_gui_callback_t)(gf_engine_t* engine, gf_draw_t* draw, gf_gui_id_t id, int type);

/**
 * @~english
 * @brief GUI component types
 */
enum GF_GUI_COMPONENT_TYPES {
	GF_GUI_BUTTON = 0,
	GF_GUI_WINDOW
};

/**
 * @struct gf_gui_button_t
 * @~english
 * @brief Button component
 *
 * @var gf_gui_button_t::text
 * @brief Button text
 */
GF_DECLARE_TYPE(gui_button, { char* text; });

/**
 * @struct gf_gui_window_t
 * @~english
 * @brief Window component
 *
 * @var gf_gui_window_t::title
 * @brief Window title
 */
GF_DECLARE_TYPE(gui_window, { char* title; });

/**
 * @union gf_gui_union_t
 * @~english
 * @brief Component union
 *
 * @var gf_gui_union_t::button
 * @brief Button component
 *
 * @var gf_gui_union_t::window
 * @brief Window component
 */
typedef union gf_gui_union_t {
	gf_gui_button_t button;
	gf_gui_window_t window;
} gf_gui_union_t;

/**
 * @struct gf_gui_component_t
 * @~english
 * @brief Component
 *
 * @var gf_gui_component_t::key
 * @brief Component ID
 *
 * @var gf_gui_component_t::type
 * @brief Component type
 * @see GF_GUI_COMPONENT_TYPES
 *
 * @var gf_gui_component_t::x
 * @brief X coord of component
 *
 * @var gf_gui_component_t::y
 * @brief X coord of component
 *
 * @var gf_gui_component_t::width
 * @brief Width of component
 *
 * @var gf_gui_component_t::height
 * @brief Height of component
 *
 * @var gf_gui_component_t::pressed
 * @brief `1` if pressed, otherwise `0`
 *
 * @var gf_gui_component_t::callback
 * @brief Event callback
 *
 * @var gf_gui_component_t::u
 * @brief Component union
 *
 * @var gf_gui_component_t::parent
 * @brief Parent GUI component
 */
GF_DECLARE_TYPE(gui_component, {
	gf_gui_id_t	  key;
	int		  type;
	double		  x;
	double		  y;
	double		  width;
	double		  height;
	int		  pressed;
	gf_gui_id_t	  parent;
	gf_gui_callback_t callback;
	gf_gui_union_t	  u;
});

/**
 * @struct gf_gui_t
 * @~english
 * @brief GUI
 *
 * @var gf_gui_t::engine
 * @brief Engine instance
 *
 * @var gf_gui_t::draw
 * @brief Drawing interface
 *
 * @var gf_gui_t::pressed
 * @brief `1` if something is being pressed, otherwise `0`
 *
 * @var gf_gui_t::area
 * @brief Created components
 */
GF_DECLARE_TYPE(gui, {
	gf_engine_t*	    engine;
	gf_draw_t*	    draw;
	gf_gui_id_t	    pressed;
	gf_gui_component_t* area;
});
#else
typedef void* gf_gui_callback_t;

typedef void gf_gui_button_t;
typedef void gf_gui_window_t;

typedef void gf_gui_t;
typedef void gf_gui_component_t;
typedef void gf_gui_union_t;
#endif

#endif
