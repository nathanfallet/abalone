#ifndef SCORED_MOVE_H
#define SCORED_MOVE_H

/**
 * \file scored_move.h
 * \brief Management of movement's score
 * 
 * Management of movement's score, with calcul.
 */

#include "move.h"
#include "cell.h"
#include "constants.h"

/**
 * \brief Represent a deplacement asociated to a score 
 *  A move associated with a score is represented with an integer on 64-bits,
 *  with 16 least significant bits for the move,
 * the next 16 bits for the start move, 
 * and the 32 most significant bits for the score.
 */
typedef unsigned long ScoredMove;

/**
 * \brief Create a new move associated with a score et save the start move. 
 * \param move The movement
 * \param root The starting move
 * \param score The score
 * \return The move associated with the score
 */
ScoredMove scored_move_new(Move move, Move root, int score);

/**
 * \brief Return the move associated with a the score 
 * \param scored_move The move associated with the score 
 * \return The move
 */
Move scored_move_move(ScoredMove scored_move);

/**
 * \brief Renvoi The starting move 
 * \param scored_move The move associated with the score
 * \return The starting move
 */
Move scored_move_root(ScoredMove scored_move);

/**
 * \brief Return the score associated with the move
 * \param scored_move The move associated with the score
 * \return The score
 */
int scored_move_score(ScoredMove scored_move);

/**
 * \brief Compute the score of a move 
 * \param scored_move The move associated with score
 * \param me The player
 * \param board The plate
 * \return The score
 */
int scored_move_compute(Cell me, Board board);

#endif
