TARGET = nishbox$(EXEC)
OBJS = main.o

include ../common.mk

$(TARGET): $(OBJS) ../engine/libnishbox.a
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS) ../engine/libnishbox.a
