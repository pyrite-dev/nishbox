TARGET = nishbox$(EXEC)
OBJS = main.o

include ../common.mk

$(TARGET): $(OBJS) ../engine/libnishbox.a
	$(CC) $(LDFLAGS) -o $@ $(OBJS) ../engine/libnishbox.a $(LIBS)
