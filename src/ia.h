#ifndef IA_H
#define IA_H

/**
 * \file ia.h
 * \brief IA management
 * 
 * IA management and his reflection.
 */

#include "board.h"
#include "game.h"
#include "constants.h"
#include "scored_move.h"
#include "state.h"

/**
 * \brief Execute the next game round of IA 
 * \param game The game
 * \param me The current player
 * \param state The state of the game
 */
void ia_update(Game *game, Cell me, State state);

/**
 * \brief Return the best Move for the IA
 * \param me The player
 * \param board The board
 * \param deepness The deepness of the tree
 * \return The best Move
 */
Move ia_minimax(Cell me, Board board, int deepness);

#endif
