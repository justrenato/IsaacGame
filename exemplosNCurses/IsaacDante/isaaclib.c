#include<stdio.h>
#include<stdlib.h>

void read_mov(Game *game){
	switch(getch()){
		case('a'): //esquerda
			game->mov = 1;
			break;
		case('d'):	//direita
			game->mov = -1;
		case('w'):	//cima
			game->mov = 2;
		case('s'):	//baixo
			game->mov = -2;
		default:	//não move
			game->mov = 0;
	}
}


void read_tears(Game *game){
	switch(getch()){
		case(37): //esquerda
			game->tears = 1;
			break;
		case(39):	//direita
			game->tears = -1;
		case(38):	//cima
			game->tears = 2;
		case(40):	//baixo
			game->tears = -2;
		default:	//não atira
			game->tears = 0;
	}
}

