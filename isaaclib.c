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
    for (int i = 0; i < LINMAX; ++i)
    {
		mvwprintw(janela, yMapa()+i, xMapa(), "%s",mapa[i]);
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

char ColisaoIsaac(int xIsaac,int yIsaac){
	char colisao;
	if (!(yIsaac+yMapa()<LINMAX+yMapa()-5))
	{
		colisao='b';
	}

	if (!(yIsaac+yMapa() >yMapa()+1) )
	{
		colisao='c';
	}

	if(!(xIsaac+xMapa()>xMapa()+2)){
		colisao='e';
	}
	if(!(xIsaac+xMapa() <COLMAX+xMapa()-7)){
		colisao='d';
	}

	return colisao;
}

void movimentacao(WINDOW *janelaJogo, WINDOW*janelaScore, int *xIsaac,int *yIsaac, char** mapa){
	int ch;
    ch = wgetch(janelaJogo);

    switch( ch ) {
	    case 'd':
	    	if (ColisaoIsaac(*xIsaac,*yIsaac)!='d'){
    			apagarIsaac(*xIsaac,*yIsaac,janelaJogo,mapa);
	    		(*xIsaac)++;
	    	}
        break;
	    case 'a':
	    	if (ColisaoIsaac(*xIsaac,*yIsaac)!='e'){
    			apagarIsaac(*xIsaac,*yIsaac,janelaJogo,mapa);
	    		(*xIsaac)--;
	    	}
        break;
	    case 's':
	    	if (ColisaoIsaac(*xIsaac,*yIsaac)!='b')
	    	{
    			apagarIsaac(*xIsaac,*yIsaac,janelaJogo,mapa);
	    		(*yIsaac)++;
	    	}
        break;
	    case 'w':
	    	if (ColisaoIsaac(*xIsaac,*yIsaac)!='c')
	    	{
    			apagarIsaac(*xIsaac,*yIsaac,janelaJogo,mapa);
	    		(*yIsaac)--;
	    	}
        break;
   	}
}

void tiro(WINDOW *janelaJogo, WINDOW *janelaScore, MEVENT *event,int xIsaac,int yIsaac, int *oldMouseX, int *oldMouseY,char** mapa){
	int click=0;
	getmouse(event);
	int i=0;
    int j=0,y=0;
    int c=0,b=0,e=0,d=0;
	if ((event->y != 0 ) && (event->x != 0)) //como o programa seta em 0 as cordenadas sempre que le outra tecla, quando posição for diferente de 0x0 eu salvo ela.
	{
		*oldMouseX = event->x - xMapa();
		*oldMouseY = event->y- yMapa()-3;
		click = event->bstate; //se click==2 botao esquerdo pressionado.
	}
	mvwprintw(janelaScore, 1, 1, "                                                                                                            ");
	mvwprintw(janelaScore, 1, 1, "ymouse: %03d xmouse: %03d | yIsaac: %03d xIsaac: %03d -- cima:%d baixo:%d, esq:%d, dir:%d",*oldMouseY,*oldMouseX,yIsaac,xIsaac,c,b,e,d);

if ((*oldMouseY <= yIsaac - 10) &&  (*oldMouseX <= xIsaac -20))
{
	c=1;
	b=0;
	e=1;
	d=0;
}

if((*oldMouseY <= yIsaac - 10) && (*oldMouseX >= xIsaac + 20)){
	c=1;
	b=0;
	e=0;
	d=1;
}


if ((*oldMouseY >= yIsaac + 10) && (*oldMouseX <= xIsaac - 20))
{
	c=0;
	b=1;
	e=1;
	d=0;
}

if ((*oldMouseY >= yIsaac + 10) && (*oldMouseX >= xIsaac + 20))
{
	c=0;
	b=1;
	e=0;
	d=1;
}

if ((*oldMouseY >= yIsaac ) && (*oldMouseX >= xIsaac - 20) && (*oldMouseX <= xIsaac+20))
{
	c=0;
	b=1;
	e=0;
	d=0;
}

if ((*oldMouseY <= yIsaac ) && (*oldMouseX >= xIsaac - 20) && (*oldMouseX <= xIsaac+20))
{
	c=1;
	b=0;
	e=0;
	d=0;
}

if ((*oldMouseY >= yIsaac -10 ) && (*oldMouseY <= yIsaac + 10) && (*oldMouseX <= xIsaac))
{
	c=0;
	b=0;
	e=1;
	d=0;
}

if ((*oldMouseY >= yIsaac -10 ) && (*oldMouseY <= yIsaac + 10) && (*oldMouseX >= xIsaac))
{
	c=0;
	b=0;
	e=0;
	d=1;
}

	j=xIsaac;
	y=yIsaac;
	
	if (click==2)
	{
		beep();
		while ((j>2)&&(j<(COLMAX-8))&& ((y>yMapa()-2)&& y<LINMAX-1))
		{	

			if (e && !d && !c && !b) //esquerda
			{
				mapa[y][j-1]=' ';
				(j)--;
				mapa[y][j-1]='*';
				attJanelas(janelaJogo, janelaScore, xIsaac, yIsaac,mapa);
				usleep(DELAY);
			}

			if (!e && d && !c && !b) // direita
			{
				mapa[y][j+5]=' ';
				(j)++;
				mapa[y][j+5]='*';
				attJanelas(janelaJogo, janelaScore, xIsaac, yIsaac,mapa);
				usleep(DELAY);
			}

			if (!e && !d && c && !b) //cima
			{
				mapa[y-1][j]=' ';
				y--;
				mapa[y-1][j]='*';
				attJanelas(janelaJogo, janelaScore, xIsaac, yIsaac,mapa);
				usleep(DELAY);
			}

			if (!e && !d && !c && b) //baixo
			{
				mapa[y-1][j]=' ';
				y++;
				mapa[y-1][j]='*';
				attJanelas(janelaJogo, janelaScore, xIsaac, yIsaac,mapa);
				usleep(DELAY);
			}

			if (e && !d && c && !b) //esq+cima
			{
				mapa[y-1][j-1]=' ';
				y--;
				j--;
				mapa[y-1][j-1]='*';
				attJanelas(janelaJogo, janelaScore, xIsaac, yIsaac,mapa);
				usleep(DELAY);
			}

			if (!e && d && c && !b) //dir+cima
			{
				mapa[y-1][j-1]=' ';
				y--;
				j++;
				mapa[y-1][j-1]='*';
				attJanelas(janelaJogo, janelaScore, xIsaac, yIsaac,mapa);
				usleep(DELAY);
			}	

			if (e && !d && !c && b) //esq+baixo
			{
				mapa[y][j-1]=' ';
				y++;
				j--;
				mapa[y][j-1]='*';
				attJanelas(janelaJogo, janelaScore, xIsaac, yIsaac,mapa);
				usleep(DELAY);
			}			
			
			if (!e && d && !c && b) //dir+baixo
			{
				mapa[y][j+5]=' ';
				y++;
				j++;
				mapa[y][j+5]='*';
				attJanelas(janelaJogo, janelaScore, xIsaac, yIsaac,mapa);
				usleep(DELAY);
			}
	
		}
		
		mapa[y][j-1]=' ';//apagar os tiros ao fim do percurso
		mapa[y][j+5]=' ';
		mapa[y-1][j]=' ';
		mapa[y-1][j-1]=' ';
		flash();
	}
}