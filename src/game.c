#include <stdio.h>
#include <stdlib.h>
#include "game.h"


PGame game_new(Cell owner, int ia_override) {
    PGame game = (PGame) malloc(sizeof(Game));

    // Initialisation du tableau
    board_create(game->board);

    // Valeur par défaut pour le reste
    game->owner = owner;
    game->playing = CELL_BLACK;
    game->ia_override = ia_override;
    game->has_last_move = 0;
    game->last_move = MOVE_NONE;
    game->refresh = NULL;
    game->refresh_opponent = NULL;

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
    game->playing = cell_opposite(game->playing);
    game->has_last_move = 1;
    game->last_move = move;

    // On emet
    State state = board_state(game->board);
    if (game->refresh != NULL) {
        game->refresh(game, game->owner, state);
    }
    if (game->refresh_opponent != NULL) {
        game->refresh_opponent(game, cell_opposite(game->owner), state);
    }
}

void game_start(PGame game) {
    State state = board_state(game->board);
    if (game->refresh != NULL) {
        game->refresh(game, game->owner, state);
    }
    if (game->refresh_opponent != NULL) {
        game->refresh_opponent(game, cell_opposite(game->owner), state);
    }
}
