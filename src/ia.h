#ifndef IA_H
#define IA_H

#include "board.h"
#include "game.h"
#include "constants.h"
#include "scored_move.h"
#include "state.h"

/**
 * Retourne le move avec le score le plus élevé/faible
 * @param me Le joueur
 * @param board Le plateau
 * @param root Le move à comparer
 * @param profondeur La profondeur de l'arbre
 * @param max Si on cherche le max ou le min
 * @param threshold Le seuil de coup
 * @return Le move avec le score le plus élevé/faible
 */
ScoredMove compare(Cell me, Cell playing, Board board, Move root, int profondeur, int max, int threshold);

/**
 * Initialise l'IA avec le callback pour actualiser les joueurs
 * @param owner Le joueur qui créé la partie (CELL_BLACK ou CELL_WHITE)
 * @param refresh_opponent Le callback pour actualiser l'adversaire
 */
void ia_init(Cell owner, void (*refresh_opponent)(PGame game, Cell me, State state));

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
