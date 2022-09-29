#include <stdlib.h>
#include <ncurses.h>
#include <string.h>
#include "sudoku.h" 
#include "control.h"
#include "solver.h"

enum INFOPANEL {INFOPANEL_ROWS = 7, INFOPANEL_COLS = 30}; 

int checkboard_usrinput(Board *board) {
    for (int i = 0; i < BOARD_ELEMS; i++) {
        if (board->gencontent_pos[i] != 1 && board->content[i] > '0')
            return 1;
    }

    return 0;
}

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

    board_clear(board);

    int keypressed;
    
    wprintw(info, "[Arrows] to navigate\n" 
                  "[1-9] to place the digit\n"
                  "[0] to erase the digit\n" 
                  "[C] to clear the board\n"
                  "[G] to generate a board\n"
                  "[S] to solve the board\n"
                  "[Q] to quit");
    wrefresh(info);
    // initial draw
    wmove(sudoku, 1, 1);
    board_draw(sudoku, board);

    while ((keypressed = getch()) != 'q') {
        switch (keypressed) {
            case KEY_UP: case KEY_DOWN: case KEY_LEFT: case KEY_RIGHT:
                update_pos(pos, keypressed);
                update_displaypos(sudoku, pos);
                wrefresh(sudoku);
                break;

            case '1': case '2': case '3': case '4': case '5':
            case '6': case '7': case '8': case '9': case '0':
                add_num(pos, board, keypressed);
                break;

            case 'c': case 'C':
                if (checkboard_usrinput(board) == 1)
                    board_clearusr(board);
                else 
                    board_clear(board);
                break;

            case 'g': case 'G':
                board_clear(board);
                board_pregen(board);
                break;

            case 's': case 'S':
                solve(board->content, 0, 0);
                //solveanim(board, 0, 0, sudoku);
                break;

            default:
                break;
        } 

        board_draw(sudoku, board);
    }

    endwin();
    free(pos);
    free(board);
    return 0;
}
