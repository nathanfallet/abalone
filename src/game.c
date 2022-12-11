#include <stdio.h>
#include <stdlib.h>
#include "game.h"

Game *game_new(Cell owner, int ia_override) {
    Game *game = malloc(sizeof(Game));

    // Initialisation du tableau
    board_create(game->board);

    // Valeur par défaut pour le reste
    game->owner = owner;
    game->playing = CELL_BLACK;
    game->ia_override = ia_override;
    game->last_move = MOVE_NONE;
    game->fdsocket = -1;
    game->fdclient = -1;
    game->refresh = NULL;
    game->refresh_opponent = NULL;

    return game;
}

void game_turn(Game *game, Move move) {
    // Appliquer le movement
    if (move_apply(move, game->playing, game->board, 1) == 0) {
        // Move invalide !
        printf("Move invalide !\n");
        exit(1);
    }

    // Actualiser le joueur
    game->playing = cell_opposite(game->playing);
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

void game_start(Game *game) {
    State state = board_state(game->board);
    if (game->refresh != NULL) {
        game->refresh(game, game->owner, state);
    }
    if (game->refresh_opponent != NULL) {
        game->refresh_opponent(game, cell_opposite(game->owner), state);
    }
}
