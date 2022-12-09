#ifndef GAME_H_
#define GAME_H_

#include "constants.h"
#include "board.h"
#include "move.h"
#include "cell.h"
#include "state.h"

typedef struct game_t {
	// Plateau : vide, pion noir ou pion blanc
	Board board;

	// Joueur qui a lancé la partie, et celui qui doit jouer
	Cell owner;
	Cell playing;
	int ia_override;

	// Dernier coup joué
	int has_last_move;
	Move last_move;

	// Callback pour actualiser les joueurs
	void (*refresh)(struct game_t *game, Cell me, State state);
	void (*refresh_opponent)(struct game_t *game, Cell me, State state);
} Game;
typedef Game* PGame;


/**
 * Créé et initialise une partie
 * @param owner Le joueur qui créé la partie (CELL_BLACK ou CELL_WHITE)
 * @param ia_override Si l'IA doit jouer à la place du joueur
 * @return La partie crée
 */
PGame game_new(Cell owner, int ia_override);

/**
 * Exécute le prochain tour de jeu
 * @param game La partie
 * @param move Le coup à jouer
 */
void game_turn(PGame game, Move move);

/**
 * Démarre la partie
 * @param game La partie
 */
void game_start(PGame game);

#endif
