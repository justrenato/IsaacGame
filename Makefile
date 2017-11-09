all: lerMapa

lerMapa: lerMapa.c 
	gcc lerMapa.c -Wall -lncurses -g

clean:
	-rm *.o

purge: clean
	-rm a.out