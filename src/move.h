#ifndef MOVE_H_
#define MOVE_H_

#include "constants.h"
#include "board.h"
#include "cell.h"
#include "list.h"

typedef struct {
    int fromLine;
    int fromColumn;
    int toLine;
    int toColumn;
} Move;

Move *move_create(int fromLine, int fromColumn, int toLine, int toColumn);
Move move_from_string(char *str);
char *move_to_string(Move move);

int move_apply(Move move, Cell me, Board board, int apply);
List *move_available(Cell me, Board board);

#endif