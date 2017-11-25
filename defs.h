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
#define DELAY 1000
#define TIRO '0'
#define MAXTIROS 10
#define MAXINIMIGOS 3 //maximo 3 inimigos de cada
#define TOTALINIMIGOS MAXINIMIGOS*2 //maximo de inimigos que estarão em jogo ao mesmo tempo 


#define LOGIN_BOX_WIDHT 35	
#define LOGIN_BOX_HEIGHT 16
#define OFFSET_X 5
#define OFFSET_Y  26

#define colMorcego 13
#define colGato 7
#define colAbelha 7

#define linGato 3
#define linAbelha 4

/*
estado 0 - n atirado
estado 1 - andando
estado 2 - acertou
estado 3 - limite

direção 0 - cima
direção 1 - baixo
direção 2 - esquerda
direção 3 - direita
direção 4 - dir + cima
direção 5 - dir + baixo
direção 6 - esq + cima
direção 7 - esq + baixo
*/
typedef struct tiro_t {
	int x,y,d,estado;
} tiro_t;


/*estado 0 - desaparece
  estado 1 - vivo*/
typedef struct morcego_t
{
	int xOld,yOld;
	int xNew,yNew;
	int estado;
	int vidas;
	char cor;
	char corpo[colMorcego];
} morcego_t;

/*estado 0 - desaparece
  estado 1 - vivo*/
typedef struct gato_t
{
	int xOld,yOld;
	int xNew,yNew;
	int estado;
	int vidas;
	char cor;
	char corpo[linGato][colMorcego];
} gato_t;

/*estado 0 - desaparece
  estado 1 - vivo*/
typedef struct abelha_t
{
	int xOld,yOld;
	int xNew,yNew;
	int estado;
	int vidas;
	char cor;
	char corpo[linAbelha][colAbelha];
} abelha_t;



void desenharBordas(WINDOW *janela);

char **inicCores(char **cores);

char **lerMapa(char **mapa,char *mapaNome); 

int yMapa();

int xMapa();

void imprimeMapa(char **mapa, char **cores, WINDOW *janela);

void infoScore(WINDOW *janela, int yIsaac, int xIsaac);

void imprimirIsaac(int x, int y, WINDOW *janela,char** mapa, char **cores);

void teste_redimensao(int *xAtual, int *yAtual, WINDOW *janelaScore, WINDOW *janelaJogo, int xIsaac, int yIsaac, char **mapa, char **cores);

void apagarIsaac(int x, int y, WINDOW *janela,char** mapa, char** cores);

void tiro(WINDOW *janelaJogo, WINDOW *janelaScore, MEVENT *event,int xIsaac,int yIsaac, int *oldMouseX, int *oldMouseY,char** mapa, tiro_t tiros[], char **cores, int clock, morcego_t morcegoVet[], gato_t gatoVet[], abelha_t abelhaVet[]);

void attJanelas(WINDOW *janelaJogo, WINDOW *janelaScore, int xIsaac,int yIsaac,char** mapa, char **cores);

void movimentacao(WINDOW *janelaJogo, WINDOW *janelaScore, int *xIsaac,int *yIsaac, char** mapa, char** cores);

void inicInimigo(WINDOW *janelaScore,morcego_t morcegoVet[], gato_t gatoVet[], abelha_t abelhaVet[]);

void geraInimigo(WINDOW *janelaJogo, char** mapa, char** cores, morcego_t morcegoVet[], gato_t gatoVet[], abelha_t abelhaVet[], int clock);

void tela_menu (WINDOW *window);

#endif