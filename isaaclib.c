#include "defs.h"

void desenharBordas(WINDOW *janela) {
  box( janela, 0, 0 ); // desenha as bordas da janela indicada
}

void teste_redimensao(int *xAtual, int *yAtual, WINDOW *janelaScore, WINDOW *janelaJogo, personagem_t isaac, char **mapa, char **cores){
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
		infoScore(janelaScore, isaac);
		imprimeMapa(mapa, cores, janelaJogo);
		imprimirIsaac(isaac,janelaJogo,mapa, cores);
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
    		if (cores[i][j]=='j')
    		{
				init_pair(1, COLOR_GREEN, COLOR_BLACK);
				wattron(janela,COLOR_PAIR(1));
				mvwprintw(janela, yMapa()+i, xMapa()+j, "%c",mapa[i][j]);//imprime os caracteres dos bonecos
				wattroff(janela,COLOR_PAIR(1));
    		} else if (cores[i][j]=='g' || cores[i][j]=='h' || cores[i][j]=='i'){
				init_pair(2, COLOR_YELLOW, COLOR_BLACK);
				wattron(janela,COLOR_PAIR(2));
				mvwprintw(janela, yMapa()+i, xMapa()+j, "%c",mapa[i][j]);//imprime os caracteres dos bonecos
				wattroff(janela,COLOR_PAIR(2));
    		}
    		else if(cores[i][j]=='d' || cores[i][j]=='e' || cores[i][j]=='f'){
				init_pair(3, COLOR_CYAN, COLOR_BLACK);
				wattron(janela,COLOR_PAIR(3));
				mvwprintw(janela, yMapa()+i, xMapa()+j, "%c",mapa[i][j]);//imprime os caracteres dos bonecos
				wattroff(janela,COLOR_PAIR(3));
    		}
    		else if(cores[i][j]=='a' || cores[i][j]=='b' || cores[i][j]=='c'){
				init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
				wattron(janela,COLOR_PAIR(4));
				mvwprintw(janela, yMapa()+i, xMapa()+j, "%c",mapa[i][j]);//imprime os caracteres dos bonecos
				wattroff(janela,COLOR_PAIR(4));
    		}
    		else if(cores[i][j]=='t'){
				init_pair(5, COLOR_BLUE, COLOR_BLACK);
				wattron(janela,COLOR_PAIR(5));
				mvwprintw(janela, yMapa()+i, xMapa()+j, "%c",mapa[i][j]);//imprime os caracteres dos bonecos
				wattroff(janela,COLOR_PAIR(5));
    		}
    		else mvwprintw(janela, yMapa()+i, xMapa()+j, "%c",mapa[i][j]);
    	}
    }
}

void infoScore(WINDOW *janela, personagem_t isaac){
	start_color();
	int xAtual;
	xAtual=getmaxx(stdscr);
	init_pair(6, COLOR_RED, COLOR_BLACK);
	mvwprintw(janela, 1, xAtual-40, "Pressione tecla 'H' para obter ajuda.",isaac.points);
	switch(isaac.hearts){
		case 0:
			mvwprintw(janela, 1, (xAtual-31)/2, "GAME OVER!!!!!!!!!!!!");
		break;
		case 1:
				mvwprintw(janela, 1, (xAtual-31)/2, "Hearts:           Points:",isaac.points);
				wattron(janela,COLOR_PAIR(2));
				mvwprintw(janela, 1, ((xAtual-31)/2)+25, "%04d",isaac.points);
				wattroff(janela,COLOR_PAIR(2));				
				wattron(janela,COLOR_PAIR(6));
				mvwprintw(janela, 1, ((xAtual-31)/2)+8, "<3");
				wattroff(janela,COLOR_PAIR(6));
				mvwprintw(janela, 1, ((xAtual-31)/2)+11,"__ __");
		break;
		case 2:
				mvwprintw(janela, 1, (xAtual-31)/2, "Hearts:           Points:",isaac.points);
				wattron(janela,COLOR_PAIR(2));
				mvwprintw(janela, 1, ((xAtual-31)/2)+25, "%04d",isaac.points);
				wattroff(janela,COLOR_PAIR(2));				
				wattron(janela,COLOR_PAIR(6));
				mvwprintw(janela, 1, ((xAtual-31)/2)+8, "<3 <3");
				wattroff(janela,COLOR_PAIR(6));
				mvwprintw(janela, 1, ((xAtual-31)/2)+14,"__");
		break;
		case 3:
				mvwprintw(janela, 1, (xAtual-31)/2, "Hearts:           Points:",isaac.points);
				wattron(janela,COLOR_PAIR(2));
				mvwprintw(janela, 1, ((xAtual-31)/2)+25, "%04d",isaac.points);
				wattroff(janela,COLOR_PAIR(2));				
				wattron(janela,COLOR_PAIR(6));
				mvwprintw(janela, 1, ((xAtual-31)/2)+8, "<3 <3 <3");
				wattroff(janela,COLOR_PAIR(6));
		break;
	}
}

void imprimirIsaac(personagem_t isaac, WINDOW *janela,char** mapa, char **cores){
	/*cabeça*/
	mapa[isaac.y][isaac.x]='(';
	mapa[isaac.y][isaac.x+1]=';';
	mapa[isaac.y][isaac.x+2]='_';
	mapa[isaac.y][isaac.x+3]=';';
	mapa[isaac.y][isaac.x+4]=')';

	/*braços*/
	mapa[isaac.y+1][isaac.x]='_';
	mapa[isaac.y+1][isaac.x+1]='_';
	mapa[isaac.y+1][isaac.x+2]='|';
	mapa[isaac.y+1][isaac.x+3]='_';
	mapa[isaac.y+1][isaac.x+4]='_';

	/*tronco*/
	mapa[isaac.y+2][isaac.x+2]='|';

	/*pernas*/
	mapa[isaac.y+3][isaac.x+1]='/';
	mapa[isaac.y+3][isaac.x+2]=' ';
	mapa[isaac.y+3][isaac.x+3]='\\';

	/*cabeça*/
	cores[isaac.y][isaac.x]='j';
	cores[isaac.y][isaac.x+1]='j';
	cores[isaac.y][isaac.x+2]='j';
	cores[isaac.y][isaac.x+3]='j';
	cores[isaac.y][isaac.x+4]='j';

	/*braços*/
	cores[isaac.y+1][isaac.x]='j';
	cores[isaac.y+1][isaac.x+1]='j';
	cores[isaac.y+1][isaac.x+2]='j';
	cores[isaac.y+1][isaac.x+3]='j';
	cores[isaac.y+1][isaac.x+4]='j';

	/*tronco*/
	cores[isaac.y+2][isaac.x+2]='j';

	/*pernas*/
	cores[isaac.y+3][isaac.x+1]='j';
	cores[isaac.y+3][isaac.x+2]='j';
	cores[isaac.y+3][isaac.x+3]='j';
}

