export
WINDOWS = NO

DRIVER = OPENGL

include mk/p_*.mk

# Lua is statically linked anyways, so this is fine.
LUA_CFLAGS = -DLUA_COMPAT_5_2 -DLUA_USE_C89 -I../external/lua -DNB_EXPOSE_ALL
LUA_LDFLAGS =
LUA_LIBS =

AR = $(TARGET_PREFIX)ar
CC = $(TARGET_PREFIX)gcc
OBJDUMP = $(TARGET_PREFIX)objdump
STRIP = $(TARGET_PREFIX)strip
CFLAGS = -D_DEFAULT_SOURCE -DUSE_$(BACKEND) -DDRV_$(DRIVER) -I../engine $(ODE_CFLAGS) $(GL_CFLAGS) $(LUA_CFLAGS)
LDFLAGS = $(LUA_LDFLAGS)
LIBS = $(ODE_LIBS) $(GL_LIBS) $(SOCKET_LIBS) $(LUA_LIBS)

.PHONY: all format clean ./engine ./src print-deps pack

all: ./src

format:
	clang-format --verbose -i `find ./src ./engine "(" -name "*.c" -or -name "*.h" ")" -and -not -name "ext_*"`

./engine::
	cd $@ && env DISCARD="lua.c" ../tool/genmk LUA ../external/lua > ext_lua.mk
	$(MAKE) -C $@

./src:: ./engine
	$(MAKE) -C $@

print-deps:
	@sh ./tool/deps.sh

pack: all
	@sh ./tool/pack.sh

clean:
	$(MAKE) -C ./engine clean
	$(MAKE) -C ./src clean
