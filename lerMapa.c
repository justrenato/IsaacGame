#include "defs.h"

int main(int argc, char *argv[]) {
	/*#################################### INICIALIZAÇÕES PARA VARIAVEIS ####################################*/
	int xIsaac=90,yIsaac=20; // coordenadas Isaac
	int gameOver = 0; 
	int xAtual, yAtual; //dimensões janela
	int oldMouseX=1, oldMouseY=1;
	char *mapaArq1 = "map.h";
	char **mapa = NULL; //matriz que sera o mapa
	char **cores = NULL; //matriz de cores
	srand(time(NULL)); //gerar semente para aleatorio
  	long int clock=0;
  	tiro_t tiros[MAXTIROS];

  	morcego_t morcegoVet[MAXINIMIGOS];
  	gato_t gatoVet[MAXINIMIGOS];
  	abelha_t abelhaVet[MAXINIMIGOS];
	

	/*#################################### INICIALIZAÇÕES PARA NCURSES ####################################*/
	initscr(); //iniciar ncurses
	getmaxyx(stdscr, yAtual, xAtual); //pega o max x e y da janela atual no terminal
	WINDOW *janelaScore = newwin(ALT_SCORE, xAtual, 0, 0); //altura,largura,posX,posY
	WINDOW *janelaJogo = newwin(yAtual - ALT_SCORE, xAtual, ALT_SCORE, 0);	

	noecho();
    keypad(janelaJogo, TRUE ); // enable keyboard input for the window.
	nodelay (janelaJogo, TRUE) ; 
	curs_set(0);
	cbreak();
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
  	attron(COLOR_PAIR(1));
  	MEVENT event; //struct que guarda os eventos do mouse

 	mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);
  	printf("\033[?1003h\n"); // Makes the terminal report mouse movement events
  	mouseinterval(0.1);

	
	/*#################################### IMPRESSÕES PRÉ JOGO ####################################*/
	
  	tela_menu(janelaJogo);
	wclear(janelaJogo);
	mapa = lerMapa(mapa,mapaArq1);
	cores = inicCores(cores);
	inicInimigo(janelaScore,morcegoVet,gatoVet,abelhaVet);

	desenharBordas(janelaScore);
	desenharBordas(janelaJogo);
	attJanelas(janelaJogo, janelaScore, xIsaac, yIsaac,mapa, cores);
	
	/*####################################  INICIO JOGO ####################################*/
	while(!gameOver){
    
		teste_redimensao(&xAtual, &yAtual, janelaScore, janelaJogo, xIsaac, yIsaac, mapa, cores);
		
		attJanelas(janelaJogo, janelaScore, xIsaac, yIsaac,mapa, cores);

		movimentacao(janelaJogo, janelaScore, &xIsaac, &yIsaac, mapa);
		geraInimigo(janelaJogo, mapa,cores,morcegoVet,gatoVet,abelhaVet);
	    tiro(janelaJogo, janelaScore, &event,xIsaac,yIsaac,&oldMouseX,&oldMouseY,mapa,tiros,cores);
	   	attJanelas(janelaJogo, janelaScore, xIsaac, yIsaac,mapa, cores);


	   	usleep(DELAY);
	   	clock++;
	}

	endwin();
	return 0;
}