void attJanelas(WINDOW *janelaJogo, WINDOW *janelaScore, personagem_t isaac, char** mapa, char **cores){
    // atualiza janelas
    infoScore(janelaScore, isaac);
	imprimeMapa(mapa, cores, janelaJogo);
	imprimirIsaac(isaac,janelaJogo,mapa, cores);
    wrefresh(janelaScore);
    wrefresh(janelaJogo);
}

void apagarIsaac(personagem_t isaac, WINDOW *janela,char** mapa, char** cores){

	/*cabeça*/
	mapa[isaac.y][isaac.x]=' ';
	mapa[isaac.y][isaac.x+1]=' ';
	mapa[isaac.y][isaac.x+2]=' ';
	mapa[isaac.y][isaac.x+3]=' ';
	mapa[isaac.y][isaac.x+4]=' ';

	/*braços*/
	mapa[isaac.y+1][isaac.x]=' ';
	mapa[isaac.y+1][isaac.x+1]=' ';
	mapa[isaac.y+1][isaac.x+2]=' ';
	mapa[isaac.y+1][isaac.x+3]=' ';
	mapa[isaac.y+1][isaac.x+4]=' ';

	/*tronco*/
	mapa[isaac.y+2][isaac.x+2]=' ';

	/*pernas*/
	mapa[isaac.y+3][isaac.x+1]=' ';
	mapa[isaac.y+3][isaac.x+2]=' ';
	mapa[isaac.y+3][isaac.x+3]=' ';


	/*cabeça*/
	cores[isaac.y][isaac.x]=' ';
	cores[isaac.y][isaac.x+1]=' ';
	cores[isaac.y][isaac.x+2]=' ';
	cores[isaac.y][isaac.x+3]=' ';
	cores[isaac.y][isaac.x+4]=' ';

	/*braços*/
	cores[isaac.y+1][isaac.x]=' ';
	cores[isaac.y+1][isaac.x+1]=' ';
	cores[isaac.y+1][isaac.x+2]=' ';
	cores[isaac.y+1][isaac.x+3]=' ';
	cores[isaac.y+1][isaac.x+4]=' ';

	/*tronco*/
	cores[isaac.y+2][isaac.x+2]=' ';

	/*pernas*/
	cores[isaac.y+3][isaac.x+1]=' ';
	cores[isaac.y+3][isaac.x+2]=' ';
	cores[isaac.y+3][isaac.x+3]=' ';
}

