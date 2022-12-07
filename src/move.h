#ifndef MOVE_H_
#define MOVE_H_

#include "constants.h"
#include "board.h"
#include "cell.h"

typedef unsigned short Move;

Move move_create(unsigned char fromLine, unsigned char fromColumn, unsigned char toLine, unsigned char toColumn);
unsigned char move_get_from_line(Move move);
unsigned char move_get_from_column(Move move);
unsigned char move_get_to_line(Move move);
unsigned char move_get_to_column(Move move);
Move move_from_string(char *string);
char *move_to_string(Move move);

int move_apply(Move move, Cell me, Board board, int apply);
void move_available(Cell me, Board board, Move array[MOVE_LIST_SIZE]);

#endif