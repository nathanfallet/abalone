#include "move.h"

typedef unsigned long ScoredMove;

ScoredMove scored_move_new(Move move, Move root, int score);
Move scored_move_move(ScoredMove scored_move);
Move scored_move_root(ScoredMove scored_move);
int scored_move_score(ScoredMove scored_move);

int scored_move_compute(Move move, Cell me, Board board);
