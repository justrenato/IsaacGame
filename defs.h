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
#define MAXINIMIGOS 7

typedef struct tiro_t {
	int x,y,d,estado;
	
	/*estado 0 - n atirado
	  estado 1 - andando
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


typedef struct morcego_t
{
	int x,y;
	int estado;
	int vidas;
	char cor;
	char corpo[13];

	corpo[0]='/';
	corpo[1]='\\';
	corpo[2]='/';
	corpo[3]='\\';
	corpo[4]='(';
	corpo[5]='o';
	corpo[6]='_';
	corpo[7]='o';
	corpo[8]=')';
	corpo[9]='/';
	corpo[10]='\\';
	corpo[11]='/';
	corpo[12]='\\';


	/*estado 0 - desaparece
	  estado 1 - vivo*/
	
} morcego_t;

typedef struct gato_t
{
	int x,y;
	int estado;
	int vidas;
	char cor;
	char corpo[3][7];

	corpo[0][0]=' ';
	corpo[0][1]='/';
	corpo[0][2]='\\';
	corpo[0][3]='_';
	corpo[0][4]='/';
	corpo[0][5]='\\';	
	corpo[0][6]=' ';	

	corpo[1][0]='(';
	corpo[1][1]=' ';
	corpo[1][2]='o';
	corpo[1][3]='.';
	corpo[1][4]='o';				
	corpo[1][5]=' ';				
	corpo[1][6]=')';

	corpo[2][0]=' ';
	corpo[2][1]='>';
	corpo[2][2]=' ';
	corpo[2][3]='^';
	corpo[2][4]=' ';
	corpo[2][5]='<';	
	corpo[2][6]=' ';	

	/*estado 0 - desaparece
	  estado 1 - vivo*/
} gato_t;

typedef struct abelha_t
{
	int x,y;
	int estado;
	int vidas;
	char cor;
	char corpo[4][7];

	cor[0][0]=' ';
	cor[0][1]=' ';
	cor[0][2]=' ';
	cor[0][3]='_';
	cor[0][4]='_';				
	cor[0][5]=' ';				
	cor[0][6]=' ';

	cor[1][0]=' ';
	cor[1][1]='_';
	cor[1][2]='/';
	cor[1][3]='_';
	cor[1][4]='_';				
	cor[1][5]=')';				
	cor[1][6]=' ';

	cor[2][0]='(';
	cor[2][1]='8';
	cor[2][2]='|';
	cor[2][3]=')';
	cor[2][4]='_';				
	cor[2][5]='}';				
	cor[2][6]='}';

	cor[3][0]=' ';
	cor[3][1]='`';
	cor[3][2]='\\';
	cor[3][3]='_';
	cor[3][4]='_';				
	cor[3][5]=')';				
	cor[3][6]=' ';
	/*estado 0 - desaparece
	  estado 1 - vivo*/
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

void apagarIsaac(int x, int y, WINDOW *janela,char** mapa);

void tiro(WINDOW *janelaJogo, WINDOW *janelaScore, MEVENT *event,int xIsaac,int yIsaac, int *oldMouseX, int *oldMouseY,char** mapa, tiro_t tiros[], char **cores, inimigo_t inimigos[]);

void attJanelas(WINDOW *janelaJogo, WINDOW *janelaScore, int xIsaac,int yIsaac,char** mapa, char **cores);

void movimentacao(WINDOW *janelaJogo, WINDOW *janelaScore, int *xIsaac,int *yIsaac, char** mapa);

void geraInimigo(WINDOW *janelaJogo, char** mapa, char **cores, inimigo_t inimigos[]);

#endif