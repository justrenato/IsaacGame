#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#define COLMAX 160
#define LINMAX 50

void desenharBordas(WINDOW *screen) {
  box( screen, 0, 0 ); // sets default borders for the window
}

int main(int argc, char *argv[]) {
  int gameOver = 0;
  int xAtual, yAtual, novoX, novoY;
  int alturaScore = 3;

  initscr();
  noecho();
  curs_set(FALSE);

  // set up initial windows
  getmaxyx(stdscr, yAtual, xAtual);

  WINDOW *janelaPontos = newwin(alturaScore, xAtual, 0, 0);//altura,largura,posX,posY
  WINDOW *janelaJogo = newwin(yAtual - alturaScore, xAtual, alturaScore, 0);	

  desenharBordas(janelaJogo);
  desenharBordas(janelaPontos);

  while(!gameOver){
    getmaxyx(stdscr, novoY, novoX);

    if (novoY != yAtual || novoX != xAtual) {
      xAtual = novoX;
      yAtual = novoY;

      wresize(janelaPontos, alturaScore, xAtual);
      wresize(janelaJogo, yAtual - alturaScore, xAtual);
      mvwin(janelaJogo, yAtual + alturaScore, 0);

      wclear(stdscr);
      wclear(janelaJogo);
      wclear(janelaPontos);

      desenharBordas(janelaJogo);
      desenharBordas(janelaPontos);
    }

    // draw to our windows
    mvwprintw(janelaPontos, 1, 1, "Hearts:");
    mvwprintw(janelaPontos, 1, 8, "00");
    mvwprintw(janelaPontos, 1, 12, "Coins:");
    mvwprintw(janelaPontos, 1, 18, "00");
    mvwprintw(janelaPontos, 1, 22, "Keys:");
    mvwprintw(janelaPontos, 1, 27, "00");

    mvwprintw(janelaJogo, 1, 1, "janelaJogo");

    // refresh each window
    wrefresh(janelaJogo);
    wrefresh(janelaPontos);
  }

  endwin();

  return 0;
}

