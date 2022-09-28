#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "sudoku.h" 
#include "control.h"

enum INFOPANEL {INFOPANEL_ROWS = 6, INFOPANEL_COLS = 30};

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
    Board *board = malloc(sizeof *board);

    memset(board->content, '0', sizeof *board->content * BOARD_ELEMS);
    memset(board->gencontent_pos, 0, 
            sizeof *board->gencontent_pos * BOARD_ELEMS);
    board_pregen(board);
    int keypressed;
    
    wprintw(info, "[Arrows] to navigate\n" 
                  "[1-9] to place the digit\n"
                  "[0] to erase the digit\n" 
                  "[G] to generate a board\n"
                  "[S] to solve the board\n"
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
