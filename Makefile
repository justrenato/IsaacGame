all: lerMapa

lerMapa: lerMapa.c 
	gcc lerMapa.c -lncurses

clean:
	-rm *.o

purge: clean
	-rm a.out