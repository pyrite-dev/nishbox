export
WINDOWS = NO

DRIVER = OPENGL

include mk/p_*.mk

# Lua is statically linked anyways, so this is fine.
LUA_CFLAGS = -DLUA_COMPAT_5_2 -DLUA_USE_C89 -I../external/lua
LUA_LDFLAGS =
LUA_LIBS =

STB_CFLAGS = -I../external/stb
STB_LDFLAGS =
STB_LIBS =

ZLIB_CFLAGS = -I../external/zlib -DHAVE_UNISTD_H=1 -DHAVE_STDARG_H=1
ZLIB_LDFLAGS =
ZLIB_LIBS =

CXX_LIBS = -lstdc++

AR = $(TARGET_PREFIX)ar
CC = $(TARGET_PREFIX)gcc
OBJDUMP = $(TARGET_PREFIX)objdump
STRIP = $(TARGET_PREFIX)strip
CFLAGS = -D_DEFAULT_SOURCE -DUSE_$(BACKEND) -DDRV_$(DRIVER) -I../engine/include $(ODE_CFLAGS) $(GL_CFLAGS) $(LUA_CFLAGS) $(STB_CFLAGS) $(ZLIB_CFLAGS)
LDFLAGS = $(LUA_LDFLAGS) $(STB_LDFLAGS) $(ZLIB_LDFLAGS)
LIBS = $(ODE_LIBS) $(GL_LIBS) $(SOCKET_LIBS) $(LUA_LIBS) $(CXX_LIBS) $(STB_LIBS) $(ZLIB_LIBS) $(MATH_LIBS)

.PHONY: all ext format clean ./engine ./src print-deps pack

all: ./src

format:
	clang-format --verbose -i `find ./src ./engine "(" -name "*.c" -or -name "*.h" ")" -and -not -name "ext_*"`

ext:
	cd ./engine && mkdir -p LUA && env DISCARD="lua.c" ../tool/genmk LUA ../external/lua > ext_lua.mk
	cd ./engine && mkdir -p ZLIB && ../tool/genmk ZLIB ../external/zlib > ext_zlib.mk

./engine:: ext
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
	rm -rf ./engine/LUA
	rm -rf ./engine/ZLIB
