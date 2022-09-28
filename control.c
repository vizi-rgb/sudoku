#include <ncurses.h>
#include <stdlib.h>
#include "control.h"
#include "sudoku.h"

void update_pos(Position *pos, int keypressed) { 
    switch (keypressed) {
        case KEY_DOWN:
            if (pos->row < BOARD_ROWS - 1) pos->row++;
            break;
        
        case KEY_UP:
            if (pos->row > 0) pos->row--;
            break;

        case KEY_RIGHT:
            if (pos->column < BOARD_COLS - 1) pos->column++;
            break;

        case KEY_LEFT:
            if (pos->column > 0) pos->column--;
            break;

        default:
            break;
    } 
}

void add_num(Position *pos, Board *board, int keypressed) { 
    if (keypressed >= '0' && keypressed <= '9') {
        int elem_num = pos->row * BOARD_COLS + pos->column;
        
        if (board_runchecks(board->content,
                    pos->row, pos->column, keypressed) == 1) 
            board->content[elem_num] = keypressed;
        else if (keypressed == '0' && board->gencontent_pos[elem_num] == 0)
            board->content[elem_num] = keypressed;
    } 
} 

Position * position_init() {
    Position *pos = malloc(sizeof *pos);
    pos->row = 0;
    pos->column = 0;
    return pos;
}
