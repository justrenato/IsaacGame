#include<stdlib.h>
#include<stdio.h>
#include<ncurses.h>
#include<unistd.h>

intmain(){
	Game *game;
	game = menu_creen();
	game = start_game();
	start_screen();

	while(!EndGame(game)){
		read_mov(game);
		read_tears(game);
		print_screen(game);
		refresh_game(game);
		usleep(1000);
		game->gtime++
	}
	print_end(game);
	killgame(game);
	killscreen();

	return 0;
}