.SUFFIXES: .c .o
.PHONY: all clean

all: $(TARGET)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET) *.a *.exe *.o ext_*
