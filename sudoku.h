#ifndef _SUDOKU_H_
#define _SUDOKU_H_

#define SUDOKU_ROWS 13
#define SUDOKU_COLS 19

void board_draw(WINDOW *win, char *board);

int board_runchecks(char *board, int row, int col, char num);

WINDOW * sudokuwin_create(int start_y, int start_x);

#endif
