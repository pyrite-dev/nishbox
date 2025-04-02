TARGET = libnishbox.a
OBJS = version.o core.o draw.o log.o $(BACKEND)_draw.o font.o stb_image.o math.o

include ../common.mk

include ext_lua.mk

$(TARGET): $(OBJS)
	$(AR) rcs $@ $(OBJS)

stb_image.c draw.c: ext_stb_image.h

ext_stb_image.h:
	wget https://github.com/nothings/stb/raw/refs/heads/master/stb_image.h -O $@
