#include <ncurses.h>
#include "sudoku.h" 

// LORF - LAST OR FIRST
#define LORF_ROW(R) (R == 0 || R == SUDOKU_ROWS - 1)
#define LORF_COL(C) (C == 0 || C == SUDOKU_COLS - 1)

// 1 - number is unique, 0 otherwise
static int check_col(char *board, int col, char num) {
    for (int i = 0; i < 9; i++) {
        if (board[i * 9 + col] == num)
            return 0;
    }

    return 1;
}

// 1 - number is unique, 0 otherwise
static int check_row(char *board, int row, char num) {
    for (int i = 0; i < 9; i++) {
        if (board[row * 9 + i] == num) 
            return 0;
    }

    return 1;
}

// 1 - number is unique, 0 otherwise
static int check_box(char *board, int row, int col, char num) {
    // left upper corner coordinates
    int pos[2] = {row/3 * 3, col/3 * 3};

    int elem = pos[0] * 9 + pos[1];


    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) 
            // i correlates to rows, while j correlates to columns
            if (board[elem + i*9 + j] == num)
                return 0;
    }

    return 1;
}

void board_draw(WINDOW *win, char *board) {
    int board_elemnum = 0;
    int start_pos[2]; 
    getyx(win, start_pos[0], start_pos[1]); 
    wborder(win, 0, 0, 0, 0, 0, 0, 0, 0);


    for (int r = 0; r < SUDOKU_ROWS; r++) {
        for (int c = 0; c < SUDOKU_COLS; c++) {
            wmove(win, r, c);
            
            // Border without corners
            if ( !(LORF_COL(c) && LORF_ROW(r)) && (LORF_ROW(r) || LORF_COL(c))) {

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
                    char elem = board[board_elemnum++];
                    if (elem != '0') 
                        waddch(win, elem);
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
