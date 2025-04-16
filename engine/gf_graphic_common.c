#define GF_EXPOSE_DRAW
#define GF_EXPOSE_TEXTURE
#define GF_EXPOSE_FONT

#include <gf_pre.h>

/* External library */

/* Interface */
#include <gf_graphic.h>

/* Engine */
#include <gf_draw.h>
#include <gf_font.h>

/* Standard */
#include <string.h>

void gf_graphic_fill_rect(gf_draw_t* draw, float x, float y, float w, float h, gf_graphic_color_t color) { gf_graphic_fill_polygon(draw, color, GF_GRAPHIC_2D, 4, x, y, x, y + h, x + w, y + h, x + w, y); }

void gf_graphic_text(gf_draw_t* draw, float x, float y, float size, const char* text, gf_graphic_color_t color) {
	int		 i;
	double		 mx = 0;
	gf_font_glyph_t* glyph;
	for(i = 0; text[i] != 0; i++) {
		if(draw->font != NULL && (glyph = gf_font_get(draw->font, text[i])) != NULL) {
			double fax = glyph->bbox.height;
			double fay = glyph->bbox.width;
			gf_graphic_draw_texture_2d(draw, x + mx, y, size * fax / fay, size, glyph->texture, color);
			mx += (size * glyph->dwidth[0]);
		}
	}
}

float gf_graphic_text_width(gf_draw_t* draw, float size, const char* text) { return 0; }

void gf_graphic_draw_texture_2d(gf_draw_t* draw, float x, float y, float w, float h, gf_texture_t* texture, gf_graphic_color_t color) {
	if(texture != NULL) gf_graphic_draw_texture_polygon(draw, texture, color, GF_GRAPHIC_2D, 4, 0.0, 0.0, x, y, 0.0, 1.0, x, y + h, 1.0, 1.0, x + w, y + h, 1.0, 0.0, x + w, y);
}
