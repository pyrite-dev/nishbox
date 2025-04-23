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
#include <gf_gui_component.h>

/* Standard */

#ifdef __cplusplus
extern "C" {
#endif

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
 * @brief Set text
 * @param gui GUI
 * @param id Component ID
 * @param text Text
 */
GF_EXPORT void gf_gui_set_text(gf_gui_t* gui, gf_gui_id_t id, const char* text);

/**
 * @~english
 * @brief Set property
 * @param gui GUI
 * @param id Component ID
 * @param key Key
 * @param value Value
 */
GF_EXPORT void gf_gui_set_prop(gf_gui_t* gui, gf_gui_id_t id, const char* key, gf_gui_prop_value_t value);

/**
 * @~english
 * @brief Delete property
 * @param gui GUI
 * @param id Component ID
 * @param key Key
 */
GF_EXPORT void gf_gui_delete_prop(gf_gui_t* gui, gf_gui_id_t id, const char* key);

/**
 * @~english
 * @brief Get property
 * @param gui GUI
 * @param id Component ID
 * @param key Key
 * @return Value
 */
GF_EXPORT gf_gui_prop_value_t gf_gui_get_prop(gf_gui_t* gui, gf_gui_id_t id, const char* key);

/**
 * @~english
 * @brief Sort components
 * @param gui GUI
 */
GF_EXPORT void gf_gui_sort_component(gf_gui_t* gui);

/**
 * @~english
 * @brief Move component topmost
 * @param gui GUI
 * @param id Component ID
 */
GF_EXPORT void gf_gui_move_topmost(gf_gui_t* gui, gf_gui_id_t id);

/**
 * @~english
 * @brief Initialize component
 * @param gui GUI
 * @param c Component
 * @param x X
 * @param y Y
 * @param w Width
 * @param h Height
 */
GF_EXPORT void gf_gui_create_component(gf_gui_t* gui, gf_gui_component_t* c, double x, double y, double w, double h);

/**
 * @~english
 * @brief Calculate component X/Y/width/height
 * @param gui GUI
 * @param c Component
 * @param x X
 * @param y Y
 * @param w Width
 * @param h Height
 */
GF_EXPORT void gf_gui_calc_xywh(gf_gui_t* gui, gf_gui_component_t* c, double* x, double* y, double* w, double* h);

#ifdef __cplusplus
}
#endif

#endif