void lerTeclado(WINDOW *janelaJogo, WINDOW*janelaScore, personagem_t *isaac, char** mapa, char** cores, int *gameOver){
	int ch,xMax,yMax;
    ch = wgetch(janelaJogo);
    getmaxyx(janelaJogo,yMax,xMax);
    switch( ch ) {
	    case 'd':
	    		if (mapa[(isaac->y)][(isaac->x)+5]==' ')
	    		{
    				apagarIsaac(*isaac,janelaJogo,mapa,cores);
	    			((isaac->x))++;
	    		}
        break;
	    case 'a':
	    		if (mapa[(isaac->y)][(isaac->x)-1]==' ')
	    		{
	    			apagarIsaac(*isaac,janelaJogo,mapa,cores);
		    		((isaac->x))--;
	    		}
        break;
	    case 's':
	    		if (mapa[(isaac->y)+4][(isaac->x)]==' ')
	    		{
    				apagarIsaac(*isaac,janelaJogo,mapa,cores);
		    		((isaac->y))++;
	    		}
        break;
	    case 'w':
	    		if (mapa[(isaac->y)-1][(isaac->x)]==' ')
	    		{
    				apagarIsaac(*isaac,janelaJogo,mapa,cores);
	    			((isaac->y))--;
	    		}
        break;
	    case 'h':
  			printf("\033[?1003l\n"); // Disable mouse movement events, as l = low
			nodelay (janelaJogo, FALSE) ; 
			wclear(janelaJogo);
			desenharBordas(janelaJogo);
			desenharBordas(janelaScore);

			mvwprintw(janelaJogo, ((yMax-30)/2)+0, (xMax-140)/2,  "############################################################################################################################################");
			mvwprintw(janelaJogo, ((yMax-30)/2)+1, (xMax-140)/2,  "#                                                                                                                                          #");
			mvwprintw(janelaJogo, ((yMax-30)/2)+2, (xMax-140)/2,  "#                                                 TELA DE AJUDA                                                                            #");
			mvwprintw(janelaJogo, ((yMax-30)/2)+3, (xMax-140)/2,  "#                                                                                                                                          #");
			mvwprintw(janelaJogo, ((yMax-30)/2)+4, (xMax-140)/2,  "#          CONTROLES:                                   |    DICA:                                                                         #");
			mvwprintw(janelaJogo, ((yMax-30)/2)+5, (xMax-140)/2,  "#                                                       |                                                                                  #");
			mvwprintw(janelaJogo, ((yMax-30)/2)+6, (xMax-140)/2,  "#               W ~> Anda para cima                     |      Mate todos os inimigos para conseguir pontuações maiores.                 #");
			mvwprintw(janelaJogo, ((yMax-30)/2)+7, (xMax-140)/2,  "#               S ~> Anda para baixo                    |                                                                                  #");
			mvwprintw(janelaJogo, ((yMax-30)/2)+8, (xMax-140)/2,  "#               A ~> Anda para esquerda                 |                                                                                  #");
			mvwprintw(janelaJogo, ((yMax-30)/2)+9, (xMax-140)/2,  "#               D ~> Anda para direita                  |           /\\_/\\                                                                  #");
			mvwprintw(janelaJogo, ((yMax-30)/2)+10, (xMax-140)/2, "#                                                       |          ( o.o )       ~> Gatinho 10 pontos                                      #");
			mvwprintw(janelaJogo, ((yMax-30)/2)+11, (xMax-140)/2, "#                                                       |           > ^ <                                                                  #");
			mvwprintw(janelaJogo, ((yMax-30)/2)+12, (xMax-140)/2, "#               Mouse ~> Atira                          |             __                                                                   #");
			mvwprintw(janelaJogo, ((yMax-30)/2)+13, (xMax-140)/2, "#                                                       |           _/__)                                                                  #");
			mvwprintw(janelaJogo, ((yMax-30)/2)+14, (xMax-140)/2, "#                                                       |          (8|)_}}       ~> Abelha 15 pontos                                       #");
			mvwprintw(janelaJogo, ((yMax-30)/2)+15, (xMax-140)/2, "#                                                       |           `\\__)                                                                  #");
			mvwprintw(janelaJogo, ((yMax-30)/2)+16, (xMax-140)/2, "#                                                       |                                                                                  #");
			mvwprintw(janelaJogo, ((yMax-30)/2)+17, (xMax-140)/2, "#                                                       |        /\\/\\(o_o)/\\/\\   ~> Morcego 20 pontos                                      #");
			mvwprintw(janelaJogo, ((yMax-30)/2)+18, (xMax-140)/2, "#                                                       |                                                                                  #");
			mvwprintw(janelaJogo, ((yMax-30)/2)+19, (xMax-140)/2, "#                                                       |                                                                                  #");
			mvwprintw(janelaJogo, ((yMax-30)/2)+20, (xMax-140)/2, "#                                                                                                                                          #");
			mvwprintw(janelaJogo, ((yMax-30)/2)+21, (xMax-140)/2, "#                                                                                                                                          #");
			mvwprintw(janelaJogo, ((yMax-30)/2)+22, (xMax-140)/2, "#                                                                                                                                          #");
			mvwprintw(janelaJogo, ((yMax-30)/2)+23, (xMax-140)/2, "#                                                                                                                                          #");
			mvwprintw(janelaJogo, ((yMax-30)/2)+24, (xMax-140)/2, "#                                                                                                                                          #");
			mvwprintw(janelaJogo, ((yMax-30)/2)+25, (xMax-140)/2, "#                                                                                                                                          #");
			mvwprintw(janelaJogo, ((yMax-30)/2)+26, (xMax-140)/2, "#                                                                                                                                          #");
			mvwprintw(janelaJogo, ((yMax-30)/2)+27, (xMax-140)/2, "#                                                                                                                                          #");
			mvwprintw(janelaJogo, ((yMax-30)/2)+28, (xMax-140)/2, "#                                                                          Pressione qualquer tecla para continuar e 'Q' para sair do jogo #");
			mvwprintw(janelaJogo, ((yMax-30)/2)+29, (xMax-140)/2, "############################################################################################################################################");
   			ch = wgetch(janelaJogo);

   			if (ch == 'q' || ch == 'Q')
   			{
				*gameOver=1;
   			}
			nodelay (janelaJogo,TRUE) ; 
  			printf("\033[?1003h\n"); // Disable mouse movement events, as l = low
			wclear(janelaJogo);
        break;
   	}
}

