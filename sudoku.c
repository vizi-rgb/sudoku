#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sudoku.h"  // SUDOKU_ROWS, SUDOKU_COLS, BOARD_ROWS COLS AND ELEMS

// LORF - LAST OR FIRST
#define LORF_ROW(R) (R == 0 || R == SUDOKU_ROWS - 1)
#define LORF_COL(C) (C == 0 || C == SUDOKU_COLS - 1)

// 1 - number is unique, 0 otherwise
static int check_col(char *board, int col, char num) {
    for (int i = 0; i < BOARD_ROWS ; i++) {
        if (board[i * BOARD_COLS + col] == num)
            return 0;
    }

    return 1;
}

// 1 - number is unique, 0 otherwise
static int check_row(char *board, int row, char num) {
    for (int i = 0; i < BOARD_COLS; i++) {
        if (board[row * BOARD_COLS + i] == num) 
            return 0;
    }

    return 1;
}

// 1 - number is unique, 0 otherwise
static int check_box(char *board, int row, int col, char num) {
    // left upper corner coordinates
    int pos[2] = {row/3 * 3, col/3 * 3};

    int elem = pos[0] * BOARD_COLS + pos[1];


    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) 
            // i correlates to rows, while j correlates to columns
            if (board[elem + (i * BOARD_COLS) + j] == num)
                return 0;
    }

    return 1;
}

void board_draw(WINDOW *win, Board *board) {
    int board_elemnum = 0;
    int start_pos[2]; 
    getyx(win, start_pos[0], start_pos[1]); 
    wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);


    for (int r = 0; r < SUDOKU_ROWS; r++) { // row
        for (int c = 0; c < SUDOKU_COLS; c++) { // col
            wmove(win, r, c);
            
            // Border without corners
            if ( !(LORF_COL(c) && LORF_ROW(r)) &&
                     (LORF_ROW(r) || LORF_COL(c))) {

                if (LORF_COL(c) && !(r % 4)) 
                    waddch(win, c == 0 ? ACS_LTEE : ACS_RTEE);
                else if (LORF_ROW(r) && !(c % 6))
                    waddch(win, r == 0 ? ACS_TTEE : ACS_BTEE);

            // Inside
            } else if (!(LORF_COL(c) && LORF_ROW(r))) {

                if (!(c % 6) && !(r % 4))
                    waddch(win, ACS_PLUS);
                else if (!(c % 6)) 
                    waddch(win, ACS_VLINE);
                else if (!(r % 4)) 
                    waddch(win, ACS_HLINE);
                // Only sudoku numbers left to draw
                else if (c % 2) {
                    int pregenflag = board->gencontent_pos[board_elemnum];
                    char elem = board->content[board_elemnum++];
                    if (elem != '0') 
                        waddch(win, pregenflag ? (elem | A_PROTECT) : 
                                                 (unsigned) elem);
                    else 
                        waddch(win, ' ');
                }

            }
        }
    } 
    
    wmove(win, start_pos[0], start_pos[1]);
    wrefresh(win);
}

WINDOW * sudokuwin_create(int start_y, int start_x) {
    return newwin(SUDOKU_ROWS, SUDOKU_COLS, start_y, start_x);
}

// returns 1 if the number [num] can be put
// inside the cell in [row] row and [col] column
int board_runchecks(char *board, int row, int col, char num) {
    return check_col(board, col, num) &&
           check_row(board, row, num) &&
           check_box(board, row, col, num); 
}

void board_pregen(Board *board) {
    srand(time(NULL));
    const int n = 10;
    const int min_value = 19;

    // board initially contains from 19 to 40
    // values; <19; 40>
    // n = 10
    // min_value = 19
    int num  = rand() % n + min_value;

    for (int i = 0; i < num; i++) {
        int pos = rand() % BOARD_ELEMS;
        int value = rand() % 9 + 1; // from 1 to 9

        while (board->gencontent_pos[pos] == 1)
            pos = rand() % 81;

        int iteration = 0;
        while (board_runchecks(board->content, pos / BOARD_COLS,
                    pos % BOARD_COLS, value + '0') != 1 && iteration < 8) { 

            value = (value + iteration++) % 9 + 1;
        }

        if (iteration == BOARD_ROWS - 1) continue;

        board->gencontent_pos[pos] = 1;
        board->content[pos] = value + '0';
    }
}
