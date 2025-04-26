#define GF_EXPOSE_LUA
#define GF_EXPOSE_CORE
#define GF_EXPOSE_CLIENT
#define GF_EXPOSE_DRAW

#include <gf_pre.h>

/* External library */
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
#include <stb_ds.h>

/* Interface */
#include <gf_lua.h>

/* Engine */
#include <gf_file.h>
#include <gf_log.h>
#include <gf_gui.h>
#include <gf_gui_component.h>

/* Standard */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int gf_lua_call_gui_create(lua_State* s) {
	const char* str = luaL_checkstring(s, 1);
	double	    x	= luaL_checknumber(s, 2);
	double	    y	= luaL_checknumber(s, 3);
	double	    w	= luaL_checknumber(s, 4);
	double	    h	= luaL_checknumber(s, 5);
	gf_lua_t*   lua;
	int	    i;

	lua_getglobal(s, "_GF_LUA");
	lua = lua_touserdata(s, -1);

	for(i = 0; i < sizeof(gf_gui_calls) / sizeof(gf_gui_calls[0]); i++) {
		if(strcmp(gf_gui_calls[i].name, str) == 0) {
			gf_lua_gui_component_t* id = lua_newuserdata(s, sizeof(*id));
			id->id			   = gf_gui_calls[i].call(lua->engine->client->draw->gui, x, y, w, h);
			luaL_getmetatable(s, "GoldFishGUIComponent");
			lua_setmetatable(s, -2);
			return 1;
		}
	}
	return 0;
}

int gf_lua_call_gui_component_text(lua_State* s) {
	gf_lua_gui_component_t* id  = luaL_checkudata(s, 1, "GoldFishGUIComponent");
	const char*		str = luaL_checkstring(s, 2);
	gf_lua_t*		lua;

	lua_getglobal(s, "_GF_LUA");
	lua = lua_touserdata(s, -1);

	gf_gui_set_text(lua->engine->client->draw->gui, id->id, str);
	return 0;
}

int gf_lua_call_gui_component_prop_id(lua_State* s) {
	gf_lua_gui_component_t* id  = luaL_checkudata(s, 1, "GoldFishGUIComponent");
	const char*		str = luaL_checkstring(s, 2);
	gf_lua_gui_component_t* r;
	gf_lua_t*		lua;

	lua_getglobal(s, "_GF_LUA");
	lua = lua_touserdata(s, -1);

	r = lua_newuserdata(s, sizeof(*r));
	luaL_getmetatable(s, "GoldFishGUIComponent");
	lua_setmetatable(s, -2);
	r->id = gf_gui_get_prop_id(lua->engine->client->draw->gui, id->id, str);
	return 1;
}

int gf_lua_call_gui_component_callback(lua_State* s) {
	gf_lua_gui_component_t* id = luaL_checkudata(s, 1, "GoldFishGUIComponent");
	gf_lua_t*		lua;

	lua_getglobal(s, "_GF_LUA");
	lua = lua_touserdata(s, -1);
	return 0;
}

int gf_lua_call_gui_component_parent(lua_State* s) {
	gf_lua_gui_component_t* id     = luaL_checkudata(s, 1, "GoldFishGUIComponent");
	gf_lua_gui_component_t* parent = luaL_checkudata(s, 2, "GoldFishGUIComponent");
	gf_lua_t*		lua;

	lua_getglobal(s, "_GF_LUA");
	lua = lua_touserdata(s, -1);

	gf_gui_set_parent(lua->engine->client->draw->gui, id->id, parent->id);
	return 0;
}

int gf_lua_call_gui_sort(lua_State* s) {
	gf_lua_t* lua;

	lua_getglobal(s, "_GF_LUA");
	lua = lua_touserdata(s, -1);

	gf_gui_sort_component(lua->engine->client->draw->gui);

	return 0;
}

void gf_lua_create_goldfish_gui(gf_lua_t* lua) {
	int i;

	lua_pushstring(lua->lua, "gui");
	lua_newtable(lua->lua);

	lua_pushstring(lua->lua, "create");
	lua_pushcfunction(lua->lua, gf_lua_call_gui_create);
	lua_settable(lua->lua, -3);

	lua_pushstring(lua->lua, "sort");
	lua_pushcfunction(lua->lua, gf_lua_call_gui_sort);
	lua_settable(lua->lua, -3);

	lua_settable(lua->lua, -3);
}

void gf_lua_create_goldfish(gf_lua_t* lua) {
	lua_newtable(lua->lua);

	gf_lua_create_goldfish_gui(lua);

	lua_setglobal(lua->lua, "goldfish");
}

gf_lua_t* gf_lua_create(gf_engine_t* engine) {
	gf_lua_t* lua = malloc(sizeof(*lua));
	memset(lua, 0, sizeof(*lua));
	lua->engine = engine;

	lua->lua = luaL_newstate();
	luaL_openlibs(lua->lua);

	lua_pushlightuserdata(lua->lua, lua);
	lua_setglobal(lua->lua, "_GF_LUA");

	luaL_newmetatable(lua->lua, "GoldFishGUIComponent");

	lua_pushstring(lua->lua, "text");
	lua_pushcfunction(lua->lua, gf_lua_call_gui_component_text);
	lua_settable(lua->lua, -3);

	lua_pushstring(lua->lua, "parent");
	lua_pushcfunction(lua->lua, gf_lua_call_gui_component_parent);
	lua_settable(lua->lua, -3);

	lua_pushstring(lua->lua, "prop_id");
	lua_pushcfunction(lua->lua, gf_lua_call_gui_component_prop_id);
	lua_settable(lua->lua, -3);

	lua_pushstring(lua->lua, "callback");
	lua_pushcfunction(lua->lua, gf_lua_call_gui_component_callback);
	lua_settable(lua->lua, -3);

	lua_pushvalue(lua->lua, -1);
	lua_setfield(lua->lua, -2, "__index");

	gf_lua_create_goldfish(lua);

	return lua;
}

int gf_lua_run(gf_lua_t* lua, const char* path) {
	gf_file_t* f = gf_file_open(lua->engine, path, "r");
	char*	   str;
	if(f == NULL) return -1;
	str = malloc(f->size + 1);
	gf_file_read(f, str, f->size);
	str[f->size] = 0;

	if(luaL_loadstring(lua->lua, str)) {
		free(str);
		gf_file_close(f);
		return -1;
	}

	if(lua_pcall(lua->lua, 0, LUA_MULTRET, 0)) {
		gf_log_function(lua->engine, "Lua error: %s", lua_tostring(lua->lua, -1));
		free(str);
		gf_file_close(f);
		return -1;
	}

	free(str);
	gf_file_close(f);
	return 0;
}

void gf_lua_destroy(gf_lua_t* lua) {
	int i;
	lua_close(lua->lua);
	gf_log_function(lua->engine, "Destroyed Lua interface", "");
	free(lua);
}