void tiro(WINDOW *janelaJogo, WINDOW *janelaScore, MEVENT *event, personagem_t *isaac, int *oldMouseX, int *oldMouseY,char** mapa, tiro_t tiros[], char**cores, int clock,morcego_t morcegoVet[], gato_t gatoVet[], abelha_t abelhaVet[]){
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

	/*##############TESTANDO A POSIÇÂO DO MOUSE PARA DETERMINAR DIREÇÃO CASO SEJA ATIRADO*##############*/
	if ((*oldMouseY <= isaac->y ) && (*oldMouseX >= isaac->x - 20) && (*oldMouseX <= isaac->x+20))
	{
		d=0;
	}

	if ((*oldMouseY >= isaac->y ) && (*oldMouseX >= isaac->x - 20) && (*oldMouseX <= isaac->x+20))
	{
		d=1;
	}

	if ((*oldMouseY >= isaac->y -10 ) && (*oldMouseY <= isaac->y + 10) && (*oldMouseX <= isaac->x))
	{
		d=2;
	}
	
	if ((*oldMouseY >= isaac->y -10 ) && (*oldMouseY <= isaac->y + 10) && (*oldMouseX >= isaac->x))
	{
		d=3;
	}

	if((*oldMouseY <= isaac->y - 10) && (*oldMouseX >= isaac->x + 20)){
		d=4;
	}

	if ((*oldMouseY >= isaac->y + 10) && (*oldMouseX >= isaac->x + 20))
	{
		d=5;
	}

	if ((*oldMouseY <= isaac->y - 10) &&  (*oldMouseX <= isaac->x -20))
	{
		d=6;
	}


	if ((*oldMouseY >= isaac->y + 10) && (*oldMouseX <= isaac->x - 20))
	{
		d=7;
	}
	/*################################################################################################*/
	
	if (click==2 < 10) //se clickar e nao houverem 10 tiros ja
	{
		beep();
		flash();

		tiros[numtiros].estado = 1; //mudo estado para 1 (tiro andando)
		switch(d){
			case 0:
				tiros[numtiros].y = isaac->y;
				tiros[numtiros].x = isaac->x+2;
			break;
			case 1:
				tiros[numtiros].y = isaac->y+2;
				tiros[numtiros].x = isaac->x+2;
			break;
			case 2:
				tiros[numtiros].y = isaac->y;
				tiros[numtiros].x = isaac->x;
			break;
			case 3:
				tiros[numtiros].y = isaac->y;
				tiros[numtiros].x = isaac->x+4;
			break;
			case 4:
				tiros[numtiros].y = isaac->y;
				tiros[numtiros].x = isaac->x+4;
			break;
			case 5:
				tiros[numtiros].y = isaac->y;
				tiros[numtiros].x = isaac->x+4;
			break;
			case 6:
				tiros[numtiros].y = isaac->y;
				tiros[numtiros].x = isaac->x;
			break;
			case 7:
				tiros[numtiros].y = isaac->y;
				tiros[numtiros].x = isaac->x;
			break;
		}

		tiros[numtiros].d = d; //atribui direção atual do mouse à direção do tiro
		numtiros++; // aumenta o contador de tiros
	}


	/*tiro inimigo*/
	if (clock % 500 == 0 && morcegoVet[0].estado) //se clickar e nao houverem 10 tiros ja
	{
		tiros[numtiros].estado = 1; //mudo estado para 1 (tiro andando)

		if (isaac->x >= morcegoVet[0].xOld)
		{
			tiros[numtiros].x = morcegoVet[0].xOld+14;
			tiros[numtiros].y = morcegoVet[0].yOld;
			tiros[numtiros].d = 3; //atribui direção atual do mouse à direção do tiro
		}
		else{
			tiros[numtiros].d = 2;
			tiros[numtiros].x = morcegoVet[0].xOld+1;
			tiros[numtiros].y = morcegoVet[0].yOld;
		}
		numtiros++; // aumenta o contador de tiros
	}


	/*ATUALIZAR TIROS EXISTENTES */
	if (clock % 4 == 0)
	{
		for (int i = 0; i < MAXTIROS; ++i)
		{
			if (tiros[i].estado) // se estado != 0 tiro existe e precisa ser atualizado
			{
				switch (tiros[i].estado){
					case 1: //tiro 'andando'
						switch(tiros[i].d){
							case 0: //cima
								if(mapa[tiros[i].y-1][tiros[i].x]==' '){
									mapa[tiros[i].y][tiros[i].x]=' ';
									(tiros[i].y) --;
									cores[tiros[i].y][tiros[i].x]='t';
									mapa[tiros[i].y][tiros[i].x]=TIRO;
								}
								else tiros[i].estado = 3;
								switch (cores[tiros[i].y-1][tiros[i].x]){
									case 'a':
										morcegoVet[0].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=20;
									break;
									case 'b':
										morcegoVet[1].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=20;
									break;
									case 'c':
										morcegoVet[2].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=20;
									break;
									case 'd':
										gatoVet[0].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=10;
									break;
									case 'e':
										gatoVet[1].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=10;
									break;
									case 'f':
										gatoVet[2].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=10;
									break;
									case 'g':
										abelhaVet[0].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=15;
									break;
									case 'h':
										abelhaVet[1].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=15;
									break;
									case 'i':
										abelhaVet[2].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=15;
									break;
									case 'j':
										//mata personagem
										tiros[i].estado =2;
										isaac->hearts--;
									break;
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
								else tiros[i].estado = 2;
								switch (cores[tiros[i].y+1][tiros[i].x]){
									case 'a':
										morcegoVet[0].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=20;
									break;
									case 'b':
										morcegoVet[1].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=20;
									break;
									case 'c':
										morcegoVet[2].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=20;
									break;
									case 'd':
										gatoVet[0].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=10;
									break;
									case 'e':
										gatoVet[1].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=10;
									break;
									case 'f':
										gatoVet[2].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=10;
									break;
									case 'g':
										abelhaVet[0].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=15;
									break;
									case 'h':
										abelhaVet[1].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=15;
									break;
									case 'i':
										abelhaVet[2].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=15;
									break;
									case 'j':
										//mata personagem
										tiros[i].estado =2;
										isaac->hearts--;
									break;
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
								else tiros[i].estado = 2;
								switch (cores[tiros[i].y][tiros[i].x-1]){
									case 'a':
										morcegoVet[0].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=20;
									break;
									case 'b':
										morcegoVet[1].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=20;
									break;
									case 'c':
										morcegoVet[2].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=20;
									break;
									case 'd':
										gatoVet[0].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=10;
									break;
									case 'e':
										gatoVet[1].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=10;
									break;
									case 'f':
										gatoVet[2].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=10;
									break;
									case 'g':
										abelhaVet[0].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=15;
									break;
									case 'h':
										abelhaVet[1].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=15;
									break;
									case 'i':
										abelhaVet[2].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=15;
									break;
									case 'j':
										//mata personagem
										tiros[i].estado =2;
										isaac->hearts--;
									break;
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
								else tiros[i].estado = 2;
								switch (cores[tiros[i].y][tiros[i].x+1]){
									case 'a':
										morcegoVet[0].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=20;
									break;
									case 'b':
										morcegoVet[1].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=20;
									break;
									case 'c':
										morcegoVet[2].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=20;
									break;
									case 'd':
										gatoVet[0].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=10;
									break;
									case 'e':
										gatoVet[1].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=10;
									break;
									case 'f':
										gatoVet[2].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=10;
									break;
									case 'g':
										abelhaVet[0].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=15;
									break;
									case 'h':
										abelhaVet[1].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=15;
									break;
									case 'i':
										abelhaVet[2].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=15;
									break;
									case 'j':
										//mata personagem
										tiros[i].estado =2;
										isaac->hearts--;
									break;
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
								}else tiros[i].estado = 2;
								switch (cores[tiros[i].y-1][tiros[i].x+1]){
									case 'a':
										morcegoVet[0].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=20;
									break;
									case 'b':
										morcegoVet[1].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=20;
									break;
									case 'c':
										morcegoVet[2].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=20;
									break;
									case 'd':
										gatoVet[0].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=10;
									break;
									case 'e':
										gatoVet[1].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=10;
									break;
									case 'f':
										gatoVet[2].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=10;
									break;
									case 'g':
										abelhaVet[0].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=15;
									break;
									case 'h':
										abelhaVet[1].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=15;
									break;
									case 'i':
										abelhaVet[2].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=15;
									break;
									case 'j':
										//mata personagem
										tiros[i].estado =2;
										isaac->hearts--;
									break;
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
								}else tiros[i].estado = 2;
								switch (cores[tiros[i].y+1][tiros[i].x+1]){
									case 'a':
										morcegoVet[0].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=20;
									break;
									case 'b':
										morcegoVet[1].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=20;
									break;
									case 'c':
										morcegoVet[2].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=20;
									break;
									case 'd':
										gatoVet[0].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=10;
									break;
									case 'e':
										gatoVet[1].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=10;
									break;
									case 'f':
										gatoVet[2].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=10;
									break;
									case 'g':
										abelhaVet[0].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=15;
									break;
									case 'h':
										abelhaVet[1].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=15;
									break;
									case 'i':
										abelhaVet[2].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=15;
									break;
									case 'j':
										//mata personagem
										tiros[i].estado =2;
										isaac->hearts--;
									break;
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
								}else tiros[i].estado = 2;
								switch (cores[tiros[i].y-1][tiros[i].x-1]){
									case 'a':
										morcegoVet[0].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=20;
									break;
									case 'b':
										morcegoVet[1].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=20;
									break;
									case 'c':
										morcegoVet[2].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=20;
									break;
									case 'd':
										gatoVet[0].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=10;
									break;
									case 'e':
										gatoVet[1].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=10;
									break;
									case 'f':
										gatoVet[2].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=10;
									break;
									case 'g':
										abelhaVet[0].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=15;
									break;
									case 'h':
										abelhaVet[1].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=15;
									break;
									case 'i':
										abelhaVet[2].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=15;
									break;
									case 'j':
										//mata personagem
										tiros[i].estado =2;
										isaac->hearts--;
									break;
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
								}else tiros[i].estado = 2;
								switch (cores[tiros[i].y+1][tiros[i].x-1]){
									case 'a':
										morcegoVet[0].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=20;
									break;
									case 'b':
										morcegoVet[1].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=20;
									break;
									case 'c':
										morcegoVet[2].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=20;
									break;
									case 'd':
										gatoVet[0].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=10;
									break;
									case 'e':
										gatoVet[1].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=10;
									break;
									case 'f':
										gatoVet[2].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=10;
									break;
									case 'g':
										abelhaVet[0].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=15;
									break;
									case 'h':
										abelhaVet[1].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=15;
									break;
									case 'i':
										abelhaVet[2].estado = 2;
										tiros[i].estado = 2;
										isaac->points +=15;
									break;
									case 'j':
										//mata personagem
										tiros[i].estado =2;
										isaac->hearts--;
									break;
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
						tiros[i].estado = 0;
						numtiros--;
					break;
				}
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

		int yM = (rand()% (LINMAX -4 -yMapa()-2))+1;
		int xM = (rand()% (COLMAX - xMapa()-colMorcego))+1;

		morcegoVet[i].yOld = yM;
		morcegoVet[i].xOld = xM;

		morcegoVet[i].yNew = yM;
		morcegoVet[i].xNew = xM;

		morcegoVet[i].vidas = 1;
		morcegoVet[i].estado = 0;
		switch(i){
			case 0:
				morcegoVet[i].cor = 'a';
			break;
			case 1:
				morcegoVet[i].cor = 'b';
			break;
			case 2:
				morcegoVet[i].cor = 'c';
			break;
		}
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
		int xG = (rand()% (COLMAX - xMapa()-colGato))+1;
		gatoVet[i].yOld = yG;
		gatoVet[i].xOld = xG;

		gatoVet[i].yNew = yG;
		gatoVet[i].xNew = xG;

		gatoVet[i].vidas = 3;
		gatoVet[i].estado = 0;
		switch(i){
			case 0:
				gatoVet[i].cor = 'd';
			break;
			case 1:
				gatoVet[i].cor = 'e';
			break;
			case 2:
				gatoVet[i].cor = 'f';
			break;
		}
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
		int xA = (rand()% (COLMAX - xMapa()-colAbelha))+1;
		abelhaVet[i].yOld = yA;
		abelhaVet[i].xOld = xA;

		abelhaVet[i].yNew = yA;
		abelhaVet[i].xNew = xA;

		abelhaVet[i].vidas = 2;
		abelhaVet[i].estado = 0;
		
		switch(i){
			case 0:
				abelhaVet[i].cor = 'g';
			break;
			case 1:
				abelhaVet[i].cor = 'h';
			break;
			case 2:
				abelhaVet[i].cor = 'i';
			break;
		}

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
}

void geraInimigo(WINDOW *janelaJogo, char** mapa, char** cores, morcego_t morcegoVet[], gato_t gatoVet[], abelha_t abelhaVet[], int clock){
	int rand1 =0;
	int delay =100;
	if (delay>0)
	{
		delay--;
	}
	for (int i = 0; i < MAXINIMIGOS; ++i)
	{
		if (clock % delay == 0)
		{
			for (int i = 0; i < MAXINIMIGOS; ++i)
			{
				rand1 = rand()% 8;
				switch(rand1){
					case 0:
						if (mapa[morcegoVet[i].yNew-1][morcegoVet[i].xNew]==' ')
						{
							morcegoVet[i].yNew--;
						}
					break;
					case 1:
						if (mapa[morcegoVet[i].yNew+1][morcegoVet[i].xNew]==' ')
						{
							morcegoVet[i].yNew++;
						}
					break;
					case 2:
						if (mapa[morcegoVet[i].yNew][morcegoVet[i].xNew-1]==' ')
						{
							morcegoVet[i].xNew--;
						}
					break;
					case 3:
						if (mapa[morcegoVet[i].yNew][morcegoVet[i].xNew+colMorcego+1]==' ')
						{
							morcegoVet[i].xNew++;
						}
					break;
					case 4:
						if (mapa[morcegoVet[i].yNew][morcegoVet[i].xNew-1]==' ')
						{
							morcegoVet[i].xNew--;
						}
						if (mapa[morcegoVet[i].yNew-1][morcegoVet[i].xNew]==' ')
						{
							morcegoVet[i].yNew--;
						}
					break;
					case 5:
						if (mapa[morcegoVet[i].yNew][morcegoVet[i].xNew+colMorcego+1]==' ')
						{
							morcegoVet[i].xNew++;
						}
						if (mapa[morcegoVet[i].yNew+1][morcegoVet[i].xNew]==' ')
						{
							morcegoVet[i].yNew++;
						}
					break;
					case 6:
						if (mapa[morcegoVet[i].yNew][morcegoVet[i].xNew-1]==' ')
						{
							morcegoVet[i].xNew--;
						}
						if (mapa[morcegoVet[i].yNew+1][morcegoVet[i].xNew]==' ')
						{
							morcegoVet[i].yNew++;
						}
					break;
					case 7:
						if (mapa[morcegoVet[i].yNew][morcegoVet[i].xNew+colMorcego+1]==' ')
						{
							morcegoVet[i].xNew++;
						}
						if (mapa[morcegoVet[i].yNew-1][morcegoVet[i].xNew]==' ')
						{
							morcegoVet[i].yNew--;
						}
					break;
				}
			}

			for (int i = 0; i < MAXINIMIGOS; ++i)
			{
				rand1 = rand()% 8;
				switch(rand1){
					case 0:
						if (mapa[gatoVet[i].yNew-1][gatoVet[i].xNew]==' ')
						{
							gatoVet[i].yNew--;
						}
					break;
					case 1:
						if (mapa[gatoVet[i].yNew+1+linGato][gatoVet[i].xNew]==' ')
						{
							gatoVet[i].yNew++;
						}
					break;
					case 2:
						if (mapa[gatoVet[i].yNew][gatoVet[i].xNew-1]==' ')
						{
							gatoVet[i].xNew--;
						}
					break;
					case 3:
						if (mapa[gatoVet[i].yNew][gatoVet[i].xNew+colGato+1]==' ')
						{
							gatoVet[i].xNew++;
						}
					break;
					case 4:
						if (mapa[gatoVet[i].yNew][gatoVet[i].xNew-1]==' ')
						{
							gatoVet[i].xNew--;
						}
						if (mapa[gatoVet[i].yNew-1][gatoVet[i].xNew]==' ')
						{
							gatoVet[i].yNew--;
						}
					break;
					case 5:
						if (mapa[gatoVet[i].yNew][gatoVet[i].xNew+colGato+1]==' ')
						{
							gatoVet[i].xNew++;
						}
						if (mapa[gatoVet[i].yNew+1+linGato][gatoVet[i].xNew]==' ')
						{
							gatoVet[i].yNew++;
						}
					break;
					case 6:
						if (mapa[gatoVet[i].yNew][gatoVet[i].xNew-1]==' ')
						{
							gatoVet[i].xNew--;
						}
						if (mapa[gatoVet[i].yNew+1+linGato][gatoVet[i].xNew]==' ')
						{
							gatoVet[i].yNew++;
						}
					break;
					case 7:
						if (mapa[gatoVet[i].yNew][gatoVet[i].xNew+colGato+1]==' ')
						{
							gatoVet[i].xNew++;
						}
						if (mapa[gatoVet[i].yNew-1][gatoVet[i].xNew]==' ')
						{
							gatoVet[i].yNew--;
						}
					break;
				}
			}

			for (int i = 0; i < MAXINIMIGOS; ++i)
			{
				rand1 = rand()% 8;
				switch(rand1){
					case 0:
						if (mapa[abelhaVet[i].yNew-1][abelhaVet[i].xNew]==' ')
						{
							abelhaVet[i].yNew--;
						}
					break;
					case 1:
						if (mapa[abelhaVet[i].yNew+1+linAbelha][abelhaVet[i].xNew]==' ')
						{
							abelhaVet[i].yNew++;
						}
					break;
					case 2:
						if (mapa[abelhaVet[i].yNew][abelhaVet[i].xNew-1]==' ')
						{
							abelhaVet[i].xNew--;
						}
					break;
					case 3:
						if (mapa[abelhaVet[i].yNew][abelhaVet[i].xNew+colAbelha+1]==' ')
						{
							abelhaVet[i].xNew++;
						}
					break;
					case 4:
						if (mapa[abelhaVet[i].yNew][abelhaVet[i].xNew-1]==' ')
						{
							abelhaVet[i].xNew--;
						}
						if (mapa[abelhaVet[i].yNew-1][abelhaVet[i].xNew]==' ')
						{
							abelhaVet[i].yNew--;
						}
					break;
					case 5:
						if (mapa[abelhaVet[i].yNew][abelhaVet[i].xNew+colAbelha+1]==' ')
						{
							abelhaVet[i].xNew++;
						}
						if (mapa[abelhaVet[i].yNew+1+linAbelha][abelhaVet[i].xNew]==' ')
						{
							abelhaVet[i].yNew++;
						}
					break;
					case 6:
						if (mapa[abelhaVet[i].yNew][abelhaVet[i].xNew-1]==' ')
						{
							abelhaVet[i].xNew--;
						}
						if (mapa[abelhaVet[i].yNew+1+linAbelha][abelhaVet[i].xNew]==' ')
						{
							abelhaVet[i].yNew++;
						}
					break;
					case 7:
						if (mapa[abelhaVet[i].yNew][abelhaVet[i].xNew+colAbelha+1]==' ')
						{
							abelhaVet[i].xNew++;
						}
						if (mapa[abelhaVet[i].yNew-1][abelhaVet[i].xNew]==' ')
						{
							abelhaVet[i].yNew--;
						}
					break;
				}
			}
		}


		if (morcegoVet[i].estado==1)
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

			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+1]=' ';
			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+2]=' ';
			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+3]=' ';
			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+4]=' ';
			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+5]=' ';
			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+6]=' ';
			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+7]=' ';
			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+8]=' ';
			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+9]=' ';
			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+10]=' ';
			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+11]=' ';
			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+12]=' ';
			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+13]=' ';


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
		if (morcegoVet[i].estado==2){
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

			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+1]=' ';
			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+2]=' ';
			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+3]=' ';
			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+4]=' ';
			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+5]=' ';
			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+6]=' ';
			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+7]=' ';
			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+8]=' ';
			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+9]=' ';
			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+10]=' ';
			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+11]=' ';
			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+12]=' ';
			cores[morcegoVet[i].yOld][morcegoVet[i].xOld+13]=' ';

			morcegoVet[i].estado=0; //muda para o estado 0 para nao ficar printando espaços em branco após a morte do inimigo
		}

		if (gatoVet[i].estado==1)
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



			cores[gatoVet[i].yOld][gatoVet[i].xOld]=' ';
			cores[gatoVet[i].yOld][gatoVet[i].xOld+1]=' ';
			cores[gatoVet[i].yOld][gatoVet[i].xOld+2]=' ';
			cores[gatoVet[i].yOld][gatoVet[i].xOld+3]=' ';
			cores[gatoVet[i].yOld][gatoVet[i].xOld+4]=' ';
			cores[gatoVet[i].yOld][gatoVet[i].xOld+5]=' ';
			cores[gatoVet[i].yOld][gatoVet[i].xOld+6]=' ';

			cores[gatoVet[i].yOld+1][gatoVet[i].xOld]=' ';
			cores[gatoVet[i].yOld+1][gatoVet[i].xOld+1]=' ';
			cores[gatoVet[i].yOld+1][gatoVet[i].xOld+2]=' ';
			cores[gatoVet[i].yOld+1][gatoVet[i].xOld+3]=' ';
			cores[gatoVet[i].yOld+1][gatoVet[i].xOld+4]=' ';
			cores[gatoVet[i].yOld+1][gatoVet[i].xOld+5]=' ';
			cores[gatoVet[i].yOld+1][gatoVet[i].xOld+6]=' ';

			cores[gatoVet[i].yOld+2][gatoVet[i].xOld]=' ';
			cores[gatoVet[i].yOld+2][gatoVet[i].xOld+1]=' ';
			cores[gatoVet[i].yOld+2][gatoVet[i].xOld+2]=' ';
			cores[gatoVet[i].yOld+2][gatoVet[i].xOld+3]=' ';
			cores[gatoVet[i].yOld+2][gatoVet[i].xOld+4]=' ';
			cores[gatoVet[i].yOld+2][gatoVet[i].xOld+5]=' ';
			cores[gatoVet[i].yOld+2][gatoVet[i].xOld+6]=' ';


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
		if (gatoVet[i].estado==2){
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



			cores[gatoVet[i].yOld][gatoVet[i].xOld]=' ';
			cores[gatoVet[i].yOld][gatoVet[i].xOld+1]=' ';
			cores[gatoVet[i].yOld][gatoVet[i].xOld+2]=' ';
			cores[gatoVet[i].yOld][gatoVet[i].xOld+3]=' ';
			cores[gatoVet[i].yOld][gatoVet[i].xOld+4]=' ';
			cores[gatoVet[i].yOld][gatoVet[i].xOld+5]=' ';
			cores[gatoVet[i].yOld][gatoVet[i].xOld+6]=' ';

			cores[gatoVet[i].yOld+1][gatoVet[i].xOld]=' ';
			cores[gatoVet[i].yOld+1][gatoVet[i].xOld+1]=' ';
			cores[gatoVet[i].yOld+1][gatoVet[i].xOld+2]=' ';
			cores[gatoVet[i].yOld+1][gatoVet[i].xOld+3]=' ';
			cores[gatoVet[i].yOld+1][gatoVet[i].xOld+4]=' ';
			cores[gatoVet[i].yOld+1][gatoVet[i].xOld+5]=' ';
			cores[gatoVet[i].yOld+1][gatoVet[i].xOld+6]=' ';

			cores[gatoVet[i].yOld+2][gatoVet[i].xOld]=' ';
			cores[gatoVet[i].yOld+2][gatoVet[i].xOld+1]=' ';
			cores[gatoVet[i].yOld+2][gatoVet[i].xOld+2]=' ';
			cores[gatoVet[i].yOld+2][gatoVet[i].xOld+3]=' ';
			cores[gatoVet[i].yOld+2][gatoVet[i].xOld+4]=' ';
			cores[gatoVet[i].yOld+2][gatoVet[i].xOld+5]=' ';
			cores[gatoVet[i].yOld+2][gatoVet[i].xOld+6]=' ';

			gatoVet[i].estado=0; //muda para o estado 0 para nao ficar printando espaços em branco após a morte do inimigo

		}

		if (abelhaVet[i].estado==1)
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



			cores[abelhaVet[i].yOld][abelhaVet[i].xOld]=' ';
			cores[abelhaVet[i].yOld][abelhaVet[i].xOld+1]=' ';
			cores[abelhaVet[i].yOld][abelhaVet[i].xOld+2]=' ';
			cores[abelhaVet[i].yOld][abelhaVet[i].xOld+3]=' ';
			cores[abelhaVet[i].yOld][abelhaVet[i].xOld+4]=' ';
			cores[abelhaVet[i].yOld][abelhaVet[i].xOld+5]=' ';
			cores[abelhaVet[i].yOld][abelhaVet[i].xOld+6]=' ';

			cores[abelhaVet[i].yOld+1][abelhaVet[i].xOld]=' ';
			cores[abelhaVet[i].yOld+1][abelhaVet[i].xOld+1]=' ';
			cores[abelhaVet[i].yOld+1][abelhaVet[i].xOld+2]=' ';
			cores[abelhaVet[i].yOld+1][abelhaVet[i].xOld+3]=' ';
			cores[abelhaVet[i].yOld+1][abelhaVet[i].xOld+4]=' ';
			cores[abelhaVet[i].yOld+1][abelhaVet[i].xOld+5]=' ';
			cores[abelhaVet[i].yOld+1][abelhaVet[i].xOld+6]=' ';

			cores[abelhaVet[i].yOld+2][abelhaVet[i].xOld]=' ';
			cores[abelhaVet[i].yOld+2][abelhaVet[i].xOld+1]=' ';
			cores[abelhaVet[i].yOld+2][abelhaVet[i].xOld+2]=' ';
			cores[abelhaVet[i].yOld+2][abelhaVet[i].xOld+3]=' ';
			cores[abelhaVet[i].yOld+2][abelhaVet[i].xOld+4]=' ';
			cores[abelhaVet[i].yOld+2][abelhaVet[i].xOld+5]=' ';
			cores[abelhaVet[i].yOld+2][abelhaVet[i].xOld+6]=' ';

			cores[abelhaVet[i].yOld+3][abelhaVet[i].xOld]=' ';
			cores[abelhaVet[i].yOld+3][abelhaVet[i].xOld+1]=' ';
			cores[abelhaVet[i].yOld+3][abelhaVet[i].xOld+2]=' ';
			cores[abelhaVet[i].yOld+3][abelhaVet[i].xOld+3]=' ';
			cores[abelhaVet[i].yOld+3][abelhaVet[i].xOld+4]=' ';
			cores[abelhaVet[i].yOld+3][abelhaVet[i].xOld+5]=' ';
			cores[abelhaVet[i].yOld+3][abelhaVet[i].xOld+6]=' ';



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
		if (abelhaVet[i].estado==2){
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



			cores[abelhaVet[i].yOld][abelhaVet[i].xOld]=' ';
			cores[abelhaVet[i].yOld][abelhaVet[i].xOld+1]=' ';
			cores[abelhaVet[i].yOld][abelhaVet[i].xOld+2]=' ';
			cores[abelhaVet[i].yOld][abelhaVet[i].xOld+3]=' ';
			cores[abelhaVet[i].yOld][abelhaVet[i].xOld+4]=' ';
			cores[abelhaVet[i].yOld][abelhaVet[i].xOld+5]=' ';
			cores[abelhaVet[i].yOld][abelhaVet[i].xOld+6]=' ';

			cores[abelhaVet[i].yOld+1][abelhaVet[i].xOld]=' ';
			cores[abelhaVet[i].yOld+1][abelhaVet[i].xOld+1]=' ';
			cores[abelhaVet[i].yOld+1][abelhaVet[i].xOld+2]=' ';
			cores[abelhaVet[i].yOld+1][abelhaVet[i].xOld+3]=' ';
			cores[abelhaVet[i].yOld+1][abelhaVet[i].xOld+4]=' ';
			cores[abelhaVet[i].yOld+1][abelhaVet[i].xOld+5]=' ';
			cores[abelhaVet[i].yOld+1][abelhaVet[i].xOld+6]=' ';

			cores[abelhaVet[i].yOld+2][abelhaVet[i].xOld]=' ';
			cores[abelhaVet[i].yOld+2][abelhaVet[i].xOld+1]=' ';
			cores[abelhaVet[i].yOld+2][abelhaVet[i].xOld+2]=' ';
			cores[abelhaVet[i].yOld+2][abelhaVet[i].xOld+3]=' ';
			cores[abelhaVet[i].yOld+2][abelhaVet[i].xOld+4]=' ';
			cores[abelhaVet[i].yOld+2][abelhaVet[i].xOld+5]=' ';
			cores[abelhaVet[i].yOld+2][abelhaVet[i].xOld+6]=' ';

			cores[abelhaVet[i].yOld+3][abelhaVet[i].xOld]=' ';
			cores[abelhaVet[i].yOld+3][abelhaVet[i].xOld+1]=' ';
			cores[abelhaVet[i].yOld+3][abelhaVet[i].xOld+2]=' ';
			cores[abelhaVet[i].yOld+3][abelhaVet[i].xOld+3]=' ';
			cores[abelhaVet[i].yOld+3][abelhaVet[i].xOld+4]=' ';
			cores[abelhaVet[i].yOld+3][abelhaVet[i].xOld+5]=' ';
			cores[abelhaVet[i].yOld+3][abelhaVet[i].xOld+6]=' ';			

			abelhaVet[i].estado=0; //muda para o estado 0 para nao ficar printando espaços em branco após a morte do inimigo
		}
	}
}

