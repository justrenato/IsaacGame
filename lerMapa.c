#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <ncurses.h>

#define COLMAX 158+1
#define LINMAX 45
#define ALT_SCORE 3

void desenharBordas(WINDOW *janela) {
  // box( janela, 0, 0 ); // desenha as bordas da janela indicada
}

char **lerMapa(char **mapa,char *mapaNome){ //matriz q vai guardar o mapa, nome do arquivo a ser lido
	// char c;

	// FILE *mapaArq = fopen(mapaNome,"r"); //abro o arquivo do mapa
	// if (!mapaArq){
 // 		endwin(); //finaliza o ncurses para printar o erro
	// 	perror("Arquivo nao aberto: "); //saber se arquivo foi aberto
	// 	exit(1);
	// }

	// mapa = malloc (LINMAX * sizeof(int*)); // aloca espaço de memoria para a matriz do mapa
	// for (int i = 0; i < LINMAX; ++i)
	// {
	// 	mapa[i] = malloc (COLMAX * sizeof(int));
	// }

 //  	for (int i = 0; i < LINMAX; ++i)//le os caracteres do arquivo e grava na matriz
	// {
	// 	for (int j = 0; j < COLMAX; ++j)
	// 	{
	// 		c=getc(mapaArq);
	// 		if (c=='\n')
	// 		{
	// 			c='\0';
	// 		}
	// 		mapa[i][j] = c;
	// 	}
	// }

	// return(mapa);
}

int yMapa(){
	// int yAtual,y;
	// yAtual = getmaxy(stdscr); //pega o max x e y da janela atual no terminal
	// if (yAtual < LINMAX +2){
	// 	y=1;
	// }
	// else{
	// 	y=(((yAtual-2)- LINMAX)/2);
	// }
	// return y;
}

int xMapa(){
	// int xAtual,x;
	// xAtual = getmaxx(stdscr); //pega o max x e y da janela atual no terminal
	// if(xAtual<COLMAX+1){
	// 	x=1;
	// }
	// else {
	// 	x = (xAtual-(COLMAX-1))/2;
	// }
	// return x;
}

void imprimeMapa(char **mapa, WINDOW *janela){
  //   for (int i = 0; i < LINMAX; ++i)
  //   {
		// mvwprintw(janela, yMapa()+i, xMapa(), "%s",mapa[i]);
  //   }
}

void infoScore(WINDOW *janela, int yIsaac, int xIsaac){
	// int xAtual, yAtual;
	// getmaxyx(stdscr, yAtual, xAtual); 
	// mvwprintw(janela, 1, 1, "Hearts:%d  Coins:00  Keys:00 | xmouse: %d ymouse: %d",55,xAtual,yAtual);
}

void imprimirIsaac(int x, int y, WINDOW *janela,char** mapa){
	// /*cabeça*/
	// mapa[y][x]='(';
	// mapa[y][x+1]=';';
	// mapa[y][x+2]='_';
	// mapa[y][x+3]=';';
	// mapa[y][x+4]=')';

	// /*braços*/
	// mapa[y+1][x]='_';
	// mapa[y+1][x+1]='_';
	// mapa[y+1][x+2]='|';
	// mapa[y+1][x+3]='_';
	// mapa[y+1][x+4]='_';

	// /*tronco*/
	// mapa[y+2][x+2]='|';

	// /*pernas*/
	// mapa[y+3][x+1]='/';
	// mapa[y+3][x+2]=' ';
	// mapa[y+3][x+3]='\\';
}

void apagarIsaac(int x, int y, WINDOW *janela,char** mapa){

	// /*cabeça*/
	// mapa[y][x]=' ';
	// mapa[y][x+1]=' ';
	// mapa[y][x+2]=' ';
	// mapa[y][x+3]=' ';
	// mapa[y][x+4]=' ';

	// /*braços*/
	// mapa[y+1][x]=' ';
	// mapa[y+1][x+1]=' ';
	// mapa[y+1][x+2]=' ';
	// mapa[y+1][x+3]=' ';
	// mapa[y+1][x+4]=' ';

	// /*tronco*/
	// mapa[y+2][x+2]=' ';

	// /*pernas*/
	// mapa[y+3][x+1]=' ';
	// mapa[y+3][x+2]=' ';
	// mapa[y+3][x+3]=' ';
}

char ColisaoIsaac(int xIsaac,int yIsaac){
	// char colisao;
	// if (!(yIsaac+yMapa()<LINMAX+yMapa()-5))
	// {
	// 	colisao='b';
	// }

	// if (!(yIsaac+yMapa() >yMapa()+1) )
	// {
	// 	colisao='c';
	// }

	// if(!(xIsaac+xMapa()>xMapa()+2)){
	// 	colisao='e';
	// }
	// if(!(xIsaac+xMapa() <COLMAX+xMapa()-7)){
	// 	colisao='d';
	// }

	// return colisao;
}

