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

int gf_lua_call_graphic_text(lua_State* s) {
	gf_font_t**	   font = luaL_checkudata(s, 1, "GoldFishFont");
	double		   x	= luaL_checknumber(s, 2);
	double		   y	= luaL_checknumber(s, 3);
	double		   sz	= luaL_checknumber(s, 4);
	const char*	   text = luaL_checkstring(s, 5);
	gf_lua_t*	   lua;
	gf_graphic_color_t col;

	lua_getglobal(s, "_GF_LUA");
	lua = lua_touserdata(s, -1);

	if(lua_gettop(s) == 7) {
		lua_rawgeti(s, 6, 1);
		col.r = lua_tonumber(s, -1);
		lua_pop(s, 1);

		lua_rawgeti(s, 6, 2);
		col.g = lua_tonumber(s, -1);
		lua_pop(s, 1);

		lua_rawgeti(s, 6, 3);
		col.b = lua_tonumber(s, -1);
		lua_pop(s, 1);

		lua_rawgeti(s, 6, 4);
		col.a = lua_tonumber(s, -1);
		lua_pop(s, 1);
	} else {
		col = lua->engine->client->draw->gui->font;
	}

	gf_graphic_text(lua->engine->client->draw, *font, x, y, sz, text, col);

	return 0;
}

int gf_lua_call_graphic_text_width(lua_State* s) {
	gf_font_t** font = luaL_checkudata(s, 1, "GoldFishFont");
	double	    sz	 = luaL_checknumber(s, 2);
	const char* text = luaL_checkstring(s, 3);
	gf_lua_t*   lua;

	lua_getglobal(s, "_GF_LUA");
	lua = lua_touserdata(s, -1);

	lua_pushnumber(s, gf_graphic_text_width(lua->engine->client->draw, *font, sz, text));

	return 1;
}

void gf_lua_create_goldfish_graphic(gf_lua_t* lua) {
	lua_pushstring(lua->lua, "graphic");
	lua_newtable(lua->lua);

	lua_pushstring(lua->lua, "text");
	lua_pushcfunction(lua->lua, gf_lua_call_graphic_text);
	lua_settable(lua->lua, -3);

	lua_pushstring(lua->lua, "text_width");
	lua_pushcfunction(lua->lua, gf_lua_call_graphic_text_width);
	lua_settable(lua->lua, -3);

	lua_settable(lua->lua, -3);
}
