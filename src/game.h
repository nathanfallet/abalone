#ifndef GAME_H
#define GAME_H

/**
 * \file game.h
 * \brief Gestion d'une partie
 * 
 * Gestion d'une partie et de son déroulement.
 */

#include "constants.h"
#include "board.h"
#include "move.h"
#include "cell.h"
#include "state.h"

/**
 * \brief Structure d'une partie
 */
typedef struct Game {
	Board board; /*!< Plateau de jeu de la partie */

	Cell owner; /*!< Le joueur qui a créé la partie */
	Cell playing; /*!< Le joueur qui joue actuellement */
	int ia_override; /*!< Si l'IA doit jouer à la place du joueur */

	int has_last_move; /*!< Si un coup a été joué dans la partie */
	Move last_move; /*!< Le dernier coup joué */

	void (*refresh)(struct Game *game, Cell me, State state); /*!< Callback pour actualiser l'affichage */
	void (*refresh_opponent)(struct Game *game, Cell me, State state); /*!< Callback pour actualiser l'affichage de l'adversaire */
} Game;

/**
 * \brief Créé et initialise une partie
 * \param owner Le joueur qui créé la partie (CELL_BLACK ou CELL_WHITE)
 * \param ia_override Si l'IA doit jouer à la place du joueur
 * \return La partie crée
 */
Game *game_new(Cell owner, int ia_override);

/**
 * \brief Exécute le prochain tour de jeu
 * \param game La partie
 * \param move Le coup à jouer
 */
void game_turn(Game *game, Move move);

/**
 * \brief Démarre la partie
 * \param game La partie
 */
void game_start(Game *game);

#endif
