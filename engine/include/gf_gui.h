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
 * @brief Create GUI
 * @param draw Drawing interface
 * @note You should not have to call this - simply use gf_draw_t::gui
 */
GF_EXPORT gf_gui_t*   gf_gui_create(gf_draw_t* draw);
GF_EXPORT gf_gui_id_t gf_gui_create_button(gf_gui_t* gui, float x, float y, float w, float h, const char* text);
GF_EXPORT void	      gf_gui_render(gf_gui_t* gui);

GF_EXPORT void gf_gui_draw_box(gf_gui_t* gui, int mul, float x, float y, float w, float h);

#endif
