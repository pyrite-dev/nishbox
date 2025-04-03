#ifndef __NB_TYPE_TEXTURE_H__
#define __NB_TYPE_TEXTURE_H__

#include <nb_pre.h>
#include <nb_macro.h>

#ifdef NB_EXPOSE_TEXTURE
/* External library */
#include <GL/gl.h>

/* NishBox */

/* Standard */

NB_DECLARE_TYPE(texture, { GLuint id; });
#else
typedef void nb_texture_t;
#endif

#endif
