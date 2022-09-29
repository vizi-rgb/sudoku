#ifndef _SUDOKU_H_
#define _SUDOKU_H_

#include <ncurses.h> // WINDOW *

enum SUDOKU_DISPLAY {SUDOKU_ROWS = 13, SUDOKU_COLS = 19};

enum SUDOKU_BOARD {BOARD_ROWS = 9, BOARD_COLS = 9, BOARD_ELEMS = 81};

typedef struct Board {
    char content[BOARD_ELEMS];

    /* 
      Array contains 1 (true) or 0 (false) whether the value in the cell
      has been pregenerated
    */
    int gencontent_pos[BOARD_ELEMS]; 
} Board;

void board_draw(WINDOW *win, Board *board);

int board_runchecks(char *board, int row, int col, char num);

void board_pregen(Board *board);

WINDOW * sudokuwin_create(int start_y, int start_x);

void board_clear(Board *board);

void board_clearusr(Board *board);

#endif
