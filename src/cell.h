#ifndef CELL_H_
#define CELL_H_

#include "constants.h"

typedef enum{
	White,
	Black,
	Empty,
} Cell;

Cell inversion(Cell casee);
Cell **clone_board(Cell board[ROWS][COLS]);

#endif
