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

void gf_graphic_fill_rect(gf_draw_t* draw, double x, double y, double w, double h, gf_graphic_color_t color) { gf_graphic_fill_polygon(draw, color, GF_GRAPHIC_2D, 4, x, y, x, y + h, x + w, y + h, x + w, y); }

void gf_graphic_text(gf_draw_t* draw, double x, double y, double size, const char* text, gf_graphic_color_t color) {
	int		 i;
	double		 mx = 0;
	gf_font_glyph_t* glyph;
	double		 zoom = 0;
	if(draw->font != NULL) {
		zoom = size / draw->font->bbox.height;
		for(i = 0; text[i] != 0; i++) {
			if((glyph = gf_font_get(draw->font, text[i])) != NULL) {
				double fax = glyph->bbox.width;
				double fay = glyph->bbox.height;
				double fx  = glyph->bbox.x;
				double fy  = (draw->font->bbox.height + draw->font->bbox.y) - (glyph->bbox.height + glyph->bbox.y);
				gf_graphic_draw_texture_2d(draw, x + mx + fx * zoom, y + fy * zoom, zoom * fax, zoom * fay, glyph->texture, color);
				mx += zoom * glyph->dwidth[0];
			}
		}
	}
}

double gf_graphic_text_width(gf_draw_t* draw, double size, const char* text) {
	int		 i;
	double		 mx = 0;
	gf_font_glyph_t* glyph;
	double		 zoom = 0;
	if(draw->font != NULL) {
		zoom = size / draw->font->bbox.height;
		for(i = 0; text[i] != 0; i++) {
			if((glyph = gf_font_get(draw->font, text[i])) != NULL) {
				mx += zoom * glyph->dwidth[0];
			}
		}
	}
	return mx;
}

void gf_graphic_draw_texture_2d(gf_draw_t* draw, double x, double y, double w, double h, gf_texture_t* texture, gf_graphic_color_t color) {
	if(texture != NULL) gf_graphic_draw_texture_polygon(draw, texture, color, GF_GRAPHIC_2D, 4, 0.0, 0.0, x, y, 0.0, 1.0, x, y + h, 1.0, 1.0, x + w, y + h, 1.0, 0.0, x + w, y);
}
