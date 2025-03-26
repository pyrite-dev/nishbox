export
ODE_CFLAGS = `pkg-config --cflags ode`
ODE_LIBS = `pkg-config --libs ode`
AMX_CFLAGS = `pkg-config --cflags amx`
AMX_LIBS = `pkg-config --libs amx`
GL_CFLAGS = `pkg-config --cflags gl`
GL_LIBS = `pkg-config --libs gl`

AR = $(TARGET_PREFIX)ar
CC = $(TARGET_PREFIX)gcc
CFLAGS = -D_DEFAULT_SOURCE -I../engine $(ODE_CFLAGS) $(AMX_CFLAGS) $(GL_CFLAGS)
LDFLAGS =
LIBS = $(ODE_LIBS) $(AMX_LIBS) $(GL_LIBS)

EXEC =

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
