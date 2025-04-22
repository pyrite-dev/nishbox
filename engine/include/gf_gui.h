/**
 * @file gf_gui.h
 * @~english
 * @brief GUI
 */

#ifndef __GF_GUI_H__
#define __GF_GUI_H__

#include <gf_pre.h>
#include <gf_macro.h>

/* Type */
#include <gf_type/gui.h>

/* Engine */
#include <gf_type/draw.h>
#include <gf_type/core.h>

/* Standard */

/**
 * @~english
 * @brief Draw border normally
 */
#define GF_GUI_NORMAL 1

/**
 * @~english
 * @brief Draw border inverted
 */
#define GF_GUI_INVERT -1

/**
 * @~english
 * @brief Value to be returned for "no such property"
 */
#define GF_GUI_NO_SUCH_PROP 0xffffff

/**
 * @~english
 * @brief Default GUI font size
 */
#define GF_GUI_FONT_SIZE 30

/**
 * @~english
 * @brief Default GUI small font size
 */
#define GF_GUI_SMALL_FONT_SIZE 20

/**
 * @~english
 * @brief Create GUI
 * @param engine Engine instance
 * @param draw Drawing interface
 * @return GUI
 */
GF_EXPORT gf_gui_t* gf_gui_create(gf_engine_t* engine, gf_draw_t* draw);

/**
 * @~english
 * @brief Destroy GUI
 * @param gui GUI
 */
GF_EXPORT void gf_gui_destroy(gf_gui_t* gui);

/**
 * @~english
 * @brief Destroy GUI component by ID
 * @param gui GUI
 * @param id Component ID
 */
GF_EXPORT void gf_gui_destroy_id(gf_gui_t* gui, gf_gui_id_t id);

/**
 * @~english
 * @brief Create button component
 * @param gui GUI
 * @param x X coord of button
 * @param y Y coord of button
 * @param w Width of button
 * @param h Height of button
 * @param text Button text
 * @return Component ID
 */
GF_EXPORT gf_gui_id_t gf_gui_create_button(gf_gui_t* gui, double x, double y, double w, double h, const char* text);

/**
 * @~english
 * @brief Create window component
 * @param gui GUI
 * @param x X coord of window
 * @param y Y coord of window
 * @param w Width of window
 * @param h Height of window
 * @param title Window title
 * @return Component ID
 */
GF_EXPORT gf_gui_id_t gf_gui_create_window(gf_gui_t* gui, double x, double y, double w, double h, const char* title);

/**
 * @~english
 * @brief Render GUI
 * @param gui GUI
 */
GF_EXPORT void gf_gui_render(gf_gui_t* gui);

/**
 * @~english
 * @brief Render box
 * @param gui GUI
 * @param mul GF_GUI_NORMAL or GF_GUI_INVERT
 * @param x X coord of box
 * @param y Y coord of box
 * @param w Width of box
 * @param h Height of box
 */
GF_EXPORT void gf_gui_draw_box(gf_gui_t* gui, int mul, double x, double y, double w, double h);

/**
 * @~english
 * @brief Set callback
 * @param gui GUI
 * @param id Component ID
 * @param callback Callback
 */
GF_EXPORT void gf_gui_set_callback(gf_gui_t* gui, gf_gui_id_t id, gf_gui_callback_t callback);

/**
 * @~english
 * @brief Set parent component
 * @param gui GUI
 * @param id Component ID
 * @param parent Parent component ID
 */
GF_EXPORT void gf_gui_set_parent(gf_gui_t* gui, gf_gui_id_t id, gf_gui_id_t parent);

/**
 * @~english
 * @brief Set property
 * @param gui GUI
 * @param id Component ID
 * @param key Key
 * @param value Value
 */
GF_EXPORT void gf_gui_set_prop(gf_gui_t* gui, gf_gui_id_t id, const char* key, int value);

/**
 * @~english
 * @brief Get property
 * @param gui GUI
 * @param id Component ID
 * @param key Key
 * @return Value
 */
GF_EXPORT int gf_gui_get_prop(gf_gui_t* gui, gf_gui_id_t id, const char* key);

#endif
