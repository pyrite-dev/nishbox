#ifndef __NB_TYPE_TEXTURE_H__
#define __NB_TYPE_TEXTURE_H__

#include <nb_pre.h>
#include <nb_macro.h>

#ifdef NB_EXPOSE_TEXTURE
/* External library */

/* NishBox */
#include <nb_type/draw_driver.h>

/* Standard */

NB_DECLARE_TYPE(texture, {
	nb_draw_driver_texture_t* draw_driver_texture;
	int			  width;
	int			  height;
});
#else
typedef void nb_texture_t;
#endif

#endif
