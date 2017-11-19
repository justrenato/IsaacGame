CFLAGS = -Wall -g
LFLAGS = -lncurses

objects = lerMapa.o isaaclib.o

all: lerMapa


lerMapa: $(objects)
	gcc -o isaacGame $(objects) $(LFLAGS)


lerMapa.o: lerMapa.c defs.h
	gcc -c lerMapa.c $(CFLAGS)

isaaclib.o: isaaclib.c defs.h
	gcc -c isaaclib.c $(CFLAGS) 


clean:
	-rm $(objects)

purge: clean
	-rm isaacGame