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
	// mvwprintw(janelaScore, 1, 50, "                                                                                                            ");
	mvwprintw(janelaScore, 1, 80, "ymouse: %03d xmouse: %03d | yIsaac: %03d xIsaac: %03d -- numtiros.y: %d ",*oldMouseY,*oldMouseX,yIsaac,xIsaac,tiros[numtiros].y);

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

void inicInimigo(WINDOW *janelaScore,morcego_t morcegoVet[], gato_t gatoVet[], abelha_t abelhaVet[]){
	int tipoInimigo=0;
	int numMorcegos=0,numGatos=0,numAbelhas=0;
	int numInimigos=0;

	// int xizes[MAXINIMIGOS*3];
	// int yipsolons[MAXINIMIGOS*3];
	// int n=0;

	for (int i = 0; i < MAXINIMIGOS; ++i) //inicializa nas structs dos tres inimigos as variaveis
	{

		int yM = (rand()% (LINMAX -4 -yMapa()))+1;
		int xM = (rand()% (COLMAX - xMapa()))+1;

		morcegoVet[i].yOld = yM;
		morcegoVet[i].xOld = xM;

		morcegoVet[i].yNew = yM;
		morcegoVet[i].xNew = xM;

		morcegoVet[i].vidas = 1;
		morcegoVet[i].estado = 0;
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
	}

	for (int i = 0; i < MAXINIMIGOS; ++i)
	{
		int yG = (rand()% (LINMAX -4 -yMapa()))+1;
		int xG = (rand()% (COLMAX - xMapa()))+1;
		gatoVet[i].yOld = yG;
		gatoVet[i].xOld = xG;

		gatoVet[i].yNew = yG;
		gatoVet[i].xNew = xG;

		gatoVet[i].vidas = 3;
		gatoVet[i].estado = 0;
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
	}

	for (int i = 0; i < MAXINIMIGOS; ++i)
	{
		int yA = (rand()% (LINMAX -4 -yMapa()))+1;
		int xA = (rand()% (COLMAX - xMapa()))+1;
		abelhaVet[i].yOld = yA;
		abelhaVet[i].xOld = xA;

		abelhaVet[i].yNew = yA;
		abelhaVet[i].xNew = xA;

		abelhaVet[i].vidas = 2;
		abelhaVet[i].estado = 0;
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

	while (numInimigos<TOTALINIMIGOS) //sorteia MAXINIMIGOS*2 inimigos para serem iniciados
	{
		tipoInimigo = rand()% 3;
		
		switch(tipoInimigo){
			case 0:
				//morcego
				if (numMorcegos<MAXINIMIGOS)
				{
					morcegoVet[numMorcegos].estado=1;
					numMorcegos++;
					numInimigos++;
				}
			break;
			case 1:
				//gato
				if (numGatos<MAXINIMIGOS)
				{
					gatoVet[numMorcegos].estado=1;
					numGatos++;
					numInimigos++;
				}
			break;
			case 2:
				//abelha
				if (numAbelhas<MAXINIMIGOS)
				{
					abelhaVet[numMorcegos].estado=1;
					numAbelhas++;
					numInimigos++;
				}
			break;
		}
	}
	
	mvwprintw(janelaScore,1,1,"numAbelhas:%d ab1: y%d x%d, ab2: y%d x%d, ab3: y%d x%d",numAbelhas, abelhaVet[0].yOld, abelhaVet[0].xOld,abelhaVet[1].yOld, abelhaVet[1].xOld,abelhaVet[2].yOld, abelhaVet[2].xOld);
}

void geraInimigo(WINDOW *janelaJogo, char** mapa, char** cores, morcego_t morcegoVet[], gato_t gatoVet[], abelha_t abelhaVet[]){
	int rand1 =0;
	for (int i = 0; i < MAXINIMIGOS; ++i)
	{

		if (morcegoVet[i].estado)
		{
			mapa[morcegoVet[i].yOld][morcegoVet[i].xOld+1]=' ';
			mapa[morcegoVet[i].yOld][morcegoVet[i].xOld+2]=' ';
			mapa[morcegoVet[i].yOld][morcegoVet[i].xOld+3]=' ';
			mapa[morcegoVet[i].yOld][morcegoVet[i].xOld+4]=' ';
			mapa[morcegoVet[i].yOld][morcegoVet[i].xOld+5]=' ';
			mapa[morcegoVet[i].yOld][morcegoVet[i].xOld+6]=' ';
			mapa[morcegoVet[i].yOld][morcegoVet[i].xOld+7]=' ';
			mapa[morcegoVet[i].yOld][morcegoVet[i].xOld+8]=' ';
			mapa[morcegoVet[i].yOld][morcegoVet[i].xOld+9]=' ';
			mapa[morcegoVet[i].yOld][morcegoVet[i].xOld+10]=' ';
			mapa[morcegoVet[i].yOld][morcegoVet[i].xOld+11]=' ';
			mapa[morcegoVet[i].yOld][morcegoVet[i].xOld+12]=' ';
			mapa[morcegoVet[i].yOld][morcegoVet[i].xOld+13]=' ';


			morcegoVet[i].xOld=morcegoVet[i].xNew;
			morcegoVet[i].yOld=morcegoVet[i].yNew;

			mapa[morcegoVet[i].yNew][morcegoVet[i].xNew+1]=morcegoVet[i].corpo[0];
			mapa[morcegoVet[i].yNew][morcegoVet[i].xNew+2]=morcegoVet[i].corpo[1];
			mapa[morcegoVet[i].yNew][morcegoVet[i].xNew+3]=morcegoVet[i].corpo[2];
			mapa[morcegoVet[i].yNew][morcegoVet[i].xNew+4]=morcegoVet[i].corpo[3];
			mapa[morcegoVet[i].yNew][morcegoVet[i].xNew+5]=morcegoVet[i].corpo[4];
			mapa[morcegoVet[i].yNew][morcegoVet[i].xNew+6]=morcegoVet[i].corpo[5];
			mapa[morcegoVet[i].yNew][morcegoVet[i].xNew+7]=morcegoVet[i].corpo[6];
			mapa[morcegoVet[i].yNew][morcegoVet[i].xNew+8]=morcegoVet[i].corpo[7];
			mapa[morcegoVet[i].yNew][morcegoVet[i].xNew+9]=morcegoVet[i].corpo[8];
			mapa[morcegoVet[i].yNew][morcegoVet[i].xNew+10]=morcegoVet[i].corpo[9];
			mapa[morcegoVet[i].yNew][morcegoVet[i].xNew+11]=morcegoVet[i].corpo[10];
			mapa[morcegoVet[i].yNew][morcegoVet[i].xNew+12]=morcegoVet[i].corpo[11];
			mapa[morcegoVet[i].yNew][morcegoVet[i].xNew+13]=morcegoVet[i].corpo[12];	

			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+1]=morcegoVet[i].cor;
			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+2]=morcegoVet[i].cor;
			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+3]=morcegoVet[i].cor;
			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+4]=morcegoVet[i].cor;
			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+5]=morcegoVet[i].cor;
			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+6]=morcegoVet[i].cor;
			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+7]=morcegoVet[i].cor;
			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+8]=morcegoVet[i].cor;
			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+9]=morcegoVet[i].cor;
			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+10]=morcegoVet[i].cor;
			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+11]=morcegoVet[i].cor;
			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+12]=morcegoVet[i].cor;
			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+13]=morcegoVet[i].cor;			
		}

		if (gatoVet[i].estado)
		{
			mapa[gatoVet[i].yOld][gatoVet[i].xOld]=' ';
			mapa[gatoVet[i].yOld][gatoVet[i].xOld+1]=' ';
			mapa[gatoVet[i].yOld][gatoVet[i].xOld+2]=' ';
			mapa[gatoVet[i].yOld][gatoVet[i].xOld+3]=' ';
			mapa[gatoVet[i].yOld][gatoVet[i].xOld+4]=' ';
			mapa[gatoVet[i].yOld][gatoVet[i].xOld+5]=' ';
			mapa[gatoVet[i].yOld][gatoVet[i].xOld+6]=' ';

			mapa[gatoVet[i].yOld+1][gatoVet[i].xOld]=' ';
			mapa[gatoVet[i].yOld+1][gatoVet[i].xOld+1]=' ';
			mapa[gatoVet[i].yOld+1][gatoVet[i].xOld+2]=' ';
			mapa[gatoVet[i].yOld+1][gatoVet[i].xOld+3]=' ';
			mapa[gatoVet[i].yOld+1][gatoVet[i].xOld+4]=' ';
			mapa[gatoVet[i].yOld+1][gatoVet[i].xOld+5]=' ';
			mapa[gatoVet[i].yOld+1][gatoVet[i].xOld+6]=' ';

			mapa[gatoVet[i].yOld+2][gatoVet[i].xOld]=' ';
			mapa[gatoVet[i].yOld+2][gatoVet[i].xOld+1]=' ';
			mapa[gatoVet[i].yOld+2][gatoVet[i].xOld+2]=' ';
			mapa[gatoVet[i].yOld+2][gatoVet[i].xOld+3]=' ';
			mapa[gatoVet[i].yOld+2][gatoVet[i].xOld+4]=' ';
			mapa[gatoVet[i].yOld+2][gatoVet[i].xOld+5]=' ';
			mapa[gatoVet[i].yOld+2][gatoVet[i].xOld+6]=' ';


			gatoVet[i].xOld=gatoVet[i].xNew;
			gatoVet[i].yOld=gatoVet[i].yNew;


			mapa[gatoVet[i].yOld][gatoVet[i].xOld]= gatoVet[i].corpo[0][0];
			mapa[gatoVet[i].yOld][gatoVet[i].xOld+1]= gatoVet[i].corpo[0][1];
			mapa[gatoVet[i].yOld][gatoVet[i].xOld+2]= gatoVet[i].corpo[0][2];
			mapa[gatoVet[i].yOld][gatoVet[i].xOld+3]= gatoVet[i].corpo[0][3];
			mapa[gatoVet[i].yOld][gatoVet[i].xOld+4]= gatoVet[i].corpo[0][4];
			mapa[gatoVet[i].yOld][gatoVet[i].xOld+5]= gatoVet[i].corpo[0][5];
			mapa[gatoVet[i].yOld][gatoVet[i].xOld+6]= gatoVet[i].corpo[0][6];

			mapa[gatoVet[i].yOld+1][gatoVet[i].xOld]= gatoVet[i].corpo[1][0];
			mapa[gatoVet[i].yOld+1][gatoVet[i].xOld+1]= gatoVet[i].corpo[1][1];
			mapa[gatoVet[i].yOld+1][gatoVet[i].xOld+2]= gatoVet[i].corpo[1][2];
			mapa[gatoVet[i].yOld+1][gatoVet[i].xOld+3]= gatoVet[i].corpo[1][3];
			mapa[gatoVet[i].yOld+1][gatoVet[i].xOld+4]= gatoVet[i].corpo[1][4];				
			mapa[gatoVet[i].yOld+1][gatoVet[i].xOld+5]= gatoVet[i].corpo[1][5];
			mapa[gatoVet[i].yOld+1][gatoVet[i].xOld+6]= gatoVet[i].corpo[1][6];

			mapa[gatoVet[i].yOld+2][gatoVet[i].xOld]= gatoVet[i].corpo[2][0];
			mapa[gatoVet[i].yOld+2][gatoVet[i].xOld+1]= gatoVet[i].corpo[2][1];
			mapa[gatoVet[i].yOld+2][gatoVet[i].xOld+2]= gatoVet[i].corpo[2][2];
			mapa[gatoVet[i].yOld+2][gatoVet[i].xOld+3]= gatoVet[i].corpo[2][3];
			mapa[gatoVet[i].yOld+2][gatoVet[i].xOld+4]= gatoVet[i].corpo[2][4];
			mapa[gatoVet[i].yOld+2][gatoVet[i].xOld+5]= gatoVet[i].corpo[2][5];
			mapa[gatoVet[i].yOld+2][gatoVet[i].xOld+6]= gatoVet[i].corpo[2][6];



			cores[gatoVet[i].yOld][gatoVet[i].xOld]= gatoVet[i].cor;
			cores[gatoVet[i].yOld][gatoVet[i].xOld+1]= gatoVet[i].cor;
			cores[gatoVet[i].yOld][gatoVet[i].xOld+2]= gatoVet[i].cor;
			cores[gatoVet[i].yOld][gatoVet[i].xOld+3]= gatoVet[i].cor;
			cores[gatoVet[i].yOld][gatoVet[i].xOld+4]= gatoVet[i].cor;
			cores[gatoVet[i].yOld][gatoVet[i].xOld+5]= gatoVet[i].cor;
			cores[gatoVet[i].yOld][gatoVet[i].xOld+6]= gatoVet[i].cor;

			cores[gatoVet[i].yOld+1][gatoVet[i].xOld]= gatoVet[i].cor;
			cores[gatoVet[i].yOld+1][gatoVet[i].xOld+1]= gatoVet[i].cor;
			cores[gatoVet[i].yOld+1][gatoVet[i].xOld+2]= gatoVet[i].cor;
			cores[gatoVet[i].yOld+1][gatoVet[i].xOld+3]= gatoVet[i].cor;
			cores[gatoVet[i].yOld+1][gatoVet[i].xOld+4]= gatoVet[i].cor;
			cores[gatoVet[i].yOld+1][gatoVet[i].xOld+5]= gatoVet[i].cor;
			cores[gatoVet[i].yOld+1][gatoVet[i].xOld+6]= gatoVet[i].cor;

			cores[gatoVet[i].yOld+2][gatoVet[i].xOld]= gatoVet[i].cor;
			cores[gatoVet[i].yOld+2][gatoVet[i].xOld+1]= gatoVet[i].cor;
			cores[gatoVet[i].yOld+2][gatoVet[i].xOld+2]= gatoVet[i].cor;
			cores[gatoVet[i].yOld+2][gatoVet[i].xOld+3]= gatoVet[i].cor;
			cores[gatoVet[i].yOld+2][gatoVet[i].xOld+4]= gatoVet[i].cor;
			cores[gatoVet[i].yOld+2][gatoVet[i].xOld+5]= gatoVet[i].cor;
			cores[gatoVet[i].yOld+2][gatoVet[i].xOld+6]= gatoVet[i].cor;
		}

		if (abelhaVet[i].estado)
		{
			mapa[abelhaVet[i].yOld][abelhaVet[i].xOld]=' ';
			mapa[abelhaVet[i].yOld][abelhaVet[i].xOld+1]=' ';
			mapa[abelhaVet[i].yOld][abelhaVet[i].xOld+2]=' ';
			mapa[abelhaVet[i].yOld][abelhaVet[i].xOld+3]=' ';
			mapa[abelhaVet[i].yOld][abelhaVet[i].xOld+4]=' ';
			mapa[abelhaVet[i].yOld][abelhaVet[i].xOld+5]=' ';
			mapa[abelhaVet[i].yOld][abelhaVet[i].xOld+6]=' ';

			mapa[abelhaVet[i].yOld+1][abelhaVet[i].xOld]=' ';
			mapa[abelhaVet[i].yOld+1][abelhaVet[i].xOld+1]=' ';
			mapa[abelhaVet[i].yOld+1][abelhaVet[i].xOld+2]=' ';
			mapa[abelhaVet[i].yOld+1][abelhaVet[i].xOld+3]=' ';
			mapa[abelhaVet[i].yOld+1][abelhaVet[i].xOld+4]=' ';
			mapa[abelhaVet[i].yOld+1][abelhaVet[i].xOld+5]=' ';
			mapa[abelhaVet[i].yOld+1][abelhaVet[i].xOld+6]=' ';

			mapa[abelhaVet[i].yOld+2][abelhaVet[i].xOld]=' ';
			mapa[abelhaVet[i].yOld+2][abelhaVet[i].xOld+1]=' ';
			mapa[abelhaVet[i].yOld+2][abelhaVet[i].xOld+2]=' ';
			mapa[abelhaVet[i].yOld+2][abelhaVet[i].xOld+3]=' ';
			mapa[abelhaVet[i].yOld+2][abelhaVet[i].xOld+4]=' ';
			mapa[abelhaVet[i].yOld+2][abelhaVet[i].xOld+5]=' ';
			mapa[abelhaVet[i].yOld+2][abelhaVet[i].xOld+6]=' ';

			mapa[abelhaVet[i].yOld+3][abelhaVet[i].xOld]=' ';
			mapa[abelhaVet[i].yOld+3][abelhaVet[i].xOld+1]=' ';
			mapa[abelhaVet[i].yOld+3][abelhaVet[i].xOld+2]=' ';
			mapa[abelhaVet[i].yOld+3][abelhaVet[i].xOld+3]=' ';
			mapa[abelhaVet[i].yOld+3][abelhaVet[i].xOld+4]=' ';
			mapa[abelhaVet[i].yOld+3][abelhaVet[i].xOld+5]=' ';
			mapa[abelhaVet[i].yOld+3][abelhaVet[i].xOld+6]=' ';



			abelhaVet[i].xOld=abelhaVet[i].xNew;
			abelhaVet[i].yOld=abelhaVet[i].yNew;


			mapa[abelhaVet[i].yOld][abelhaVet[i].xOld]=abelhaVet[i].corpo[0][0];
			mapa[abelhaVet[i].yOld][abelhaVet[i].xOld+1]=abelhaVet[i].corpo[0][1];
			mapa[abelhaVet[i].yOld][abelhaVet[i].xOld+2]=abelhaVet[i].corpo[0][2];
			mapa[abelhaVet[i].yOld][abelhaVet[i].xOld+3]=abelhaVet[i].corpo[0][3];
			mapa[abelhaVet[i].yOld][abelhaVet[i].xOld+4]=abelhaVet[i].corpo[0][4];
			mapa[abelhaVet[i].yOld][abelhaVet[i].xOld+5]=abelhaVet[i].corpo[0][5];
			mapa[abelhaVet[i].yOld][abelhaVet[i].xOld+6]=abelhaVet[i].corpo[0][6];

			mapa[abelhaVet[i].yOld+1][abelhaVet[i].xOld]=abelhaVet[i].corpo[1][0];
			mapa[abelhaVet[i].yOld+1][abelhaVet[i].xOld+1]=abelhaVet[i].corpo[1][1];
			mapa[abelhaVet[i].yOld+1][abelhaVet[i].xOld+2]=abelhaVet[i].corpo[1][2];
			mapa[abelhaVet[i].yOld+1][abelhaVet[i].xOld+3]=abelhaVet[i].corpo[1][3];
			mapa[abelhaVet[i].yOld+1][abelhaVet[i].xOld+4]=abelhaVet[i].corpo[1][4];
			mapa[abelhaVet[i].yOld+1][abelhaVet[i].xOld+5]=abelhaVet[i].corpo[1][5];
			mapa[abelhaVet[i].yOld+1][abelhaVet[i].xOld+6]=abelhaVet[i].corpo[1][6];

			mapa[abelhaVet[i].yOld+2][abelhaVet[i].xOld]=abelhaVet[i].corpo[2][0];
			mapa[abelhaVet[i].yOld+2][abelhaVet[i].xOld+1]=abelhaVet[i].corpo[2][1];
			mapa[abelhaVet[i].yOld+2][abelhaVet[i].xOld+2]=abelhaVet[i].corpo[2][2];
			mapa[abelhaVet[i].yOld+2][abelhaVet[i].xOld+3]=abelhaVet[i].corpo[2][3];
			mapa[abelhaVet[i].yOld+2][abelhaVet[i].xOld+4]=abelhaVet[i].corpo[2][4];
			mapa[abelhaVet[i].yOld+2][abelhaVet[i].xOld+5]=abelhaVet[i].corpo[2][5];
			mapa[abelhaVet[i].yOld+2][abelhaVet[i].xOld+6]=abelhaVet[i].corpo[2][6];

			mapa[abelhaVet[i].yOld+3][abelhaVet[i].xOld]=abelhaVet[i].corpo[3][0];
			mapa[abelhaVet[i].yOld+3][abelhaVet[i].xOld+1]=abelhaVet[i].corpo[3][1];
			mapa[abelhaVet[i].yOld+3][abelhaVet[i].xOld+2]=abelhaVet[i].corpo[3][2];
			mapa[abelhaVet[i].yOld+3][abelhaVet[i].xOld+3]=abelhaVet[i].corpo[3][3];
			mapa[abelhaVet[i].yOld+3][abelhaVet[i].xOld+4]=abelhaVet[i].corpo[3][4];
			mapa[abelhaVet[i].yOld+3][abelhaVet[i].xOld+5]=abelhaVet[i].corpo[3][5];
			mapa[abelhaVet[i].yOld+3][abelhaVet[i].xOld+6]=abelhaVet[i].corpo[3][6];



			cores[abelhaVet[i].yOld][abelhaVet[i].xOld]=abelhaVet[i].cor;
			cores[abelhaVet[i].yOld][abelhaVet[i].xOld+1]=abelhaVet[i].cor;
			cores[abelhaVet[i].yOld][abelhaVet[i].xOld+2]=abelhaVet[i].cor;
			cores[abelhaVet[i].yOld][abelhaVet[i].xOld+3]=abelhaVet[i].cor;
			cores[abelhaVet[i].yOld][abelhaVet[i].xOld+4]=abelhaVet[i].cor;
			cores[abelhaVet[i].yOld][abelhaVet[i].xOld+5]=abelhaVet[i].cor;
			cores[abelhaVet[i].yOld][abelhaVet[i].xOld+6]=abelhaVet[i].cor;

			cores[abelhaVet[i].yOld+1][abelhaVet[i].xOld]=abelhaVet[i].cor;
			cores[abelhaVet[i].yOld+1][abelhaVet[i].xOld+1]=abelhaVet[i].cor;
			cores[abelhaVet[i].yOld+1][abelhaVet[i].xOld+2]=abelhaVet[i].cor;
			cores[abelhaVet[i].yOld+1][abelhaVet[i].xOld+3]=abelhaVet[i].cor;
			cores[abelhaVet[i].yOld+1][abelhaVet[i].xOld+4]=abelhaVet[i].cor;
			cores[abelhaVet[i].yOld+1][abelhaVet[i].xOld+5]=abelhaVet[i].cor;
			cores[abelhaVet[i].yOld+1][abelhaVet[i].xOld+6]=abelhaVet[i].cor;

			cores[abelhaVet[i].yOld+2][abelhaVet[i].xOld]=abelhaVet[i].cor;
			cores[abelhaVet[i].yOld+2][abelhaVet[i].xOld+1]=abelhaVet[i].cor;
			cores[abelhaVet[i].yOld+2][abelhaVet[i].xOld+2]=abelhaVet[i].cor;
			cores[abelhaVet[i].yOld+2][abelhaVet[i].xOld+3]=abelhaVet[i].cor;
			cores[abelhaVet[i].yOld+2][abelhaVet[i].xOld+4]=abelhaVet[i].cor;
			cores[abelhaVet[i].yOld+2][abelhaVet[i].xOld+5]=abelhaVet[i].cor;
			cores[abelhaVet[i].yOld+2][abelhaVet[i].xOld+6]=abelhaVet[i].cor;

			cores[abelhaVet[i].yOld+3][abelhaVet[i].xOld]=abelhaVet[i].cor;
			cores[abelhaVet[i].yOld+3][abelhaVet[i].xOld+1]=abelhaVet[i].cor;
			cores[abelhaVet[i].yOld+3][abelhaVet[i].xOld+2]=abelhaVet[i].cor;
			cores[abelhaVet[i].yOld+3][abelhaVet[i].xOld+3]=abelhaVet[i].cor;
			cores[abelhaVet[i].yOld+3][abelhaVet[i].xOld+4]=abelhaVet[i].cor;
			cores[abelhaVet[i].yOld+3][abelhaVet[i].xOld+5]=abelhaVet[i].cor;
			cores[abelhaVet[i].yOld+3][abelhaVet[i].xOld+6]=abelhaVet[i].cor;
		}
	}

	for (int i = 0; i < MAXINIMIGOS; ++i)
	{
		rand1 = rand()% 8;
		switch(rand1){
			case 0:
				morcegoVet[i].yNew--;
			break;
			case 1:
				morcegoVet[i].yNew++;
			break;
			case 2:
				morcegoVet[i].xNew--;
			break;
			case 3:
				morcegoVet[i].xNew++;
			break;
			case 4:
				morcegoVet[i].xNew--;
				morcegoVet[i].yNew--;
			break;
			case 5:
				morcegoVet[i].xNew++;
				morcegoVet[i].yNew++;
			break;
			case 6:
				morcegoVet[i].xNew--;
				morcegoVet[i].yNew++;
			break;
			case 7:
				morcegoVet[i].xNew++;
				morcegoVet[i].yNew--;
			break;
		}
	}

	for (int i = 0; i < MAXINIMIGOS; ++i)
	{
		rand1 = rand()% 8;
		switch(rand1){
			case 0:
				gatoVet[i].yNew--;
			break;
			case 1:
				gatoVet[i].yNew++;
			break;
			case 2:
				gatoVet[i].xNew--;
			break;
			case 3:
				gatoVet[i].xNew++;
			break;
			case 4:
				gatoVet[i].xNew--;
				gatoVet[i].yNew--;
			break;
			case 5:
				gatoVet[i].xNew++;
				gatoVet[i].yNew++;
			break;
			case 6:
				gatoVet[i].xNew--;
				gatoVet[i].yNew++;
			break;
			case 7:
				gatoVet[i].xNew++;
				gatoVet[i].yNew--;
			break;
		}
	}

	for (int i = 0; i < MAXINIMIGOS; ++i)
	{
		rand1 = rand()% 8;
		switch(rand1){
			case 0:
				abelhaVet[i].yNew--;
			break;
			case 1:
				abelhaVet[i].yNew++;
			break;
			case 2:
				abelhaVet[i].xNew--;
			break;
			case 3:
				abelhaVet[i].xNew++;
			break;
			case 4:
				abelhaVet[i].xNew--;
				abelhaVet[i].yNew--;
			break;
			case 5:
				abelhaVet[i].xNew++;
				abelhaVet[i].yNew++;
			break;
			case 6:
				abelhaVet[i].xNew--;
				abelhaVet[i].yNew++;
			break;
			case 7:
				abelhaVet[i].xNew++;
				abelhaVet[i].yNew--;
			break;
		}
	}
}


