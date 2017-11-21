#ifndef __ISAACLIB__
#define __ISAACLIB__

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <ncurses.h>
#include <time.h>//preciso função para gerar aleatorios
#include <unistd.h>//preciso função sleep.

#define COLMAX 158+1
#define LINMAX 45
#define ALT_SCORE 3
#define DELAY 6000
#define TIRO '0'
#define MAXTIROS 10

typedef struct tiro_t {
	int x,y,d,estado;
	
	/*estado 0 - n atirado
	  estado 1 - atirado
	  estado 2 - acertou
	  estado 3 - limite*/

/*	direção 0 - cima
	direção 1 - baixo
	direção 2 - esquerda
	direção 3 - direita
	direção 4 - dir + cima
	direção 5 - dir + baixo
	direção 6 - esq + cima
	direção 7 - esq + baixo
	*/
} tiro_t;

void desenharBordas(WINDOW *janela) ;

char **lerMapa(char **mapa,char *mapaNome); 

int yMapa();

int xMapa();

void imprimeMapa(char **mapa, WINDOW *janela);

void infoScore(WINDOW *janela, int yIsaac, int xIsaac);

void imprimirIsaac(int x, int y, WINDOW *janela,char** mapa);

void teste_redimensao(int *xAtual, int *yAtual, WINDOW *janelaScore, WINDOW *janelaJogo, int xIsaac, int yIsaac, char **mapa);

void apagarIsaac(int x, int y, WINDOW *janela,char** mapa);

// void tiro(WINDOW *janelaJogo, WINDOW *janelaScore, MEVENT *event,int xIsaac,int yIsaac, int *oldMouseX, int *oldMouseY,char** mapa, tiro_t *tiros);

void attJanelas(WINDOW *janelaJogo, WINDOW *janelaScore, int xIsaac,int yIsaac,char** mapa);

void movimentacao(WINDOW *janelaJogo, WINDOW *janelaScore, int *xIsaac,int *yIsaac, char** mapa);

void geraInimigo(WINDOW *janelaJogo, char** mapa);

#endif