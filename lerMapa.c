#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#define COL 160
#define LIN 50

void lerMapa(FILE **mapaMatriz, char *mapaArq){
	*mapaMatriz = fopen (mapaArq, "r") ;
	if(!mapaMatriz) {
		perror("Arquivo nao aberto: "); //saber se dicionario foi aberto
		exit(1);
	}
}

int main(int argc, char const *argv[])
{
	WINDOW *window;
	char **mapa;
	char *mapaArq = "map.h";
	FILE *mapaMatriz;

    initscr(); // initialize Ncurses

    window = newwin( LIN,COL ,2 , 2); // create a new window
	box( window, 0, 0 ); // sets default borders for the window

	lerMapa(&mapaMatriz,mapaArq);

	
	mapa = malloc(LIN * COL+1 * sizeof(char));
	for (int i = 0; i < LIN; ++i)
	{
		mapa[i] = malloc(COL+1 * sizeof(int));
	}



	char c;
	for (int i = 0; i < LIN; ++i)
	{
		for (int j = 0; j < COL+1; ++j)
		{
			c=getc(mapaMatriz);
			mapa[i][j] = c;
		}
	}


	for (int i = 0; i < LIN; ++i)
	{
		for (int j = 0; j < COL+1; ++j)
		{
			putc(mapa[i][j],stdout);
		}
	}




    delwin( window);
    endwin();




	return 0;
}