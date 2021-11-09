CC = gcc
OBJ = main.o
CFLAGS = -c
LFLAGS = -lm -pthread 

vpath %.c src
vpath %.h src

output: $(OBJ) 
	$(CC) main.o -o $@ $(LFLAGS)

main.o: main.c project.h
	$(CC) $(CFLAGS) $^

clean: 
	rm -rf *.o output