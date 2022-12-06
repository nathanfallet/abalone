#include <stdlib.h>
#include "scored_move.h"
#include "move.h"
#include "cell.h"



ScoredMove *score_move_new(Move move, int score){
    ScoredMove *score_move = malloc(sizeof(ScoredMove));
    score_move->move=move;
    score_move->score=score;
    return score_move;
}

//fonction de comparaison des scores, return la différence des scores
int score_move_cmp(void *sm1, void *sm2){
    return ((ScoredMove*)sm1)->score-((ScoredMove*)sm2)->score;
}

//fonction qui servira à calculer le score d'un mouvement /!\ Non faite !
//si le mouvement est gagnant, return 1
//si le mouvement est perdant (suicide), return -1
//sinon, si le mouvement n'implique pas directement la victoire ou la défaite du joueur, return 0
int compute_score(Move move,Cell me, Cell board[ROWS][COLS]){
    move_apply(move,me,clone_board(board),1);
    // Count the number of pawns
    int pawn_me = 0;
    int pawn_opponent = 0;
    for(int i = 0; i<ROWS; i++){
        //Compte le nombre de pions dans la partie
        for(int j = 0; j<ROWS; j++){
            if(board[i][j] == me) pawn_me += 1;
            if(board[i][j] == inversion(me)) pawn_opponent += 1;
        }
    }
    if(pawn_me < PAWN_TOT) return -1;
    if(pawn_opponent < PAWN_TOT) return 1;

    return 0;
}

