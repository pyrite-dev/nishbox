export
WINDOWS = NO
ifeq ($(PLATFORM),win32)
TARGET_PREFIX = i686-w64-mingw32-
WINDOWS = YES
endif

ifeq ($(PLATFORM),win64)
TARGET_PREFIX = x86_64-w64-mingw32-
WINDOWS = YES
endif

ifdef WINDOWS
ODE_CFLAGS = -I../deps/include
ODE_LIBS = -L../deps/lib -lode
AMX_CFLAGS = -I../deps/include
AMX_LIBS = -L../deps/lib -lamx
GL_CFLAGS =
GL_LIBS = -lopengl32 -lgdi32

BACKEND = WGL

EXEC = .exe
endif

ifeq ($(PLATFORM),)
ODE_CFLAGS = `pkg-config --cflags ode`
ODE_LIBS = `pkg-config --libs ode`
AMX_CFLAGS = `pkg-config --cflags amx`
AMX_LIBS = `pkg-config --libs amx`
GL_CFLAGS = `pkg-config --cflags gl`
GL_LIBS = `pkg-config --libs gl`

BACKEND = GLX

EXEC =
endif

AR = $(TARGET_PREFIX)ar
CC = $(TARGET_PREFIX)gcc
CFLAGS = -D_DEFAULT_SOURCE -DUSE_$(BACKEND) -I../engine $(ODE_CFLAGS) $(AMX_CFLAGS) $(GL_CFLAGS)
LDFLAGS =
LIBS = $(ODE_LIBS) $(AMX_LIBS) $(GL_LIBS)

.PHONY: all format clean ./engine ./src

all: ./src

format:
	clang-format --verbose -i `find ./src ./engine -name "*.c" -or -name "*.h"`

./engine::
	$(MAKE) -C $@

./src:: ./engine
	$(MAKE) -C $@

clean:
	$(MAKE) -C ./engine clean
	$(MAKE) -C ./src clean
