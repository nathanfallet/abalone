#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "ia.h"

int max(){
    return 0;
}

int min(){
    return 0;
}

// Algorithme minimax. Il retourne une décision (move) et prend en compte le joueur qui joue ainsi que le board actuel

Move minimax(Cell me, Cell board[ROWS][COLS]){
    List *moves = move_available(me, board);
    List *scored_moves = list_init();
    for(int i=1;i<=list_taille(moves);i++){
        Move *move = (Move*)list_accede(i,moves);
        list_insere(
            score_move_new(*move, compute_score(*move, me, board)),
            i,
            scored_moves
        );
    }

    // Tri
    list_trirapide(scored_moves, score_move_cmp);

    // On fait genre que l'IA réfléchit
    sleep(3);

    // Prends le move avec le plus haut score
    if (list_taille(scored_moves) > 0) {
        ScoredMove *sm = list_accede(1, scored_moves);
        return sm->move;
    }

    // Cas par défaut
    return (Move){0,0,0,0};
}


// Implémentation des fonctions de base pour intéragir avec le jeu

void ia_init(Cell owner, void (*refresh_opponent)(PGame game, Cell me, State state)) {
    PGame game = new_game(owner);
    game->refresh = ia_update;
    game->refresh_opponent = refresh_opponent;

    game_start(game);
}

void ia_update(PGame game, Cell me, State state){
    // Fin de partie 
    if (state != In_progress) {
        return;
    }

    // Si c'est mon tour:
    if (game->playing == me) {
        Move move = minimax(me, game->board);
        game_turn(game, move);

    }
}
