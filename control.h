#ifndef _CONTROL_H_
#define _CONTROL_H_

typedef struct Position {
    int row;
    int column;
} Position;

void update_pos(Position *pos, int keypressed);

void add_num(Position *pos, char *board, int keypressed);

Position * position_init();

#endif
