#ifndef __NE_TYPE_TEXTURE_H__
#define __NE_TYPE_TEXTURE_H__

#include <ne_pre.h>
#include <ne_macro.h>

#ifdef NE_EXPOSE_TEXTURE
/* External library */

/* NishBox */
#include <ne_type/draw_driver.h>

/* Standard */

NE_DECLARE_TYPE(texture, {
	ne_draw_driver_texture_t* draw_driver_texture;
	int			  width;
	int			  height;
});
#else
typedef void ne_texture_t;
#endif

#endif