void tela_menu (WINDOW *window){
	
 //    char list[5][7] = { "ISAAC" };
 //    char item[7];
 //    int i = 0;

 //    char c = 'c';

 
 //    initscr(); // initialize Ncurses
 //    window = newwin( LOGIN_BOX_HEIGHT,LOGIN_BOX_WIDHT ,OFFSET_X , OFFSET_Y); // create a new window
 //    box( window, 0, 0 ); // sets default borders for the window
     
	// // now print all the menu items and highlight the first one
	// mvwprintw(window,1, 8, "THE BINDING OF ISAAC");
 //    for( i=0; i<2; i++ ) {
 //        if( i == 0 ) 
 //            wattron( window, A_STANDOUT ); // highlights the first item.
 //        else
 //            wattroff( window, A_STANDOUT );
 //        sprintf(item, "%-5s",  list[i]);
 //        mvwprintw( window,3, 11 + (7 * i), "%s", item );
 //    }
 //    printf("\n");
 //    mvwprintw(window,11,  1, "HP");
 // 	mvwprintw(window,12, 1, "Strength");
 // 	mvwprintw(window,13, 1, "Speed");
 // 	mvwprintw(window,14, 1, "Luck");


 //    mvwprintw(window,4, 11, "     ");
 //  	mvwprintw(window,5, 11, "     ");
 // 	mvwprintw(window,6, 11, "(;_;)");
 // 	mvwprintw(window,7, 11, "__|__");
 // 	mvwprintw(window,8, 11, "  |  ");
 // 	mvwprintw(window,9, 11, " / \\ ");

 // 	mvwprintw(window,11,  12, "6");
 // 	mvwprintw(window,12, 12, "3.5");
 // 	mvwprintw(window,13, 12, "1.0");
 // 	mvwprintw(window,14, 12, "0");
 //    wrefresh( window ); // update the terminal screen
 
 //    noecho(); // disable echoing of characters on the screen
 //    keypad( window, TRUE ); // enable keyboard input for the window.
 //    curs_set(0); // hide the default screen cursor.
    
     
 //    while(c  == 'c'){
 //    	c = getchar();

 //    }
 	
 //    delwin( window);
}