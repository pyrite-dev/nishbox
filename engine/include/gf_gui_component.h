/**
 * @file gf_gui_component.h
 * @~english
 * @brief GUI component stuff
 * @warning This file is auto-generated using ./tool/gengui.sh at `Wed Apr 23 23:51:41 JST 2025`
 */

#ifndef __GF_GUI_COMPONENT_H__
#define __GF_GUI_COMPONENT_H__

#include <gf_pre.h>
#include <gf_macro.h>

/* Type */

/* Engine */
#include <gf_type/gui.h>

/* Standard */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @~english
 * @brief Create button component
 * @param gui GUI
 * @param x X
 * @param y Y
 * @param w Width
 * @param h Height
 * @return Component ID
 */
GF_EXPORT gf_gui_id_t gf_gui_create_button(gf_gui_t* gui, double x, double y, double w, double h);

/**
 * @~english
 * @brief Create frame component
 * @param gui GUI
 * @param x X
 * @param y Y
 * @param w Width
 * @param h Height
 * @return Component ID
 */
GF_EXPORT gf_gui_id_t gf_gui_create_frame(gf_gui_t* gui, double x, double y, double w, double h);

/**
 * @~english
 * @brief Create window component
 * @param gui GUI
 * @param x X
 * @param y Y
 * @param w Width
 * @param h Height
 * @return Component ID
 */
GF_EXPORT gf_gui_id_t gf_gui_create_window(gf_gui_t* gui, double x, double y, double w, double h);

#ifdef __cplusplus
}
#endif

#endif
