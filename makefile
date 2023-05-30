CC=gcc
CFLAGS=-I.

OBJ = st_pipeline.o activeObject.o queue.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

st_pipeline: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -pthread

.PHONY: clean

clean:
	rm -f $(OBJ) st_pipeline
