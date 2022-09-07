#include <stdlib.h>
#include <ncurses.h>
#include "sudoku.h" 

void startup_config() {
    initscr();
    refresh();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
}

int main(void) {
    startup_config();
    WINDOW *win = newwin(SUDOKU_ROWS, SUDOKU_COLS, 0, 0);
    char *board[9*9] = {NULL}; 
    
    board_draw(win, board);
    getch();

    endwin();
    return 0;
}
