TARGET = libnishbox.a
OBJS = version.o core.o draw.o log.o

include ../common.mk

$(TARGET): $(OBJS)
	$(AR) rcs $@ $(OBJS)