void tela_menu (){
    char list[5][7] = { "ISAAC" };
    char item[7];
    int i = 0;
    char c = 'c';
    int yMax, xMax;
    getmaxyx(stdscr,yMax,xMax);
	start_color();
    WINDOW *window = newwin( yMax/3,xMax/4 ,yMax/3 ,xMax/3); // create a new window
    box( window, 0, 0 ); // sets default borders for the window
     
	// now print all the menu items and highlight the first one
	wattron( window, A_BOLD ); // highlights the first item.
	mvwprintw(window,1, 8, "THE BINDING OF ISAAC");
    for( i=0; i<2; i++ ) {
        if( i == 0 ) 
            wattron( window, A_STANDOUT ); // highlights the first item.
        else
            wattroff( window,A_STANDOUT);
        sprintf(item, "%-5s",  list[i]);
        mvwprintw( window,3, 11 + (7 * i), "%s", item );
    }
    printf("\n");
    mvwprintw(window,11,  1, "HP");
 	mvwprintw(window,12, 1, "Strength");
 	mvwprintw(window,13, 1, "Speed");
 	mvwprintw(window,14, 1, "Luck");


    mvwprintw(window,4, 11, "     ");
  	mvwprintw(window,5, 11, "     ");
 	mvwprintw(window,6, 11, "(;_;)");
 	mvwprintw(window,7, 11, "__|__");
 	mvwprintw(window,8, 11, "  |  ");
 	mvwprintw(window,9, 11, " / \\ ");

 	mvwprintw(window,11,  12, "3");
 	mvwprintw(window,12, 12, "3.5");
 	mvwprintw(window,13, 12, "1.0");
 	mvwprintw(window,14, 12, "0");
    wrefresh( window ); // update the terminal screen
 
    noecho(); // disable echoing of characters on the screen
    keypad( window, TRUE ); // enable keyboard input for the window.
    curs_set(0); // hide the default screen cursor.
    
     
    while(c  == 'c'){
    	c = getchar();

    }
 	
    delwin( window);
}

void contPontos(int clock, personagem_t *isaac){
	if (clock % 300 == 0)
	{
		isaac->points++;
	}
}

void salvarPontos(personagem_t isaac){
	FILE *pontuacao = fopen("SCORE_ISAAC.txt","a");
	if (!pontuacao)
	{
		perror("Erro ao salvar pontuação.");
	}

  	time_t rawtime;
	struct tm * timeinfo;

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );



	fprintf(pontuacao, "################# %02d/%02d/%d - %02d:%02d:%02d ##################\n",timeinfo->tm_mday,timeinfo->tm_mon+1,timeinfo->tm_year+1900,timeinfo->tm_hour,timeinfo->tm_min,timeinfo->tm_sec);
	fprintf(pontuacao, "#\tVIDAS: %d                                             #\n",isaac.hearts );
	fprintf(pontuacao, "#\tPONTUAÇÃO: %04ld                                      #\n",isaac.points );
	fprintf(pontuacao, "##########################################################\n\n");
}