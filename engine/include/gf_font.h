/**
 * @file gf_font.h
 * @~english
 * @brief Font
 */

#ifndef __GF_FONT_H__
#define __GF_FONT_H__

#include <gf_pre.h>
#include <gf_macro.h>

/* Type */
#include <gf_type/font.h>

/* Engine */
#include <gf_type/draw.h>

/* Standard */

/**
 * @~english
 * @brief Get glyph
 * @param font Font
 * @param code Character code
 * @return Glyph
 */
GF_EXPORT gf_font_glyph_t* gf_font_get(gf_font_t* font, int code);

/**
 * @~english
 * @brief Load font
 * @param draw Drawing interface
 * @param path Path
 * @return Font
 */
GF_EXPORT gf_font_t* gf_font_create(gf_draw_t* draw, const char* path);

#endif
