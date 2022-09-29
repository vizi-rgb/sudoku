#include "sudoku.h"
#include "solver.h"

/* Sudoku solver for 9x9 boards
   returns 1 if the solution is found 0 otherwise */
int solve(char *board, int row, int col) {
    // solver has filled the whole board with digits so the solution is found
    if (row == 8 && col == 9)
        return 1;

    // maximum column index is 8
    if (col == 9) {
        col = 0;
        row++;
    }

    // the digit is already in the cell => run solve() for the next cell
    if (board[row * BOARD_COLS + col] > '0')
        return solve(board, row, col + 1);

    // puts the digit in the cell [row][col] if it can be put there (naivly)
    for (int i = '1'; i <= '9'; i++) {
        if (board_runchecks(board, row, col, i) == 1) {
            board[row * BOARD_COLS + col] = i;

            if (solve(board, row, col + 1) == 1)
                return 1;
        } 
    }

    // the loop does not return 1 hence no digit can be put in cell [row][col]
    board[row * BOARD_COLS + col] = '0';
    return 0; 
}

int solveanim(Board *board, int row, int col, WINDOW *win) {
    board_draw(win, board);
    // solveanimr has filled the whole board with digits so the solution is found
    if (row == 8 && col == 9)
        return 1;

    // maximum column index is 8
    if (col == 9) {
        col = 0;
        row++;
    }

    // the digit is already in the cell => run solveanim() for the next cell
    if (board->content[row * BOARD_COLS + col] > '0')
        return solveanim(board, row, col + 1, win);

    // puts the digit in the cell [row][col] if it can be put there (naivly)
    for (int i = '1'; i <= '9'; i++) {
        if (board_runchecks(board->content, row, col, i) == 1) {
            board->content[row * BOARD_COLS + col] = i;

            if (solveanim(board, row, col + 1, win) == 1)
                return 1;
        } 
    }

    // the loop does not return 1 hence no digit can be put in cell [row][col]
    board->content[row * BOARD_COLS + col] = '0';
    return 0; 

}
