#ifndef BOARD_H
#define BOARD_H

#include "constants.h"
#include "cell.h"

typedef unsigned long Board[2];

void board_create(Board board);
void board_clone(Board board, Board target);
Cell board_get_cell(Board board, int line, int column);
void board_set_cell(Board board, int line, int column, Cell cell);

#endif
