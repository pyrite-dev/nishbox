export
include mk/p_*.mk

AR = $(TARGET_PREFIX)ar
CC = $(TARGET_PREFIX)gcc
CFLAGS = -g -D_DEFAULT_SOURCE -DUSE_$(BACKEND) -I../engine $(ODE_CFLAGS) $(AMX_CFLAGS) $(PAWNC_CFLAGS) $(GL_CFLAGS)
LDFLAGS =
LIBS = $(ODE_LIBS) $(AMX_LIBS) $(PAWNC_LIBS) $(GL_LIBS)

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
