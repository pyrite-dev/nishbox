/**
 * @file gf_opengl.h
 * @~english
 * @brief OpenGL headers
 * @note User should not include this, this header is used internally
 */

#ifndef __GF_OPENGL_H__
#define __GF_OPENGL_H__

#if defined(USE_RGFW)
#define RGFW_USE_XDL
#define RGFWDEF extern

#include <RGFW.h>
#else
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#if defined(USE_X11)
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <GL/glx.h>
#elif defined(USE_GDI)
/* Should require nothing... for now? */
#endif
#endif

#endif
