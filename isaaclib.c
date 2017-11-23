#include "defs.h"

void desenharBordas(WINDOW *janela) {
  box( janela, 0, 0 ); // desenha as bordas da janela indicada
}

void teste_redimensao(int *xAtual, int *yAtual, WINDOW *janelaScore, WINDOW *janelaJogo, int xIsaac, int yIsaac, char **mapa, char **cores){
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
		imprimeMapa(mapa, cores, janelaJogo);
		imprimirIsaac(xIsaac,yIsaac,janelaJogo,mapa, cores);
	}
}

char **inicCores(char **cores){
	cores = malloc (LINMAX * sizeof(int*)); // aloca espaço de memoria para a matriz do mapa
	for (int i = 0; i < LINMAX; ++i)
	{
		cores[i] = malloc (COLMAX * sizeof(int));
	}	
	return cores;
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

void imprimeMapa(char **mapa, char **cores, WINDOW *janela){
	start_color();
    for (int i = 0; i < LINMAX; ++i)
    {
    	for (int j = 0; j < COLMAX; ++j)
    	{
    		if (cores[i][j]=='i')
    		{
				init_pair(1, COLOR_GREEN, COLOR_BLACK);
				wattron(janela,COLOR_PAIR(1));
				mvwprintw(janela, yMapa()+i, xMapa()+j, "%c",mapa[i][j]);
				wattroff(janela,COLOR_PAIR(1));
    		} else if (cores[i][j]=='a'){
				init_pair(2, COLOR_YELLOW, COLOR_BLACK);
				wattron(janela,COLOR_PAIR(2));
				mvwprintw(janela, yMapa()+i, xMapa()+j, "%c",mapa[i][j]);
				wattroff(janela,COLOR_PAIR(2));
    		}
    		else if(cores[i][j]=='g'){
				init_pair(3, COLOR_CYAN, COLOR_BLACK);
				wattron(janela,COLOR_PAIR(3));
				mvwprintw(janela, yMapa()+i, xMapa()+j, "%c",mapa[i][j]);
				wattroff(janela,COLOR_PAIR(3));
    		}
    		else if(cores[i][j]=='m'){
				init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
				wattron(janela,COLOR_PAIR(4));
				mvwprintw(janela, yMapa()+i, xMapa()+j, "%c",mapa[i][j]);
				wattroff(janela,COLOR_PAIR(4));
    		}
    		else if(cores[i][j]=='t'){
				init_pair(5, COLOR_BLUE, COLOR_BLACK);
				wattron(janela,COLOR_PAIR(5));
				mvwprintw(janela, yMapa()+i, xMapa()+j, "%c",mapa[i][j]);
				wattroff(janela,COLOR_PAIR(5));
    		}
    		else mvwprintw(janela, yMapa()+i, xMapa()+j, "%c",mapa[i][j]);
    	}
    }
}


void infoScore(WINDOW *janela, int yIsaac, int xIsaac){
	int xAtual, yAtual;
	getmaxyx(stdscr, yAtual, xAtual); 
	mvwprintw(janela, 1, 1, "Hearts:%d  Coins:00  Keys:00 | xmouse: %d ymouse: %d",55,xAtual,yAtual);
}

void imprimirIsaac(int x, int y, WINDOW *janela,char** mapa, char **cores){
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

	/*cabeça*/
	cores[y][x]='i';
	cores[y][x+1]='i';
	cores[y][x+2]='i';
	cores[y][x+3]='i';
	cores[y][x+4]='i';

	/*braços*/
	cores[y+1][x]='i';
	cores[y+1][x+1]='i';
	cores[y+1][x+2]='i';
	cores[y+1][x+3]='i';
	cores[y+1][x+4]='i';

	/*tronco*/
	cores[y+2][x+2]='i';

	/*pernas*/
	cores[y+3][x+1]='i';
	cores[y+3][x+2]='i';
	cores[y+3][x+3]='i';
}

void attJanelas(WINDOW *janelaJogo, WINDOW *janelaScore, int xIsaac,int yIsaac, char** mapa, char **cores){
    // atualiza janelas
    // infoScore(janelaScore, yIsaac, xIsaac);
	imprimeMapa(mapa, cores, janelaJogo);
	imprimirIsaac(xIsaac,yIsaac,janelaJogo,mapa, cores);
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

void tiro(WINDOW *janelaJogo, WINDOW *janelaScore, MEVENT *event,int xIsaac,int yIsaac, int *oldMouseX, int *oldMouseY,char** mapa, tiro_t tiros[], char**cores){
	int click=0;
	getmouse(event);
    int d;
    static int numtiros=0;

	if ((event->y != 0 ) && (event->x != 0)) //como o programa seta em 0 as cordenadas sempre que le outra tecla, quando posição for diferente de 0x0 eu salvo ela.
	{
		*oldMouseX = event->x - xMapa();
		*oldMouseY = event->y- yMapa()-3;
		click = event->bstate; //se click==2 botao esquerdo pressionado.
	}
	mvwprintw(janelaScore, 1, 1, "                                                                                                            ");
	mvwprintw(janelaScore, 1, 1, "ymouse: %03d xmouse: %03d | yIsaac: %03d xIsaac: %03d -- numtiros.y: %d ",*oldMouseY,*oldMouseX,yIsaac,xIsaac,tiros[numtiros].y);

	/*##############TESTANDO A POSIÇÂO DO MOUSE PARA DETERMINAR DIREÇÃO CASO SEJA ATIRADO*##############*/
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
/*################################################################################################*/
	
	if (click==2 && numtiros < 10) //se clickar e nao houverem 10 tiros ja
	{
		geraInimigo(janelaJogo, mapa,cores);
		beep();
		flash();

		tiros[numtiros].estado = 1; //mudo estado para 1 (tiro andando)
		switch(d){
			case 0:
				tiros[numtiros].y = yIsaac;
				tiros[numtiros].x = xIsaac+2;
			break;
			case 1:
				tiros[numtiros].y = yIsaac+2;
				tiros[numtiros].x = xIsaac+2;
			break;
			case 2:
				tiros[numtiros].y = yIsaac;
				tiros[numtiros].x = xIsaac;
			break;
			case 3:
				tiros[numtiros].y = yIsaac;
				tiros[numtiros].x = xIsaac+4;
			break;
			case 4:
				tiros[numtiros].y = yIsaac;
				tiros[numtiros].x = xIsaac+4;
			break;
			case 5:
				tiros[numtiros].y = yIsaac;
				tiros[numtiros].x = xIsaac+4;
			break;
			case 6:
				tiros[numtiros].y = yIsaac;
				tiros[numtiros].x = xIsaac;
			break;
			case 7:
				tiros[numtiros].y = yIsaac;
				tiros[numtiros].x = xIsaac;
			break;
		}

		tiros[numtiros].d = d; //atribui direção atual do mouse à direção do tiro
		numtiros++; // aumenta o contador de tiros
	
	}


	/*ATUALIZAR TIROS EXISTENTES */

	for (int i = 0; i < MAXTIROS; ++i)
	{
		if (tiros[i].estado) // se estado != 0 tiro existe e precisa ser atualizado
		{
			switch (tiros[i].estado){
				case 1: //tiro 'andando'
					switch(tiros[i].d){
						case 0: //cima
							if (mapa[tiros[i].y-1][tiros[i].x]==' ') //testando se o proximo lugar que ira imprimir o tiro é um espaço em branco, se nao for o tiro some.
							{
								mapa[tiros[i].y][tiros[i].x]=' ';
								(tiros[i].y) --;
								cores[tiros[i].y][tiros[i].x]='t';
								mapa[tiros[i].y][tiros[i].x]=TIRO;
							} 
							else { 
								tiros[i].estado = 2;
							}
						break;
						case 1: //baixo
							if (mapa[tiros[i].y+1][tiros[i].x]==' ') //testando se o proximo lugar que ira imprimir o tiro é um espaço em branco, se nao for o tiro some.
							{
								mapa[tiros[i].y][tiros[i].x]=' ';
								(tiros[i].y)++;
								cores[tiros[i].y][tiros[i].x]='t';
								mapa[tiros[i].y][tiros[i].x]=TIRO;
							}
							else{
								tiros[i].estado = 2;
							}
						break;
						case 2: //esq
							if (mapa[tiros[i].y][tiros[i].x-1]==' ') //testando se o proximo lugar que ira imprimir o tiro é um espaço em branco, se nao for o tiro some.
							{
								mapa[tiros[i].y][tiros[i].x]=' ';
								(tiros[i].x)--;
								cores[tiros[i].y][tiros[i].x]='t';
								mapa[tiros[i].y][tiros[i].x]=TIRO;
							}
							else{
								tiros[i].estado = 2;
							}
						break;
						case 3: //dir
							if (mapa[tiros[i].y][tiros[i].x+1]==' ') //testando se o proximo lugar que ira imprimir o tiro é um espaço em branco, se nao for o tiro some.
							{
								
								mapa[tiros[i].y][tiros[i].x]=' ';
								(tiros[i].x)++;
								cores[tiros[i].y][tiros[i].x]='t';
								mapa[tiros[i].y][tiros[i].x]=TIRO;
							}
							else{
								tiros[i].estado = 2;
							}
						break;
						case 4: //dir + cima
							if (mapa[tiros[i].y-1][tiros[i].x+1]==' ') //testando se o proximo lugar que ira imprimir o tiro é um espaço em branco, se nao for o tiro some.
							{
								mapa[tiros[i].y][tiros[i].x]=' ';
								(tiros[i].y)--;
								(tiros[i].x)++;
								cores[tiros[i].y][tiros[i].x]='t';
								mapa[tiros[i].y][tiros[i].x]=TIRO;
							}else{
								tiros[i].estado = 2;
							}
						break;
						case 5: //dir + baixo
							if (mapa[tiros[i].y+1][tiros[i].x+1]==' ') //testando se o proximo lugar que ira imprimir o tiro é um espaço em branco, se nao for o tiro some.
							{
								mapa[tiros[i].y][tiros[i].x]=' ';
								(tiros[i].y)++;
								(tiros[i].x)++;
								cores[tiros[i].y][tiros[i].x]='t';
								mapa[tiros[i].y][tiros[i].x]=TIRO;
							}else{
								tiros[i].estado = 2;
							}
						break;
						case 6: //esq + cima
							if (mapa[tiros[i].y-1][tiros[i].x-1]==' ') //testando se o proximo lugar que ira imprimir o tiro é um espaço em branco, se nao for o tiro some.
							{
								mapa[tiros[i].y][tiros[i].x]=' ';
								(tiros[i].y)--;
								(tiros[i].x)--;
								cores[tiros[i].y][tiros[i].x]='t';
								mapa[tiros[i].y][tiros[i].x]=TIRO;
							}else{
								tiros[i].estado = 2;
							}
						break;
						case 7: //esq + baixo
							if (mapa[tiros[i].y+1][tiros[i].x-1]==' ') //testando se o proximo lugar que ira imprimir o tiro é um espaço em branco, se nao for o tiro some.
							{
								mapa[tiros[i].y][tiros[i].x]=' ';
								(tiros[i].y)++;
								(tiros[i].x)--;
								cores[tiros[i].y][tiros[i].x]='t';
								mapa[tiros[i].y][tiros[i].x]=TIRO;
							}else{
								tiros[i].estado = 2;
							}
						break;
					}
				break;

				case 2:
					mapa[tiros[i].y][tiros[i].x]=' ';
					tiros[i].estado = 0;
					numtiros--;
				break;

				case 3:
					mapa[tiros[i].y][tiros[i].x]=' ';
				break;
			}
		}
	}
}

void inicInimigo(morcego_t morcegoVet[], gato_t gatoVet[], abelha_t abelhaVet[]){
	for (int i = 0; i < MAXINIMIGOS; ++i) //inicializa nas structs dos tres inimigos as variaveis
	{
		morcegoVet[i].vidas = 3;
		morcegoVet[i].cor = 'm';
		morcegoVet[i].corpo[0]='/';
		morcegoVet[i].corpo[1]='\\';
		morcegoVet[i].corpo[2]='/';
		morcegoVet[i].corpo[3]='\\';
		morcegoVet[i].corpo[4]='(';
		morcegoVet[i].corpo[5]='o';
		morcegoVet[i].corpo[6]='_';
		morcegoVet[i].corpo[7]='o';
		morcegoVet[i].corpo[8]=')';
		morcegoVet[i].corpo[9]='/';
		morcegoVet[i].corpo[10]='\\';
		morcegoVet[i].corpo[11]='/';
		morcegoVet[i].corpo[12]='\\';

		gatoVet[i].vidas = 3;
		gatoVet[i].cor = 'g';
		gatoVet[i].corpo[0][0]=' ';
		gatoVet[i].corpo[0][1]='/';
		gatoVet[i].corpo[0][2]='\\';
		gatoVet[i].corpo[0][3]='_';
		gatoVet[i].corpo[0][4]='/';
		gatoVet[i].corpo[0][5]='\\';	
		gatoVet[i].corpo[0][6]=' ';	

		gatoVet[i].corpo[1][0]='(';
		gatoVet[i].corpo[1][1]=' ';
		gatoVet[i].corpo[1][2]='o';
		gatoVet[i].corpo[1][3]='.';
		gatoVet[i].corpo[1][4]='o';				
		gatoVet[i].corpo[1][5]=' ';				
		gatoVet[i].corpo[1][6]=')';

		gatoVet[i].corpo[2][0]=' ';
		gatoVet[i].corpo[2][1]='>';
		gatoVet[i].corpo[2][2]=' ';
		gatoVet[i].corpo[2][3]='^';
		gatoVet[i].corpo[2][4]=' ';
		gatoVet[i].corpo[2][5]='<';	
		gatoVet[i].corpo[2][6]=' ';	


		abelhaVet[i].vidas = 3;
		abelhaVet[i].cor = 'a';

		abelhaVet[i].corpo[0][0]=' ';
		abelhaVet[i].corpo[0][1]=' ';
		abelhaVet[i].corpo[0][2]=' ';
		abelhaVet[i].corpo[0][3]='_';
		abelhaVet[i].corpo[0][4]='_';				
		abelhaVet[i].corpo[0][5]=' ';				
		abelhaVet[i].corpo[0][6]=' ';

		abelhaVet[i].corpo[1][0]=' ';
		abelhaVet[i].corpo[1][1]='_';
		abelhaVet[i].corpo[1][2]='/';
		abelhaVet[i].corpo[1][3]='_';
		abelhaVet[i].corpo[1][4]='_';				
		abelhaVet[i].corpo[1][5]=')';				
		abelhaVet[i].corpo[1][6]=' ';

		abelhaVet[i].corpo[2][0]='(';
		abelhaVet[i].corpo[2][1]='8';
		abelhaVet[i].corpo[2][2]='|';
		abelhaVet[i].corpo[2][3]=')';
		abelhaVet[i].corpo[2][4]='_';				
		abelhaVet[i].corpo[2][5]='}';				
		abelhaVet[i].corpo[2][6]='}';

		abelhaVet[i].corpo[3][0]=' ';
		abelhaVet[i].corpo[3][1]='`';
		abelhaVet[i].corpo[3][2]='\\';
		abelhaVet[i].corpo[3][3]='_';
		abelhaVet[i].corpo[3][4]='_';				
		abelhaVet[i].corpo[3][5]=')';				
		abelhaVet[i].corpo[3][6]=' ';
	}
}

void geraInimigo(WINDOW *janelaJogo, char** mapa, char** cores){
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

			/*COR*/
			cores[i][j+1]='m';
			cores[i][j+2]='m';
			cores[i][j+3]='m';
			cores[i][j+4]='m';
			cores[i][j+5]='m';
			cores[i][j+6]='m';
			cores[i][j+7]='m';
			cores[i][j+8]='m';
			cores[i][j+9]='m';
			cores[i][j+10]='m';
			cores[i][j+11]='m';
			cores[i][j+12]='m';
			cores[i][j+13]='m';
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

			/*COR*/
			cores[i][j+1]='g';
			cores[i][j+2]='g';
			cores[i][j+3]='g';
			cores[i][j+4]='g';
			cores[i][j+5]='g';	

			cores[i+1][j]='g';
			cores[i+1][j+1]='g';
			cores[i+1][j+2]='g';
			cores[i+1][j+3]='g';
			cores[i+1][j+4]='g';				
			cores[i+1][j+5]='g';				
			cores[i+1][j+6]='g';

			cores[i+2][j+1]='g';
			cores[i+2][j+2]='g';
			cores[i+2][j+3]='g';
			cores[i+2][j+4]='g';
			cores[i+2][j+5]='g';				
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

			/*COR*/
			cores[i][j]='a';
			cores[i][j+1]='a';
			cores[i][j+2]='a';
			cores[i][j+3]='a';
			cores[i][j+4]='a';				
			cores[i][j+5]='a';				
			cores[i][j+6]='a';

			cores[i+1][j]='a';
			cores[i+1][j+1]='a';
			cores[i+1][j+2]='a';
			cores[i+1][j+3]='a';
			cores[i+1][j+4]='a';				
			cores[i+1][j+5]='a';				
			cores[i+1][j+6]='a';

			cores[i+2][j]='a';
			cores[i+2][j+1]='a';
			cores[i+2][j+2]='a';
			cores[i+2][j+3]='a';
			cores[i+2][j+4]='a';				
			cores[i+2][j+5]='a';				
			cores[i+2][j+6]='a';

			cores[i+3][j]='a';
			cores[i+3][j+1]='a';
			cores[i+3][j+2]='a';
			cores[i+3][j+3]='a';
			cores[i+3][j+4]='a';				
			cores[i+3][j+5]='a';				
			cores[i+3][j+6]='a';

		break;
	}
}

