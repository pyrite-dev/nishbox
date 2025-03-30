export
WINDOWS = NO

include mk/p_*.mk

AR = $(TARGET_PREFIX)ar
CC = $(TARGET_PREFIX)gcc
OBJDUMP = $(TARGET_PREFIX)objdump
CFLAGS = -g -D_DEFAULT_SOURCE -DUSE_$(BACKEND) -I../engine $(ODE_CFLAGS) $(AMX_CFLAGS) $(PAWNC_CFLAGS) $(GL_CFLAGS)
LDFLAGS =
LIBS = $(ODE_LIBS) $(AMX_LIBS) $(PAWNC_LIBS) $(GL_LIBS) $(SOCKET_LIBS)

.PHONY: all format clean ./engine ./src print-deps

all: ./src

format:
	clang-format --verbose -i `find ./src ./engine -name "*.c" -or -name "*.h"`

./engine::
	$(MAKE) -C $@

./src:: ./engine
	$(MAKE) -C $@

print-deps:
	@sh ./tool/deps.sh

clean:
	$(MAKE) -C ./engine clean
	$(MAKE) -C ./src clean
