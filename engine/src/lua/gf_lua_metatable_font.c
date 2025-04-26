#define GF_EXPOSE_LUA
#define GF_EXPOSE_CORE
#define GF_EXPOSE_CLIENT
#define GF_EXPOSE_DRAW
#define GF_EXPOSE_GUI

#include <gf_pre.h>

/* External library */
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include <stb_ds.h>

/* Interface */
#include <gf_lua.h>

/* Engine */
#include <gf_prop.h>
#include <gf_file.h>
#include <gf_log.h>
#include <gf_gui.h>
#include <gf_font.h>
#include <gf_gui_component.h>
#include <gf_graphic.h>

/* Standard */

gf_font_t** gf_lua_create_font(lua_State* s);

int gf_lua_meta_call_font_gc(lua_State* s) {
	gf_font_t** font = luaL_checkudata(s, 1, "GoldFishFont");
	gf_lua_t*   lua;

	lua_getglobal(s, "_GF_LUA");
	lua = lua_touserdata(s, -1);

	gf_font_destroy(*font);

	return 1;
}

void gf_lua_meta_init_font(gf_lua_t* lua) {
	luaL_newmetatable(lua->lua, "GoldFishFont");

	lua_pushstring(lua->lua, "__gc");
	lua_pushcfunction(lua->lua, gf_lua_meta_call_font_gc);
	lua_settable(lua->lua, -3);

	lua_pushvalue(lua->lua, -1);
	lua_setfield(lua->lua, -2, "__index");
}
