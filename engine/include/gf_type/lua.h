/**
 * @file gf_type/lua.h
 * @~english
 * @brief Type definitions related to lua
 */

#ifndef __GF_TYPE_LUA_H__
#define __GF_TYPE_LUA_H__

#include <gf_pre.h>
#include <gf_macro.h>

#ifdef GF_EXPOSE_LUA
typedef struct gf_lua_t		      gf_lua_t;
typedef struct gf_lua_gui_component_t gf_lua_gui_component_t;

/* External library */
#include <lua.h>

/* Engine */
#include <gf_type/core.h>
#include <gf_type/gui.h>

/* Standard */

/**
 * @struct gf_lua_t
 * @~english
 * @brief Lua interface
 *
 * @var gf_lua_t::engine
 * @brief Engine instance
 */
GF_DECLARE_TYPE(lua, {
	gf_engine_t* engine;
	lua_State*   lua;
});

GF_DECLARE_TYPE(lua_gui_component, { gf_gui_id_t id; });
#else
typedef void gf_lua_t;
typedef void gf_lua_gui_component_t;
#endif

#endif
