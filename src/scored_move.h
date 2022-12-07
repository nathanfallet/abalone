#include "move.h"

typedef struct{
    Move *move;
    Move *root;
    int score;
}ScoredMove;

ScoredMove* score_move_new(Move *move, Move *root, int score);
int score_move_cmp(void *sm1, void *sm2);
int compute_score(Move move,Cell me, Board board);
