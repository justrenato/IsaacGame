#include <stdio.h>
#include <stdlib.h>

#define LIN 50
#define COL 160
#define ROOMS 10

#define FRIEND 1
#define FOE 0
#define STATIC 2

#define INTEIRO 1
#define MEIO 0

#define DIREITA 1
#define ESQUERDA 2
#define CIMA 3
#define BAIXO 4
#define PARADO 0

#define PEDRA 1 //destroi
#define POO 0

#define BOMBA 1 //hit
#define TEARS 0
#define NADA 2

typedef struct moving_object_t{
	int tipo; //friend, foe
	int hp;
	int forca;
	int direcao;
	int tamX;
	int tamY;
	int cordX;
	int cordY;
	void (*atualiza_lugar)(int *cordX, int *cordY, int *direcao);


}moving_object;

typedef struct static_object_t{
	int tipo;
	int destroi;
	int hit;
	int(*sorteia_item)(int *destroi, int *hit);
	
}static_object;

int sorteia(int *destroi, int *hit){
	int x;	
	
	if (*destroi == PEDRA && *hit ==BOMBA){
		x = rand()%3;
		return x;
	}
	else if (*destroi == POO && (*hit == BOMBA || *hit == TEARS)){
				x = rand()%3;
		return x;		
	}
	else
		return 0;

}

void movimento(int *cordX, int *cordY, int *direcao){
	if(direcao){
		if (DIREITA)
			cordX ++;
		if (ESQUERDA)
			cordX --;
		if (CIMA)
			cordY ++;
		if (BAIXO)
			cordY --;
	}	
}

int main(){
	
	int **matrix ;
	int i;
	
	//aloca espaço para mapa 
	matrix = malloc (LIN * sizeof (int*) * ROOMS) ;
	for (i=0; i < LIN; i++)
  		matrix[i] = malloc (COL * sizeof (int) * ROOMS) ;

  	// depois fazer essas coisas num vetor;
	moving_object gapper;
	gapper.tipo = FOE;
	gapper.hp = 90;
	gapper.forca = MEIO;
	gapper.tamX = 5;
	gapper.tamY = 4;	
	gapper.direcao = DIREITA; // isso depois muda 
	gapper.atualiza_lugar = movimento;
	gapper.atualiza_lugar(&gapper.cordX, &gapper.cordY, &gapper.direcao);

	static_object poo;
	poo.tipo = STATIC;
	poo.destroi = POO;
	poo.hit = NADA;
	poo.sorteia_item = sorteia;
	poo.sorteia_item(&poo.destroi,&poo.hit);
}