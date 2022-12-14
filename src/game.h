#ifndef GAME_H
#define GAME_H

/**
 * \file game.h
 * \brief Game management
 * 
 * Management of a game and its progress. 
 */

#include "constants.h"
#include "board.h"
#include "move.h"
#include "cell.h"
#include "state.h"

/**
 * \brief Game structure
 */
typedef struct Game {
	Board board; /*!< Board of game */

	Cell owner; /*!< The player who create the game */
	Cell playing; /*!< The player who currently playing */
	int ia_override; /*!< If the AI ​​should play instead of the player */
	Move last_move; /*!< The last move played */

	char address[ADDRESS_LENGTH]; /*!< Server address (if game as client) */
	int port; /*!< Server port (if game as client or server) */
	int fdsocket; /*!< Server socket (if game as server) */
	int fdclient; /*!< Client socket (if game as client or server) */

	void (*refresh)(struct Game *game, Cell me, State state); /*!< Callback for refesh display */
	void (*refresh_opponent)(struct Game *game, Cell me, State state); /*!< Callback for refesh opponant display */
} Game;

/**
 * \brief Create and initialize a game
 * \param owner The player who create the game (CELL_BLACK or CELL_WHITE)
 * \param ia_override If the AI must play instead of player
 * \return The game created
 */
Game *game_new(Cell owner, int ia_override);

/**
 * \brief Execute the next game turn
 * \param game The game
 * \param move The move to play
 */
void game_turn(Game *game, Move move);

/**
 * \brief Start game
 * \param game The game
 */
void game_start(Game *game);

#endif
