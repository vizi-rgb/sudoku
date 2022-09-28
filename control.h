#ifndef _CONTROL_H_
#define _CONTROL_H_

typedef struct Board Board;

typedef struct Position {
    int row;
    int column;
} Position;

void update_pos(Position *pos, int keypressed);

void add_num(Position *pos, Board *board, int keypressed);

Position * position_init();

#endif
