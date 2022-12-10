#ifndef SCORED_MOVE_H
#define SCORED_MOVE_H

/**
 * \file scored_move.h
 * \brief Gestion du score des mouvements
 * 
 * Gestion du score des mouvements, avec leur calcul.
 */

#include "move.h"
#include "cell.h"
#include "constants.h"

/**
 * \brief Représente un déplacement associé à un score
 * 
 * Un déplacement associé à un score est représenté par un entier sur 64 bits,
 * avec les 16 bits de poids faible pour le déplacement,
 * les 16 bits suivants pour le déplacement de départ,
 * et les 32 bits de poids fort pour le score.
 */
typedef unsigned long ScoredMove;

/**
 * \brief Crée un nouveau déplacement associé à un score et sauvegarde le déplacement de départ
 * \param move Le déplacement
 * \param root Le déplacement de départ
 * \param score Le score
 * \return Le déplacement associé au score
 */
ScoredMove scored_move_new(Move move, Move root, int score);

/**
 * \brief Renvoi le déplacement associé au score
 * \param scored_move Le déplacement associé au score
 * \return Le déplacement
 */
Move scored_move_move(ScoredMove scored_move);

/**
 * \brief Renvoi le déplacement de départ
 * \param scored_move Le déplacement associé au score
 * \return Le déplacement de départ
 */
Move scored_move_root(ScoredMove scored_move);

/**
 * \brief Renvoi le score associé au déplacement
 * \param scored_move Le déplacement associé au score
 * \return Le score
 */
int scored_move_score(ScoredMove scored_move);

/**
 * \brief Calcul le score d'un déplacement
 * \param scored_move Le déplacement associé au score
 * \param me Le joueur
 * \param board Le plateau
 * \return Le score
 */
int scored_move_compute(Cell me, Board board);

#endif
