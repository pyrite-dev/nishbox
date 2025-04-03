#define NB_EXPOSE_TEXTURE

#include "nb_pre.h"

/* External library */

/* Interface */
#include "nb_texture.h"

/* NishBox */
#include "nb_draw_driver.h"

/* Standard */

nb_texture_t* nb_register_texture(nb_draw_t* draw, int width, int height, unsigned char* data) { return nb_draw_driver_register_texture(draw, width, height, data); }

void nb_destroy_texture(nb_texture_t* texture) { nb_draw_driver_destroy_texture(texture); }
