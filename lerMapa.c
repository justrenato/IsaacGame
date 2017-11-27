#include "defs.h"

int main(){
	/*#################################### INICIALIZAÇÕES PARA VARIAVEIS ####################################*/
	personagem_t isaac;
	isaac.x=90; // coordenadas Isaac
	isaac.y=20;
	isaac.hearts = 3;
	isaac.points = -1;

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
  	mouseinterval(0.1);

	/*#################################### IMPRESSÕES PRÉ JOGO ####################################*/
	
	wclear(janelaJogo);
	mapa = lerMapa(mapa,mapaArq1);
	cores = inicCores(cores);
	inicInimigo(janelaScore,morcegoVet,gatoVet,abelhaVet);
  	tela_menu();

	desenharBordas(janelaScore);
	desenharBordas(janelaJogo);
	attJanelas(janelaJogo, janelaScore, isaac,mapa, cores);
	
	/*####################################  INICIO JOGO ####################################*/
  	printf("\033[?1003h\n"); // Makes the terminal report mouse movement events
	while(!gameOver){
    
		teste_redimensao(&xAtual, &yAtual, janelaScore, janelaJogo, isaac, mapa, cores);
		
		attJanelas(janelaJogo, janelaScore, isaac,mapa, cores);
		contPontosVidas(clock,&isaac,&gameOver,janelaJogo,janelaScore);
		lerTeclado(janelaJogo, janelaScore, &isaac, mapa, cores, &gameOver);
		geraInimigo(janelaJogo, mapa,cores,morcegoVet,gatoVet,abelhaVet,clock);
	    tiro(janelaJogo, janelaScore, &event,&isaac,&oldMouseX,&oldMouseY,mapa,tiros,cores,clock,morcegoVet,gatoVet,abelhaVet);
	   	attJanelas(janelaJogo, janelaScore, isaac,mapa, cores);


	   	usleep(DELAY);
	   	clock++;
	}

	printf("\033[?1003l\n"); // Disable mouse movement events, as l = low
	endwin();
	salvarPontos(isaac);
	return 0;
}