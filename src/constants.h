#ifndef CONSTANTS_H
#define CONSTANTS_H

/**
 * \file constants.h
 * \brief Global constant
 */

/**
 * \brief Board size
 */
#define BOARD_SIZE 8

/**
 * \brief Empty cell
 */
#define CELL_EMPTY 0 

/**
 * \brief Black cell
 */
#define CELL_BLACK 1

/**
 * \brief White cell
 */
#define CELL_WHITE 2

/**
 * \brief Game in court
 */
#define STATE_PLAYING 0

/**
 * \brief Game over, black victory
 */
#define STATE_WIN_BLACK 1

/**
 * \brief Game over, white victory
 */
#define STATE_WIN_WHITE 2

/**
 * \brief Move none
 */
#define MOVE_NONE 0

/**
 * \brief Maximum move list size 
 */
#define MOVE_LIST_SIZE 280

/**
 * \brief weight of win move (dans scored_move_compute)
 */
#define WEIGHT_WIN 100000

/**
 * \brief weight of win move (dans ia_minimax_compare directement)
 */
#define WEIGHT_WIN_DIRECT 1000000

/**
 * \brief Weight when a pawn is neighbour
 */
#define WEIGHT_NEIGHBOUR 2

/**
 * \brief Weight when a pawn is near
 */
#define WEIGHT_PROXIMITY 1

/**
 * \brief Weight when a pawn is center
 */
#define WEIGHT_CENTER 3

/**
 * \brief Weight when a pawn can push an another
 */
#define WEIGHT_OPPOSITE 3

/**
 * \brief Number of player pawns
 */
#define PAWN_TOT 14

/**
 * \brief Deepness of IA
 */
#ifndef DEEPNESS
#define DEEPNESS 4
#endif

/**
 * \brief Initialization constant (none)
 */
#define INIT_NONE -1

/**
 * \brief Default initialization constant
 */
#define INIT_DEFAULT 0

/**
 * \brief Initialization constant (terminal)
 */
#define INIT_TERMINAL 1

/**
 * \brief Initialization constant (graphic interface)
 */
#define INIT_GUI 2

/**
 * \brief Initialization constant  (network)
 */
#define INIT_NETWORK 3

/**
 * \brief Maximum size of an IP address
 */
#define ADDRESS_LENGTH 16

/**
 * \brief Color in terminal
 */
#define color(param) printf("\033[%sm",param)

#endif
