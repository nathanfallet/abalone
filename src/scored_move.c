#include <stdlib.h>
#include "scored_move.h"

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
    
    int count=0;
    
    int score = 0;
    int pawn_me = 0;
    int pawn_opponent = 0;
    for(int i = 0; i<BOARD_SIZE; i++){
        for(int j = 0; j<BOARD_SIZE; j++){
            // point par rapport au centre
            if(board_get_cell(copy, i, j) == me) score += WEIGHT_CENTER*(10 - abs(4-i) - abs(4-j));
            if(board_get_cell(copy, i, j) == cell_opposite(me)) score -= WEIGHT_CENTER*(10 - abs(4-i) - abs(4-j));
            // Count the number of pawns
            if(board_get_cell(copy, i, j) == me) pawn_me += 1;
            if(board_get_cell(copy, i, j) == cell_opposite(me)) pawn_opponent += 1;
            //Regarde la proximité par rapport au autres pions
            if(board_get_cell(copy, i, j) == me){
                //regarde si on est aligné à 2
                if(board_get_cell(copy, i+1,j) == me){
                    score += WEIGHT_PROXIMITY;
                    for(int k=i;k<BOARD_SIZE;k++){
            		if(board_get_cell(copy, i+k, j) == cell_opposite(me)){
            			count+=1;
            			if(count==1){
            				score*=WEIGHT_OPPOSITE;
            			}
            			else{
            				score-=WEIGHT_OPPOSITE;
            			}
            			count=0;
            		}
            	    }
            	    for(int k=i;k>0;k--){
            		if(board_get_cell(copy, i+k, j) == cell_opposite(me)){
            			count+=1;
            			if(count==1){
            				score*=WEIGHT_OPPOSITE;
            			}
            			else{
            				score-=WEIGHT_OPPOSITE;
            			}
            			count=0;
            		}
            	    }
                    //cherche s'il y a un aversaire au bout de la ligne
                    /*if(board_get_cell(copy, i+2,j) == cell_opposite(me) || board_get_cell(copy, i-1,j) == cell_opposite(me)){
                        score += WeiGTH_OPPOSITE;
                    }*/
                    //regarde si on est aligné à 3
                    if(board_get_cell(copy, i+2, j) == me){
                        score += 2*WEIGHT_PROXIMITY;
                        /*cherche s'il y a un aversaire au bout de la ligne
                        if(board_get_cell(copy, i+3,j) == cell_opposite(me)){
                            score += WeiGTH_OPPOSITE;
                        }*/
                        for(int k=i+2;k<BOARD_SIZE;k++){
            		if(board_get_cell(copy, i+k, j) == cell_opposite(me)){
            			count+=1;
            			if(count<=2){
            				score*=WEIGHT_OPPOSITE;
            			}
            		   }
            	    	}
            	    	for(int k=i-2;k>0;k--){
            			if(board_get_cell(copy, i+k, j) == cell_opposite(me)){
            				count+=1;
            				if(count<=2){
            					score*=WEIGHT_OPPOSITE;
            				}
            		}
            	    }
                    }
                }
                //regarde si on est aligné à 2
                if(board_get_cell(copy, i,j+1) == me){
                    score += WEIGHT_PROXIMITY;
                    //cherche s'il y a un aversaire au bout de la ligne
                    /*if(board_get_cell(copy, i, j+2) == cell_opposite(me) || board_get_cell(copy, i, j-1) == cell_opposite(me)){
                        score += WeiGTH_OPPOSITE;
                    }*/
                    for(int k=j;k<BOARD_SIZE;k++){
            		if(board_get_cell(copy, i, j+k) == cell_opposite(me)){
            			count+=1;
            			if(count==1){
            				score*=WEIGHT_OPPOSITE;
            			}
            			else{
            				score-=WEIGHT_OPPOSITE;
            			}
            			count=0;
            		}
            	    }
            	    for(int k=j;k>0;k--){
            		if(board_get_cell(copy, i, j+k) == cell_opposite(me)){
            			count+=1;
            			if(count==1){
            				score*=WEIGHT_OPPOSITE;
            			}
            			else{
            				score-=WEIGHT_OPPOSITE;
            			}
            			count=0;
            		}
            	    }
                    //regarde si on est aligné à 3
                    if(board_get_cell(copy, i, j+2) == me){
                        score += 2*WEIGHT_PROXIMITY;
                        /*cherche s'il y a un aversaire au bout de la ligne
                        if(board_get_cell(copy, i,j+3) == cell_opposite(me)){
                            score += WeiGTH_OPPOSITE;
                        }*/
                        for(int k=j+2;k<BOARD_SIZE;k++){
            			if(board_get_cell(copy, i, j+k) == cell_opposite(me)){
            				count+=1;
            				if(count<=2){
            					score*=WEIGHT_OPPOSITE;
            			}
            		   }
            	    	}
            	    	for(int k=j-2;k>0;k--){
            			if(board_get_cell(copy, i, j+k) == cell_opposite(me)){
            				count+=1;
            				if(count<=2){
            					score*=WEIGHT_OPPOSITE;
            				}
            			}
            	    	}
                        
                    }
                }
            }   
        }
    }
        
    if(pawn_me < PAWN_TOT) score -= WEIGHT_WIN;;
    if(pawn_opponent < PAWN_TOT) score += WEIGHT_WIN;;

    return score;
}

