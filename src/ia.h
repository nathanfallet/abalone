#ifndef IA_H
#define IA_H

#include "board.h"
#include "game.h"
#include "constants.h"
#include "scored_move.h"
#include "state.h"

/**
 * Exécute le prochain tour de jeu de l'IA
 * @param game La partie
 * @param me Le joueur
 * @param state L'état de la partie
 */
void ia_update(PGame game, Cell me, State state);

/**
 * Retourne le meilleur move pour l'IA
 * @param me Le joueur
 * @param board Le plateau
 * @param profondeur La profondeur de l'arbre
 * @return Le meilleur move
 */
Move ia_minimax(Cell me, Board board, int profondeur);

#endif
