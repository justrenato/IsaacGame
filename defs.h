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
#define MAXTIROS 100
#define MAXINIMIGOS 3 //maximo 3 inimigos de cada
#define TOTALINIMIGOS MAXINIMIGOS*2 //maximo de inimigos que estarão em jogo ao mesmo tempo 


#define colMorcego 13
#define colGato 7
#define colAbelha 7

#define linGato 3
#define linAbelha 4

typedef struct personagem_t {
	int x,y,estado,hearts;
	long int points;
} personagem_t;


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

origem 0 - inimigo
origem 1 - personagem
*/
typedef struct tiro_t {
	int x,y,d,estado,origem;
} tiro_t;


/*estado 0 - n nasceu
  estado 1 - vivo
  estado 2 - morreu*/
typedef struct morcego_t
{
	int xOld,yOld;
	int xNew,yNew;
	int estado;
	int vidas;
	char cor;
	char corpo[colMorcego];
} morcego_t;

/*estado 0 - n nasceu
  estado 1 - vivo
  estado 2 - morreu*/
typedef struct gato_t
{
	int xOld,yOld;
	int xNew,yNew;
	int estado;
	int vidas;
	char cor;
	char corpo[linGato][colMorcego];
} gato_t;

/*estado 0 - n nasceu
  estado 1 - vivo
  estado 2 - morreu*/
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

void infoScore(WINDOW *janela, personagem_t isaac);

void imprimirIsaac(personagem_t isaac, WINDOW *janela,char** mapa, char **cores);

void teste_redimensao(int *xAtual, int *yAtual, WINDOW *janelaScore, WINDOW *janelaJogo, personagem_t isaac, char **mapa, char **cores);

void apagarIsaac(personagem_t isaac, WINDOW *janela,char** mapa, char** cores);

void tiro(WINDOW *janelaJogo, WINDOW *janelaScore, MEVENT *event,personagem_t *isaac, int *oldMouseX, int *oldMouseY,char** mapa, tiro_t tiros[], char **cores, int clock, morcego_t morcegoVet[], gato_t gatoVet[], abelha_t abelhaVet[]);

void attJanelas(WINDOW *janelaJogo, WINDOW *janelaScore,personagem_t isaac,char** mapa, char **cores);

void lerTeclado(WINDOW *janelaJogo, WINDOW *janelaScore, personagem_t* isaac, char** mapa, char** cores, int *gameOver);

void inicInimigo(WINDOW *janelaScore,morcego_t morcegoVet[], gato_t gatoVet[], abelha_t abelhaVet[]);

void geraInimigo(WINDOW *janelaJogo, char** mapa, char** cores, morcego_t morcegoVet[], gato_t gatoVet[], abelha_t abelhaVet[], int clock);

void tela_menu ();

void contPontosVidas(int clock, personagem_t *isaac, int *gameOver,WINDOW *janelaJogo, WINDOW *janelaScore);

void salvarPontos(personagem_t isaac);

#endif