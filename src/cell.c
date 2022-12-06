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

Cell **clone_board(Cell board[ROWS][COLS]){
	Cell **clone = malloc(ROWS * sizeof(Cell *));
	for (int i = 0; i < ROWS; i++){
		clone[i] = malloc(COLS * sizeof(Cell));
		for (int j = 0; j < COLS; j++){
			clone[i][j] = board[i][j];
		}
	}
	return clone;
}
