#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#define COLMAX 158+1
#define LINMAX 45
#define ALT_SCORE 3

void desenharBordas(WINDOW *janela) {
  box( janela, 0, 0 ); // desenha as bordas da janela indicada
}

char **lerMapa(char **mapa,char *mapaNome){ //matriz q vai guardar o mapa, nome do arquivo a ser lido
	char c;

	FILE *mapaArq = fopen(mapaNome,"r"); //abro o arquivo do mapa
	if (!mapaArq){
 		endwin(); //finaliza o ncurses para printar o erro
		perror("Arquivo nao aberto: "); //saber se arquivo foi aberto
		exit(1);
	}

	mapa = malloc (LINMAX * sizeof(int*)); // aloca espaço de memoria para a matriz do mapa
	for (int i = 0; i < LINMAX; ++i)
	{
		mapa[i] = malloc (COLMAX * sizeof(int));
	}

  	for (int i = 0; i < LINMAX; ++i)//le os caracteres do arquivo e grava na matriz
	{
		for (int j = 0; j < COLMAX; ++j)
		{
			c=getc(mapaArq);
			if (c=='\n')
			{
				c='\0';
			}
			mapa[i][j] = c;
		}
	}

	return(mapa);
}

void imprimeMapa(char **mapa, WINDOW *janela){
	int xAtual, yAtual;
	getmaxyx(stdscr, yAtual, xAtual); //pega o max x e y da janela atual no terminal
    for (int i = 0; i < LINMAX; ++i)
    {
    	if (xAtual < COLMAX+1){
		   if (yAtual < LINMAX +2){
				mvwprintw(janela, i+1, 1, "%s",mapa[i]);
		   }
		   else{
				mvwprintw(janela, (((yAtual-2)- LINMAX)/2)+i, 1, "%s",mapa[i]);
		   }
    	}
    	else{
    		if (xAtual < COLMAX+1)
    		{
			    mvwprintw(janela, i+1, (xAtual-(COLMAX-1))/2, "%s", mapa[i]);
    		}
    		else{
			    mvwprintw(janela,(((yAtual-2)- LINMAX)/2)+i, (xAtual-(COLMAX-1))/2, "%s", mapa[i]);

    		}
    	}
    }
}

void infoScore(WINDOW *janela){
	int xAtual, yAtual;
	getmaxyx(stdscr, yAtual, xAtual); 
	mvwprintw(janela, 1, 1, "Hearts:%d  Coins:00  Keys:00 | (x: %d y: %d)",05,xAtual,yAtual);
}

int main(int argc, char *argv[]) {
	/*#################################### INICIALIZAÇÕES AQUI ####################################*/
	int gameOver = 0; 
	int xAtual, yAtual, novoX, novoY; //cordenadas

	char *mapa1 = "map.h";
	char **mapa = NULL;
  
	initscr();
	noecho();
	curs_set(0);

	mapa = lerMapa(mapa,mapa1);

	getmaxyx(stdscr, yAtual, xAtual); //pega o max x e y da janela atual no terminal
	WINDOW *janelaScore = newwin(ALT_SCORE, xAtual, 0, 0); //altura,largura,posX,posY
	WINDOW *janelaJogo = newwin(yAtual - ALT_SCORE, xAtual, ALT_SCORE, 0);	


	/*#################################### IMPRESSÕES AQUI ####################################*/

	/*duas bordas*/
	desenharBordas(janelaScore);
	desenharBordas(janelaJogo);
    
	/*mapa mais score*/
    infoScore(janelaScore);
	imprimeMapa(mapa,janelaJogo);

  while(!gameOver){
    
    getmaxyx(stdscr, novoY, novoX);

    /*teste para ver se o terminal foi */
    if (novoY != yAtual || novoX != xAtual){
      xAtual = novoX;
      yAtual = novoY;

      wresize(janelaScore, ALT_SCORE, xAtual);
      wresize(janelaJogo, yAtual - ALT_SCORE, xAtual);
      mvwin(janelaJogo, yAtual + ALT_SCORE, 0);

      wclear(stdscr);
      wclear(janelaJogo);
      wclear(janelaScore);

      desenharBordas(janelaJogo);
      desenharBordas(janelaScore);
	  imprimeMapa(mapa,janelaJogo);
    }

    // infos score 
    infoScore(janelaScore);

    // mapa na tela
	imprimeMapa(mapa,janelaJogo);

    // atualiza janelas
    wrefresh(janelaScore);
    wrefresh(janelaJogo);
  }

  endwin();
  return 0;
}