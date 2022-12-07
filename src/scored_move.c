#include <stdlib.h>
#include "scored_move.h"
#include "move.h"
#include "cell.h"

ScoredMove scored_move_new(Move move, Move root, int score){
    return move | (root << 16) | (((ScoredMove) score) << 32);
}

Move scored_move_move(ScoredMove scored_move) {
    return scored_move & 0xffff;
}

Move scored_move_root(ScoredMove scored_move) {
    return (scored_move >> 16) & 0xffff;
}

int scored_move_score(ScoredMove scored_move) {
    return (int) (scored_move >> 32);
}

//fonction qui servira à calculer le score d'un mouvement /!\ Non faite !
//si le mouvement est gagnant, return 1
//si le mouvement est perdant (suicide), return -1
//sinon, si le mouvement n'implique pas directement la victoire ou la défaite du joueur, return 0
int scored_move_compute(Move move, Cell me, Board board) {
    Board copy;
    board_clone(board, copy);
    move_apply(move,me,copy,1);
    
    int score = 0;

    // point par rapport au centre
    for(int i = 0; i<BOARD_SIZE; i++){
        for(int j = 0; j<BOARD_SIZE; j++){
            if(board_get_cell(copy, i, j) == me) score += (10 - abs(4-i) - abs(4-j));
            if(board_get_cell(copy, i, j) == cell_opposite(me)) score -= (10 - abs(4-i) - abs(4-j));
        }
    }

    // Count the number of pawns
    int pawn_me = 0;
    int pawn_opponent = 0;
    for(int i = 0; i<BOARD_SIZE; i++){
        for(int j = 0; j<BOARD_SIZE; j++){
            if(board_get_cell(copy, i, j) == me) pawn_me += 1;
            if(board_get_cell(copy, i, j) == cell_opposite(me)) pawn_opponent += 1;
        }
    }
    if(pawn_me < PAWN_TOT) score -= WEIGTH_WIN;;
    if(pawn_opponent < PAWN_TOT) score += WEIGTH_WIN;;

    return score;
}

