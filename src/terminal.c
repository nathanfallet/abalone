#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "terminal.h"

// Stockage de trucs

PGame terminal_last_game;
Cell terminal_last_me;
State terminal_last_state;

// Fonctions internes

Move terminal_read() {
    char input[6];
    scanf("%s", input);
    return move_from_string(input);
}

int terminal_print(Board board) {
    char *alpha = {"ABCDEFGH"}; // colonne lettre
    printf("\n   ");
    for (int i = 1; i <= 8; i++) {
        printf("  %i ", i);
    }
    printf("\n");
    printf("   +-------------------------------+ \n");
    for (int i = 0; i < 8; i++) {
        printf(" %c ", alpha[i]);
        for (int j = 0; j < 8; j++) {
            printf("| ");
            switch (board_get_cell(board, i, j)) {
            case CELL_BLACK:
                color("31");
                printf("⬤ ");
                color("00");
                break;
            case CELL_WHITE:
                color("34");
                printf("⬤ ");
                color("00");
                break;
            default:
                color("00");
                printf("  ");
                break;
            }
        }
        printf("|\n");
        printf("   +-------------------------------+ \n");
    }
    color("31");
    printf("         Black   ");
    color("34");
    printf("         White   ");
    color("00");
    printf("\n");
    return 0;
}

void terminal_background_start(PGame game) {
    pthread_t thread;
    pthread_create(&thread, NULL, game_start, game);
}

void *terminal_background_turn() {
    if (terminal_last_game->ia_override) {
        // Ask IA
        ia_update(terminal_last_game, terminal_last_me, terminal_last_state);
    }
    else {
        // Ask player
        Move move = MOVE_NONE;
        do {
            printf("Votre coup : ");
            move = terminal_read();
        } while (move_apply(move, terminal_last_me, terminal_last_game->board, 0) == 0);
        game_turn(terminal_last_game, move);
    }
    return NULL;
}

void terminal_update_intern(PGame game, Cell me, State state, int affichage) {
    // On enregistre les trucs (pour les passer au main thread)
    terminal_last_game = game;
    terminal_last_me = me;
    terminal_last_state = state;

    // Affichage
    if (affichage) {
        terminal_print(game->board);
    }

    // Fin de la partie
    switch (state) {
    case STATE_WIN_BLACK:
        printf("Le joueur Black a gagné !\n");
        return;
    case STATE_WIN_WHITE:
        printf("Le joueur White a gagné !\n");
        return;
    default:
        break;
    }

    // Si c'est mon tour:
    if (game->playing == me) {
        pthread_t thread;
        pthread_create(&thread, NULL, terminal_background_turn, NULL);
    }
}

// Fonctions publiques

void terminal_init(Cell owner, int ia_override, void (*refresh_opponent)(PGame game, Cell me, State state)) {
    PGame game = game_new(owner, ia_override);
    game->refresh = terminal_update;
    game->refresh_opponent = refresh_opponent;

    terminal_background_start(game);

    while (1) {
        sleep(1);
    }
}

void terminal_update(PGame game, Cell me, State state) {
    terminal_update_intern(game, me, state, 1);
}

void terminal_update_no_print(PGame game, Cell me, State state) {
    terminal_update_intern(game, me, state, 0);
}
