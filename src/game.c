#include <stdio.h>
#include <stdlib.h>
#include "game.h"


PGame new_game(Cell owner) {
    PGame game = (PGame) malloc(sizeof(Game));

    // Initialisation du tableau
    for(int i=0; i<ROWS; i++){
        for(int j=0; j<COLS; j++){
            game->board[i][j] = Empty;
        }
    }
    for (int i=0; i<8; i++){
        game->board[0][i]=White;
    }
    for (int i=1; i<7; i++){
        game->board[1][i]=White;
    }
    for (int i=1; i<7; i++){
        game->board[6][i]=Black;
    }
    for (int i=0; i<8; i++){
        game->board[7][i]=Black;
    }

    // Valeur par défaut pour le reste
    game->start = time(NULL);
    game->owner = owner;
    game->playing = Black;
    game->last_move = (Move){0,0,0,0};
    game->actualiser = NULL;
    game->actualiser_adversaire = NULL;

    return game;
}

void game_turn(PGame game, Move move) {
    // Appliquer le movement
    if (move_apply(move, game->playing, game->board, 1) == 0) {
        // Move invalide !
        printf("Move invalide !\n");
        exit(1);
    }

    // Actualiser le joueur
    game->playing = inversion(game->playing);
    game->last_move = move;

    // On emet
    State state = game_state(game);
    if (game->actualiser != NULL) {
        game->actualiser(game, game->owner, state);
    }
    if (game->actualiser_adversaire != NULL) {
        game->actualiser_adversaire(game, inversion(game->owner), state);
    }
}

void game_start(PGame game) {
    if (game->actualiser != NULL) {
        game->actualiser(game, game->owner, In_progress);
    }
    if (game->actualiser_adversaire != NULL) {
        game->actualiser_adversaire(game, inversion(game->owner), In_progress);
    }
}

//Renvoi l'état de la partie
State game_state(PGame game){
    // Check for time first (timeout after 15 minutes)
    time_t now = time(NULL);
    if (difftime(now, game->start) > 15*60) {
        return Out_of_time;
    }

    // Count the number of pawns
    int pion_noir = 0;
    int pion_blanc = 0;
    for(int i = 0; i<ROWS; i++){
        //Compte le nombre de pions dans la partie
        for(int j = 0; j<COLS; j++){
            if(game->board[i][j] == Black) pion_noir += 1;
            if(game->board[i][j] == White) pion_blanc += 1;
        }
    }
    if(pion_noir < PION_TOT) return Win_white;
    if(pion_blanc < PION_TOT) return Win_black;

    return In_progress;
}
