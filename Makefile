export
WINDOWS = NO

include mk/p_*.mk

AR = $(TARGET_PREFIX)ar
CC = $(TARGET_PREFIX)gcc
OBJDUMP = $(TARGET_PREFIX)objdump
STRIP = $(TARGET_PREFIX)strip
CFLAGS = -D_DEFAULT_SOURCE -DUSE_$(BACKEND) -I../engine $(ODE_CFLAGS) $(GL_CFLAGS)
LDFLAGS =
LIBS = $(ODE_LIBS) $(GL_LIBS) $(SOCKET_LIBS)

.PHONY: all format clean ./engine ./src print-deps pack

all: ./src

format:
	clang-format --verbose -i `find ./src ./engine "(" -name "*.c" -or -name "*.h" ")" -and -not -name "ext_*"`

./engine::
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
