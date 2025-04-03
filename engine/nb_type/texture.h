#ifndef __NB_TYPE_TEXTURE_H__
#define __NB_TYPE_TEXTURE_H__

#include <nb_pre.h>
#include <nb_macro.h>

#ifdef NB_EXPOSE_TEXTURE
/* External library */

/* NishBox */
#include <nb_type/draw_driver.h>

/* Standard */

typedef nb_draw_driver_texture_t nb_texture_t;
#else
typedef void nb_texture_t;
#endif

#endif
