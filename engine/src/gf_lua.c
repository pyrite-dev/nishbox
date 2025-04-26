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
#include <gf_gui_component.h>

/* Standard */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

gf_gui_id_t* gf_lua_create_gui_id(lua_State* s) {
	gf_gui_id_t* id = lua_newuserdata(s, sizeof(*id));
	luaL_getmetatable(s, "GoldFishGUIComponent");
	lua_setmetatable(s, -2);
	return id;
}

void gf_lua_gui_callback(gf_engine_t* engine, gf_draw_t* draw, gf_gui_id_t id, int type) {
	int*	     call = gf_prop_get_ptr(gf_gui_get_prop(draw->gui, id), "luacall");
	gf_lua_t*    lua;
	gf_gui_id_t* pid;
	if(call == NULL) return;

	lua = *(gf_lua_t**)gf_prop_get_ptr(gf_gui_get_prop(draw->gui, id), "lua");

	lua_rawgeti(lua->lua, LUA_REGISTRYINDEX, *call);

	pid  = gf_lua_create_gui_id(lua->lua);
	*pid = id;

	lua_pushnumber(lua->lua, type);
	lua_pcall(lua->lua, 2, 0, 0);
}

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
			void**	     plua = malloc(sizeof(*plua));
			gf_gui_id_t* id	  = gf_lua_create_gui_id(s);

			*plua = lua;

			*id = gf_gui_calls[i].call(lua->engine->client->draw->gui, x, y, w, h);

			gf_gui_set_callback(lua->engine->client->draw->gui, *id, gf_lua_gui_callback);

			gf_prop_set_ptr(gf_gui_get_prop(lua->engine->client->draw->gui, *id), "lua", (void*)plua);

			return 1;
		}
	}
	return 0;
}

int gf_lua_call_gui_component_text(lua_State* s) {
	gf_gui_id_t* id	 = luaL_checkudata(s, 1, "GoldFishGUIComponent");
	const char*  str = luaL_checkstring(s, 2);
	gf_lua_t*    lua;

	lua_getglobal(s, "_GF_LUA");
	lua = lua_touserdata(s, -1);

	gf_gui_set_text(lua->engine->client->draw->gui, *id, str);
	return 0;
}

int gf_lua_call_gui_component_destroy(lua_State* s) {
	gf_gui_id_t* id = luaL_checkudata(s, 1, "GoldFishGUIComponent");
	gf_lua_t*    lua;

	lua_getglobal(s, "_GF_LUA");
	lua = lua_touserdata(s, -1);

	gf_gui_destroy_id(lua->engine->client->draw->gui, *id);
	return 0;
}

int gf_lua_call_gui_component_prop(lua_State* s) {
	gf_gui_id_t* id	  = luaL_checkudata(s, 1, "GoldFishGUIComponent");
	const char*  type = luaL_checkstring(s, 2);
	const char*  str  = luaL_checkstring(s, 3);
	gf_lua_t*    lua;

	lua_getglobal(s, "_GF_LUA");
	lua = lua_touserdata(s, -1);

	if(lua_gettop(s) == 5) {
		if(strcmp(type, "id") == 0) {
			gf_gui_id_t* t = luaL_checkudata(s, 4, "GoldFishGUIComponent");
			gf_gui_set_prop_id(lua->engine->client->draw->gui, *id, str, *t);
		} else if(strcmp(type, "integer") == 0) {
			lua_Integer t = luaL_checkinteger(s, 4);
			gf_prop_set_integer(gf_gui_get_prop(lua->engine->client->draw->gui, *id), str, t);
		} else if(strcmp(type, "floating") == 0) {
			lua_Number t = luaL_checknumber(s, 4);
			gf_prop_set_floating(gf_gui_get_prop(lua->engine->client->draw->gui, *id), str, t);
		}
		return 0;
	} else {
		if(strcmp(type, "id") == 0) {
			gf_gui_id_t* r = gf_lua_create_gui_id(s);
			*r	       = gf_gui_get_prop_id(lua->engine->client->draw->gui, *id, str);
		} else if(strcmp(type, "integer") == 0) {
			lua_pushinteger(s, gf_prop_get_integer(gf_gui_get_prop(lua->engine->client->draw->gui, *id), str));
		} else if(strcmp(type, "floating") == 0) {
			lua_pushnumber(s, gf_prop_get_floating(gf_gui_get_prop(lua->engine->client->draw->gui, *id), str));
		}
	}
	return 1;
}

int gf_lua_call_gui_component_callback(lua_State* s) {
	gf_gui_id_t* id = luaL_checkudata(s, 1, "GoldFishGUIComponent");
	gf_lua_t*    lua;

	lua_getglobal(s, "_GF_LUA");
	lua = lua_touserdata(s, -1);

	if(lua_gettop(s) == 3) {
		int* ptr = malloc(sizeof(*ptr));
		lua_pop(s, 1);
		*ptr = luaL_ref(s, LUA_REGISTRYINDEX);
		gf_prop_set_ptr(gf_gui_get_prop(lua->engine->client->draw->gui, *id), "luacall", (void*)ptr);
	} else {
		gf_prop_delete(gf_gui_get_prop(lua->engine->client->draw->gui, *id), "luacall");
	}
	return 0;
}

int gf_lua_call_gui_component_parent(lua_State* s) {
	gf_gui_id_t* id = luaL_checkudata(s, 1, "GoldFishGUIComponent");
	gf_gui_id_t* parent;
	gf_lua_t*    lua;

	lua_getglobal(s, "_GF_LUA");
	lua = lua_touserdata(s, -1);

	if(lua_gettop(s) == 3) {
		parent = luaL_checkudata(s, 2, "GoldFishGUIComponent");
		gf_gui_set_parent(lua->engine->client->draw->gui, *id, *parent);
		return 0;
	} else {
		parent	= gf_lua_create_gui_id(s);
		*parent = gf_gui_get_parent(lua->engine->client->draw->gui, *id);
		return 1;
	}
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

	lua_pushstring(lua->lua, "PRESS_EVENT");
	lua_pushnumber(lua->lua, GF_GUI_PRESS_EVENT);
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

	lua_pushstring(lua->lua, "destroy");
	lua_pushcfunction(lua->lua, gf_lua_call_gui_component_destroy);
	lua_settable(lua->lua, -3);

	lua_pushstring(lua->lua, "prop");
	lua_pushcfunction(lua->lua, gf_lua_call_gui_component_prop);
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
