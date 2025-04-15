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
 * @brief Default GUI font size
 */
#define GF_GUI_FONT_SIZE 16

/**
 * @~english
 * @brief Create GUI
 * @param draw Drawing interface
 * @return GUI
 * @note You should not have to call this - simply use gf_draw_t::gui
 */
GF_EXPORT gf_gui_t* gf_gui_create(gf_draw_t* draw);

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
GF_EXPORT gf_gui_id_t gf_gui_create_button(gf_gui_t* gui, float x, float y, float w, float h, const char* text);

/**
 * @~english
 * @brief Render GUI
 * @param gui GUI
 */
GF_EXPORT void gf_gui_render(gf_gui_t* gui);

/**
 * @~english
 * @brief Get first unused component entry
 * @param gui GUI
 * @param id Component ID to be returned
 * @return Pointer to component
 */
gf_gui_component_t* gf_gui_first_unused(gf_gui_t* gui, gf_gui_id_t* id);

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
GF_EXPORT void gf_gui_draw_box(gf_gui_t* gui, int mul, float x, float y, float w, float h);

#endif
