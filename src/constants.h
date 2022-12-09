#ifndef CONSTANTS_H
#define CONSTANTS_H

#define BOARD_SIZE 8

/**
 * cellule vide 
 */
#define CELL_EMPTY 0 

/**
 * cellule noire 
 */
#define CELL_BLACK 1
/**
 * cellule blanche
 */
#define CELL_WHITE 2

#define STATE_PLAYING 0
#define STATE_WIN_BLACK 1
#define STATE_WIN_WHITE 2
#define STATE_TIME_OUT 3

#define MOVE_NONE 0
#define MOVE_LIST_SIZE 280

#define WEIGHT_WIN 100000
#define WEIGHT_NEIGHBOUR 2
#define WEIGHT_PROXIMITY 1
#define WEIGHT_CENTER 5
#define WEIGHT_OPPOSITE 3
#define PAWN_TOT 14

#define INIT_NONE -1
#define INIT_TERMINAL 0
#define INIT_GUI 1
#define INIT_NETWORK 2
#define INIT_DEFAULT INIT_GUI

#define ADDRESS_LENGTH 255

#define color(param) printf("\033[%sm",param)


#endif
