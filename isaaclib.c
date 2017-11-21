#include "defs.h"

void desenharBordas(WINDOW *janela) {
  box( janela, 0, 0 ); // desenha as bordas da janela indicada
}

void teste_redimensao(int *xAtual, int *yAtual, WINDOW *janelaScore, WINDOW *janelaJogo, int xIsaac, int yIsaac, char **mapa){
	int novoX, novoY;
    getmaxyx(stdscr, novoY, novoX);
    /*teste para ver se o terminal foi redimensionado */
	if (novoY != *yAtual || novoX != *xAtual){
		*xAtual = novoX;
		*yAtual = novoY;

		wresize(janelaScore, ALT_SCORE, *xAtual);
		wresize(janelaJogo, *yAtual - ALT_SCORE, *xAtual);
		mvwin(janelaJogo, *yAtual + ALT_SCORE, 0);

		wclear(stdscr);
		wclear(janelaJogo);
		wclear(janelaScore);

		desenharBordas(janelaJogo);
		desenharBordas(janelaScore);
		infoScore(janelaScore, yIsaac, xIsaac);
		imprimeMapa(mapa,janelaJogo);
		imprimirIsaac(xIsaac,yIsaac,janelaJogo,mapa);
	}
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

int yMapa(){
	int yAtual,y;
	yAtual = getmaxy(stdscr); //pega o max x e y da janela atual no terminal
	if (yAtual < LINMAX +2){
		y=1;
	}
	else{
		y=(((yAtual-2)- LINMAX)/2);
	}
	return y;
}

int xMapa(){
	int xAtual,x;
	xAtual = getmaxx(stdscr); //pega o max x e y da janela atual no terminal
	if(xAtual<COLMAX+1){
		x=1;
	}
	else {
		x = (xAtual-(COLMAX-1))/2;
	}
	return x;
}

void imprimeMapa(char **mapa, WINDOW *janela){
	start_color();
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
    for (int i = 0; i < LINMAX; ++i)
    {
    	for (int j = 0; j < COLMAX; ++j)
    	{
    		if (mapa[i][j]==TIRO)
    		{
				wattron(janela,COLOR_PAIR(1));
				mvwprintw(janela, yMapa()+i, xMapa()+j, "%c",mapa[i][j]);
				wattroff(janela,COLOR_PAIR(1));
    		}else mvwprintw(janela, yMapa()+i, xMapa()+j, "%c",mapa[i][j]);
    	}
    }
}


void infoScore(WINDOW *janela, int yIsaac, int xIsaac){
	int xAtual, yAtual;
	getmaxyx(stdscr, yAtual, xAtual); 
	mvwprintw(janela, 1, 1, "Hearts:%d  Coins:00  Keys:00 | xmouse: %d ymouse: %d",55,xAtual,yAtual);
}

void imprimirIsaac(int x, int y, WINDOW *janela,char** mapa){
	/*cabeça*/
	mapa[y][x]='(';
	mapa[y][x+1]=';';
	mapa[y][x+2]='_';
	mapa[y][x+3]=';';
	mapa[y][x+4]=')';

	/*braços*/
	mapa[y+1][x]='_';
	mapa[y+1][x+1]='_';
	mapa[y+1][x+2]='|';
	mapa[y+1][x+3]='_';
	mapa[y+1][x+4]='_';

	/*tronco*/
	mapa[y+2][x+2]='|';

	/*pernas*/
	mapa[y+3][x+1]='/';
	mapa[y+3][x+2]=' ';
	mapa[y+3][x+3]='\\';
}

void attJanelas(WINDOW *janelaJogo, WINDOW *janelaScore, int xIsaac,int yIsaac, char** mapa){
    // atualiza janelas
    // infoScore(janelaScore, yIsaac, xIsaac);
	imprimeMapa(mapa,janelaJogo);
	imprimirIsaac(xIsaac,yIsaac,janelaJogo,mapa);
    wrefresh(janelaScore);
    wrefresh(janelaJogo);
}

void apagarIsaac(int x, int y, WINDOW *janela,char** mapa){

	/*cabeça*/
	mapa[y][x]=' ';
	mapa[y][x+1]=' ';
	mapa[y][x+2]=' ';
	mapa[y][x+3]=' ';
	mapa[y][x+4]=' ';

	/*braços*/
	mapa[y+1][x]=' ';
	mapa[y+1][x+1]=' ';
	mapa[y+1][x+2]=' ';
	mapa[y+1][x+3]=' ';
	mapa[y+1][x+4]=' ';

	/*tronco*/
	mapa[y+2][x+2]=' ';

	/*pernas*/
	mapa[y+3][x+1]=' ';
	mapa[y+3][x+2]=' ';
	mapa[y+3][x+3]=' ';
}

void movimentacao(WINDOW *janelaJogo, WINDOW*janelaScore, int *xIsaac,int *yIsaac, char** mapa){
	int ch;
    ch = wgetch(janelaJogo);

    switch( ch ) {
	    case 'd':
	    		if (mapa[*yIsaac][*xIsaac+5]==' ')
	    		{
    				apagarIsaac(*xIsaac,*yIsaac,janelaJogo,mapa);
	    			(*xIsaac)++;
	    		}
        break;
	    case 'a':
	    		if (mapa[*yIsaac][*xIsaac-1]==' ')
	    		{
	    			apagarIsaac(*xIsaac,*yIsaac,janelaJogo,mapa);
		    		(*xIsaac)--;
	    		}
        break;
	    case 's':
	    		if (mapa[*yIsaac+4][*xIsaac]==' ')
	    		{
    				apagarIsaac(*xIsaac,*yIsaac,janelaJogo,mapa);
		    		(*yIsaac)++;
	    		}
        break;
	    case 'w':
	    		if (mapa[*yIsaac-1][*xIsaac]==' ')
	    		{
    				apagarIsaac(*xIsaac,*yIsaac,janelaJogo,mapa);
	    			(*yIsaac)--;
	    		}
        break;
   	}
}

void tiro(WINDOW *janelaJogo, WINDOW *janelaScore, MEVENT *event,int xIsaac,int yIsaac, int *oldMouseX, int *oldMouseY,char** mapa, tiro_t tiros[]){
	int click=0;
	getmouse(event);
    int d=0;
    static int numtiros=0;

	if ((event->y != 0 ) && (event->x != 0)) //como o programa seta em 0 as cordenadas sempre que le outra tecla, quando posição for diferente de 0x0 eu salvo ela.
	{
		*oldMouseX = event->x - xMapa();
		*oldMouseY = event->y- yMapa()-3;
		click = event->bstate; //se click==2 botao esquerdo pressionado.
	}
	mvwprintw(janelaScore, 1, 1, "                                                                                                            ");
	// mvwprintw(janelaScore, 1, 1, "ymouse: %03d xmouse: %03d | yIsaac: %03d xIsaac: %03d -- numtiros.y: %d ",*oldMouseY,*oldMouseX,yIsaac,xIsaac,tiros[numtiros].y);

	if ((*oldMouseY <= yIsaac ) && (*oldMouseX >= xIsaac - 20) && (*oldMouseX <= xIsaac+20))
	{
		d=0;
	}

	if ((*oldMouseY >= yIsaac ) && (*oldMouseX >= xIsaac - 20) && (*oldMouseX <= xIsaac+20))
	{
		d=1;
	}

	if ((*oldMouseY >= yIsaac -10 ) && (*oldMouseY <= yIsaac + 10) && (*oldMouseX <= xIsaac))
	{
		d=2;
	}
	
	if ((*oldMouseY >= yIsaac -10 ) && (*oldMouseY <= yIsaac + 10) && (*oldMouseX >= xIsaac))
	{
		d=3;
	}

	if((*oldMouseY <= yIsaac - 10) && (*oldMouseX >= xIsaac + 20)){
		d=4;
	}

	if ((*oldMouseY >= yIsaac + 10) && (*oldMouseX >= xIsaac + 20))
	{
		d=5;
	}

	if ((*oldMouseY <= yIsaac - 10) &&  (*oldMouseX <= xIsaac -20))
	{
		d=6;
	}


	if ((*oldMouseY >= yIsaac + 10) && (*oldMouseX <= xIsaac - 20))
	{
		d=7;
	}

	
	if (click==2 && numtiros < 10)
	{
		geraInimigo(janelaJogo, mapa);
		beep();
		flash();

		tiros[numtiros].y = yIsaac;
		tiros[numtiros].x = xIsaac-1;
		tiros[numtiros].d = d;
		numtiros++;
	
	}
		mvwprintw(janelaScore, 1, 1, " numtiros.y: %d yIsaac:%d",tiros[0].y,yIsaac);

/*ATUALIZAR TIROS EXISTENTES */

	for (int i = 0; i < MAXTIROS; ++i)
	{
		if (tiros[i].estado) // se estado != 0 tiro existe e precisa ser atualizado
		{
			switch(tiros[i].d){
				case 0:
					mapa[tiros[i].y][tiros[i].x]=' ';
					(tiros[i].y) --;
					mapa[tiros[i].y][tiros[i].x]=TIRO;
					attJanelas(janelaJogo, janelaScore, xIsaac, yIsaac,mapa);
					usleep(DELAY);
				break;
			// 	case 1:
			// 		mapa[y+1][j+1]=' ';
			// 		y++;
			// 		mapa[y+1][j+1]=TIRO;
			// 		attJanelas(janelaJogo, janelaScore, xIsaac, yIsaac,mapa);
			// 		usleep(DELAY);
			// 	break;
			// 	case 2:
			// 		mapa[y][j-1]=' ';
			// 		(j)--;
			// 		mapa[y][j-1]=TIRO;
			// 		attJanelas(janelaJogo, janelaScore, xIsaac, yIsaac,mapa);
			// 		usleep(DELAY);			
			// 	break;
			// 	case 3:
			// 		mapa[y][j+5]=' ';
			// 		(j)++;
			// 		mapa[y][j+5]=TIRO;
			// 		attJanelas(janelaJogo, janelaScore, xIsaac, yIsaac,mapa);
			// 		usleep(DELAY);
			// 	break;
			// 	case 4:
			// 		mapa[y][j+5]=' ';
			// 		y--;
			// 		j++;
			// 		mapa[y][j+5]=TIRO;
			// 		attJanelas(janelaJogo, janelaScore, xIsaac, yIsaac,mapa);
			// 		usleep(DELAY);
			// 	break;
			// 	case 5:
			// 		mapa[y][j+5]=' ';
			// 		y++;
			// 		j++;
			// 		mapa[y][j+5]=TIRO;
			// 		attJanelas(janelaJogo, janelaScore, xIsaac, yIsaac,mapa);
			// 		usleep(DELAY);
			// 	break;
			// 	case 6:
			// 		mapa[y][j-1]=' ';
			// 		y--;
			// 		j--;
			// 		mapa[y][j-1]=TIRO;
			// 		attJanelas(janelaJogo, janelaScore, xIsaac, yIsaac,mapa);
			// 		usleep(DELAY);
			// 	break;
			// 	case 7:
			// 		mapa[y][j-1]=' ';
			// 		y++;
			// 		j--;
			// 		mapa[y][j-1]=TIRO;
			// 		attJanelas(janelaJogo, janelaScore, xIsaac, yIsaac,mapa);
			// 		usleep(DELAY);
			// 	break;
			}
		}
	}


 
}

void geraInimigo(WINDOW *janelaJogo, char** mapa){
	int i=0,j=0,inimigo=0;
	i = (rand()% (LINMAX -4 -yMapa()))+1;
	j = (rand()% (COLMAX - xMapa()))+1;
	inimigo = rand()% 3;
	
	switch (inimigo) 
	{
		case 0://morceguineo
			mapa[i][j+1]='/';
			mapa[i][j+2]='\\';
			mapa[i][j+3]='/';
			mapa[i][j+4]='\\';
			mapa[i][j+5]='(';
			mapa[i][j+6]='o';
			mapa[i][j+7]='_';
			mapa[i][j+8]='o';
			mapa[i][j+9]=')';
			mapa[i][j+10]='/';
			mapa[i][j+11]='\\';
			mapa[i][j+12]='/';
			mapa[i][j+13]='\\';
		break;
		case 1://gatineo
			mapa[i][j+1]='/';
			mapa[i][j+2]='\\';
			mapa[i][j+3]='_';
			mapa[i][j+4]='/';
			mapa[i][j+5]='\\';	

			mapa[i+1][j]='(';
			mapa[i+1][j+1]=' ';
			mapa[i+1][j+2]='o';
			mapa[i+1][j+3]='.';
			mapa[i+1][j+4]='o';				
			mapa[i+1][j+5]=' ';				
			mapa[i+1][j+6]=')';

			mapa[i+2][j+1]='>';
			mapa[i+2][j+2]=' ';
			mapa[i+2][j+3]='^';
			mapa[i+2][j+4]=' ';
			mapa[i+2][j+5]='<';				
		break;
		case 2://abelinea
			mapa[i][j]=' ';
			mapa[i][j+1]=' ';
			mapa[i][j+2]=' ';
			mapa[i][j+3]='_';
			mapa[i][j+4]='_';				
			mapa[i][j+5]=' ';				
			mapa[i][j+6]=' ';

			mapa[i+1][j]=' ';
			mapa[i+1][j+1]='_';
			mapa[i+1][j+2]='/';
			mapa[i+1][j+3]='_';
			mapa[i+1][j+4]='_';				
			mapa[i+1][j+5]=')';				
			mapa[i+1][j+6]=' ';

			mapa[i+2][j]='(';
			mapa[i+2][j+1]='8';
			mapa[i+2][j+2]='|';
			mapa[i+2][j+3]=')';
			mapa[i+2][j+4]='_';				
			mapa[i+2][j+5]='}';				
			mapa[i+2][j+6]='}';

			mapa[i+3][j]=' ';
			mapa[i+3][j+1]='`';
			mapa[i+3][j+2]='\\';
			mapa[i+3][j+3]='_';
			mapa[i+3][j+4]='_';				
			mapa[i+3][j+5]=')';				
			mapa[i+3][j+6]=' ';

		break;
	}
}

