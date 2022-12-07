#include <stdlib.h>
#include "cell.h"
#include "constants.h"

Cell inversion(Cell casee){
	if (casee == White){
		return Black;
	}
	if (casee == Black){
		return White;	
	}
	return Empty;
}

void clone_board(Cell board[ROWS][COLS], Cell target[ROWS][COLS]) {
	for (int i = 0; i < ROWS; i++){
		for (int j = 0; j < COLS; j++){
			target[i][j] = board[i][j];
		}
	}
}