int main(int argc, char *argv[]) {
	/*#################################### INICIALIZAÇÕES AQUI ####################################*/
	int xIsaac=90,yIsaac=20;
	int ch;
	int gameOver = 0; 
	int xAtual, yAtual, novoX, novoY; //cordenadas

	char *mapa1 = "map.h";
	char **mapa = NULL;
  
	mapa = lerMapa(mapa,mapa1);

	initscr(); //iniciar ncurses

	getmaxyx(stdscr, yAtual, xAtual); //pega o max x e y da janela atual no terminal
	WINDOW *janelaScore = newwin(ALT_SCORE, xAtual, 0, 0); //altura,largura,posX,posY
	WINDOW *janelaJogo = newwin(yAtual - ALT_SCORE, xAtual, ALT_SCORE, 0);	

    start_color();
	noecho();
    keypad(stdscr, TRUE ); // enable keyboard input for the window.

  	mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
  	printf("\033[?1003h\n"); // Makes the terminal report mouse movement events


	curs_set(0);
	cbreak();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
  	attron(COLOR_PAIR(1));

	/*#################################### IMPRESSÕES AQUI ####################################*/

	/*duas bordas*/
	desenharBordas(janelaScore);
	desenharBordas(janelaJogo);
    
	/*mapa mais score*/
    infoScore(janelaScore, yIsaac, xIsaac);
	imprimeMapa(mapa,janelaJogo);
	imprimirIsaac(xIsaac,yIsaac,janelaJogo,mapa);





/*COLAR CODIGO DO MOUSE DO SCRIPT TESTE*/





 //  while(!gameOver){
    
 //    getmaxyx(stdscr, novoY, novoX);

 //    /*teste para ver se o terminal foi */
 //    if (novoY != yAtual || novoX != xAtual){
 //      xAtual = novoX;
 //      yAtual = novoY;

 //      wresize(janelaScore, ALT_SCORE, xAtual);
 //      wresize(janelaJogo, yAtual - ALT_SCORE, xAtual);
 //      mvwin(janelaJogo, yAtual + ALT_SCORE, 0);

 //      wclear(stdscr);
 //      wclear(janelaJogo);
 //      wclear(janelaScore);

 //      desenharBordas(janelaJogo);
 //      desenharBordas(janelaScore);
	//   imprimeMapa(mapa,janelaJogo);
 //      imprimirIsaac(xIsaac,yIsaac,janelaJogo,mapa);
 //    }

 //    // infos score 
 //    infoScore(janelaScore, yIsaac, xIsaac);

 //    // mapa na tela
	// imprimeMapa(mapa,janelaJogo);
	// imprimirIsaac(xIsaac,yIsaac,janelaJogo,mapa);

 //    // atualiza janelas
 //    wrefresh(janelaScore);
 //    wrefresh(janelaJogo);

 //    apagarIsaac(xIsaac,yIsaac,janelaJogo,mapa);

 //    char buffer[512];
 //    size_t max_size = sizeof(buffer);


 //    ch = wgetch(janelaJogo);
	// MEVENT event;
 //    switch( ch ) {

	//     case 'd':
	//     	if (ColisaoIsaac(xIsaac,yIsaac)!='d'){
	//     		xIsaac++;
	//     	}
	//         break;

	//     case 'a':
	//     	if (ColisaoIsaac(xIsaac,yIsaac)!='e'){
	//     		xIsaac--;
	//     	}
	//         break;

	//     case 's':
	//     	if (ColisaoIsaac(xIsaac,yIsaac)!='b')
	//     	{
	//     		yIsaac++;
	//     	}
	//         break;

	//     case 'w':
	//     	if (ColisaoIsaac(xIsaac,yIsaac)!='c')
	//     	{
	//     		yIsaac--;
	//     	}
	//         break;
 //   	}
	// mvwprintw(janelaScore, 1, 1, "ch: %08lx ",ch);


 //    if (ch == KEY_MOUSE){
	//     if (1) {
	// 		mvwprintw(janelaScore, 1, 1, "xmouse: %d ymouse: %d",event.x,event.y);
	//         snprintf(buffer, max_size, "Mouse at row=%d, column=%d bstate=0x%08lx",
	//                  event.y, event.x, event.bstate);
	// 		}    
	// }

	// 	// infos score 
	// 	infoScore(janelaScore, yIsaac, xIsaac);

	// 	// mapa na tela
	// 	imprimeMapa(mapa,janelaJogo);
	// 	imprimirIsaac(xIsaac,yIsaac,janelaJogo,mapa);

	// 	// atualiza janelas
	// 	wrefresh(janelaScore);
	// 	wrefresh(janelaJogo);

	// 	move(0, 0);
	// 	insertln();
	// 	addstr(buffer);
	// 	clrtoeol();
	// 	move(0, 0);
	// }

    printf("\033[?1003l\n"); // Disable mouse movement events, as l = low
  	endwin();
  return 0;
}