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
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int gf_lua_call_loop(lua_State* s) {
	int	  call = luaL_ref(s, LUA_REGISTRYINDEX);
	gf_lua_t* lua;

	lua_getglobal(s, "_GF_LUA");
	lua = lua_touserdata(s, -1);

	lua->loop = call;

	return 0;
}

void gf_lua_create_goldfish(gf_lua_t* lua) {
	lua_newtable(lua->lua);

	gf_lua_create_goldfish_gui(lua);
	gf_lua_create_goldfish_graphic(lua);
	gf_lua_create_goldfish_font(lua);

	lua_pushstring(lua->lua, "loop");
	lua_pushcfunction(lua->lua, gf_lua_call_loop);
	lua_settable(lua->lua, -3);

	lua_setglobal(lua->lua, "goldfish");
}

gf_lua_t* gf_lua_create(gf_engine_t* engine) {
	gf_lua_t* lua = malloc(sizeof(*lua));
	memset(lua, 0, sizeof(*lua));
	lua->engine = engine;

	lua->loop = 0;
	lua->lua  = luaL_newstate();
	luaL_openlibs(lua->lua);

	lua_pushlightuserdata(lua->lua, lua);
	lua_setglobal(lua->lua, "_GF_LUA");

	gf_lua_meta_init(lua);

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

void gf_lua_step(gf_lua_t* lua) {
	if(lua->loop == 0) return;

	lua_rawgeti(lua->lua, LUA_REGISTRYINDEX, lua->loop);
	lua_pcall(lua->lua, 0, 0, 0);
}

void gf_lua_destroy(gf_lua_t* lua) {
	int i;
	lua_close(lua->lua);
	gf_log_function(lua->engine, "Destroyed Lua interface", "");
	free(lua);
}
