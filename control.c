#include <ncurses.h>
#include <stdlib.h>
#include "control.h"

void update_pos(Position *pos, int keypressed) { 
    // Since the counting starts from 0
    int maxrow, maxcol;
    maxrow = maxcol = 8;

    switch (keypressed) {
        case KEY_DOWN:
            if (pos->row < maxrow) pos->row++;
            break;
        
        case KEY_UP:
            if (pos->row > 0) pos->row--;
            break;

        case KEY_RIGHT:
            if (pos->column < maxcol) pos->column++;
            break;

        case KEY_LEFT:
            if (pos->column > 0) pos->column--;
            break;

        default:
            break;
    } 
}

void add_num(Position *pos, char *board, int keypressed) { 
    if (keypressed >= '1' && keypressed <= '9') {
        int row_length = 9;
        int elem_num = pos->row * row_length + pos->column;
        
        board[elem_num] = keypressed;
    } 
} 

Position * position_init() {
    Position *pos = malloc(sizeof *pos);
    pos->row = 0;
    pos->column = 0;
    return pos;
}
