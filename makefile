CC=gcc
CFLAGS=-I.

OBJ = main.o activeObject.o queue.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

activeObject: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -pthread

.PHONY: clean

clean:
	rm -f $(OBJ) activeObject
