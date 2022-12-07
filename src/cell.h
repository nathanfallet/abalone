#ifndef CELL_H_
#define CELL_H_

#include "constants.h"

typedef enum{
	White,
	Black,
	Empty,
} Cell;

Cell inversion(Cell casee);
void clone_board(Cell board[ROWS][COLS], Cell target[ROWS][COLS]);

#endif
