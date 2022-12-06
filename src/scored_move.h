#include "move.h"

typedef struct{
    Move move;
    int score;
}ScoredMove;


ScoredMove* score_move_new(Move move, int score);
int score_move_cmp(void *sm1, void *sm2);
int compute_score(Move move,Cell me, Cell board[ROWS][COLS]);
