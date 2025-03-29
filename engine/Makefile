TARGET = libnishbox.a
OBJS = version.o core.o draw.o log.o $(BACKEND)_draw.o font.o

include ../common.mk

$(TARGET): $(OBJS)
	$(AR) rcs $@ $(OBJS)
