#include <stdio.h>
#include <stdlib.h>
#include "game.h"

Game *game_new(Cell owner, int ia_override) {
    Game *game = malloc(sizeof(Game));

    /* board initialization */ 
    board_create(game->board);

    /* Default value for the rest */ 
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
    /* apply the movement */
    if (move_apply(move, game->playing, game->board, 1) == 0) {
        /* impossible to move ! */
        printf("Move invalide !\n");
        exit(1);
    }

    /* refresh player */
    game->playing = cell_opposite(game->playing);
    game->last_move = move;

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
