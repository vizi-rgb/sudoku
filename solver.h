#ifndef _SOLVER_H_
#define _SOLVER_H_ 

#include <ncurses.h>
#include "sudoku.h"

int solve(char *board, int row, int col);

int solveanim(Board *board, int row, int col, WINDOW *win);

#endif
