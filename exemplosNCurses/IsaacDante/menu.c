#include <curses.h>
#include <menu.h>
#include <stdlib.h>
#include <string.h> 
#include <ncurses.h>
#include "character_struct.h"


#define LOGIN_BOX_WIDHT 35	
#define LOGIN_BOX_HEIGHT 16
#define OFFSET_X 5
#define OFFSET_Y  26

int main(int argc, char **argv){
	character persona; 
	
    WINDOW *window, *window1;
    char list[5][7] = { "ISAAC" };
    char item[7];
    int ch, i = 0;
 
    initscr(); // initialize Ncurses
    window = newwin( LOGIN_BOX_HEIGHT,LOGIN_BOX_WIDHT ,OFFSET_X , OFFSET_Y); // create a new window
    box( window, 0, 0 ); // sets default borders for the window
     
	// now print all the menu items and highlight the first one
	mvwprintw(window,1, 8, "THE BINDING OF ISAAC");
    for( i=0; i<2; i++ ) {
        if( i == 0 ) 
            wattron( window, A_STANDOUT ); // highlights the first item.
        else
            wattroff( window, A_STANDOUT );
        sprintf(item, "%-5s",  list[i]);
        mvwprintw( window,3, 11 + (7 * i), "%s", item );
    }
    printf("\n");
    mvwprintw(window,11,  1, "HP");
 	mvwprintw(window,12, 1, "Strength");
 	mvwprintw(window,13, 1, "Speed");
 	mvwprintw(window,14, 1, "Luck");


    mvwprintw(window,4, 11, "     ");
  	mvwprintw(window,5, 11, "     ");
 	mvwprintw(window,6, 11, "(;_;)");
 	mvwprintw(window,7, 11, "__|__");
 	mvwprintw(window,8, 11, "  |  ");
 	mvwprintw(window,9, 11, " / \\ ");

 	mvwprintw(window,11,  12, "6");
 	mvwprintw(window,12, 12, "3.5");
 	mvwprintw(window,13, 12, "1.0");
 	mvwprintw(window,14, 12, "0");
    wrefresh( window ); // update the terminal screen
 
    i = 0;
    noecho(); // disable echoing of characters on the screen
    keypad( window, TRUE ); // enable keyboard input for the window.
    curs_set(0); // hide the default screen cursor.
     
       // get the input
    while(( ch = wgetch(window)) != 32){ 
         
                // right qpad with spaces to make the items appear with even width.
            sprintf(item, "%-5s",  list[i]); 
            mvwprintw( window, 3, 11 + (7 *i), "%s", item ); 
              // use a variable to increment or decrement the value based on the input.
            switch( ch ) {
                case KEY_RIGHT:
                            i--;
                            i = ( i<0 ) ? 1 : i;
                            break;
                case KEY_LEFT:
                            i++;
                            i = ( i>1 ) ? 0 : i;
                            break;
            }
            // now highlight the next item in the list.
            wattron( window, A_STANDOUT );
             
            sprintf(item, "%-5s",  list[i]);
            mvwprintw( window, 3, 11 + (7 *i), "%s", item);
            wattroff( window, A_STANDOUT );
    }
 	
    delwin( window);
    // endwin();

    // if (!strcmp(list[i],"ISAAC") ) {
    // 	persona.hp = 6;
    // 	persona.strength = 35;
    // 	persona.speed = 10;
    // 	persona.luck = 0;
    // }
    // else{
    // 	persona.hp = 2;
    // 	persona.strength = 49;
    // 	persona.speed = 12;
    // 	persona.luck = 0;
    // }

 	sleep(1);
    endwin();
    return 0;
}