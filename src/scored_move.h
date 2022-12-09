#include "move.h"
#include "cell.h"
#include "constants.h"

typedef unsigned long ScoredMove;

/**
 * Crée un nouveau déplacement associé à un score 
 * et sauvegarde le déplacement de départ
 * @param move Le déplacement
 * @param root Le déplacement de départ
 * @param score Le score
 * @return Le déplacement associé au score 
*/
ScoredMove scored_move_new(Move move, Move root, int score);

/**
 * Renvoi le déplacement associé au score
 * @param scored_move Le déplacement associé au score
 * @return Le déplacement
*/
Move scored_move_move(ScoredMove scored_move);

/**
 * Renvoi le déplacement de départ
 * @param scored_move Le déplacement associé au score
 * @return Le déplacement de départ
*/
Move scored_move_root(ScoredMove scored_move);

/**
 * Renvoi le score associé au déplacement
 * @param scored_move Le déplacement associé au score
 * @return Le score
*/
int scored_move_score(ScoredMove scored_move);

/**
 * Calcul le score d'un déplacement
 * @param scored_move Le déplacement associé au score
 * @param me Le joueur
 * @param board Le plateau
 * @return Le score
*/
int scored_move_compute(Cell me, Board board);
