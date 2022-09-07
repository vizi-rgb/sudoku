#include <ncurses.h>
#include "sudoku.h" 

// LORF - LAST OR FIRST
#define LORF_ROW(R) (R == 0 || R == SUDOKU_ROWS - 1)
#define LORF_COL(C) (C == 0 || C == SUDOKU_COLS - 1)

void board_draw(WINDOW *win, char **board) {
    int board_elemnum = 0;
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
                    char *elem_ptr = board[board_elemnum++];
                    if (elem_ptr != NULL) 
                        waddch(win, *elem_ptr);
                }

            }
            /*
             else if (!LORF_ROW(r) && !LORF_COL(c)){
                int *elem_ptr = board[board_elemnum];

                if (c % 2) {
                    board_elemnum++;
                    if (elem_ptr != NULL)
                        waddch(win, *elem_ptr);
                } 
            }
            */
        }
    } 

    wrefresh(win);
}
