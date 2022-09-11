#include <stdlib.h>
#include <ncurses.h>
#include "sudoku.h" 
#include "control.h"

#define INFOPANEL_ROWS 3
#define INFOPANEL_COLS 20

void startup_config() {
    initscr();
    refresh();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
}

void update_displaypos(WINDOW *win, Position *pos) {
    int display_row = pos->row + (pos->row / 3) + 1;
    int display_col = pos->column * 2 + 1;

    wmove(win, display_row, display_col);
}

int main(void) {
    startup_config();

    WINDOW *info = newwin(INFOPANEL_ROWS, INFOPANEL_COLS, 0, 0);
    WINDOW *sudoku = sudokuwin_create(INFOPANEL_ROWS, 0);
    Position *pos = position_init(); 
    char *board[9*9] = {NULL}; 
    int keypressed;
    
    wprintw(info, "[Arrows] to navigate" 
                  "[Q] to quit");
    wrefresh(info);
    // initial draw
    wmove(sudoku, 1, 1);
    board_draw(sudoku, board);

    while ((keypressed = getch()) != 'q') {
        update_pos(pos, keypressed);
        update_displaypos(sudoku, pos);
        wrefresh(sudoku);

        add_num(pos, board, keypressed); 
        board_draw(sudoku, board);
    }

    endwin();
    return 0;
}
