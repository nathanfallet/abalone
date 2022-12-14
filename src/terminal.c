#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "terminal.h"

// Storage of things

Game *terminal_last_game;
Cell terminal_last_me;
State terminal_last_state;

// Internal functions

Move terminal_read() {
    char input[6];
    scanf("%s", input);
    return move_from_string(input);
}

void terminal_print(Board board) {
    char *alpha = {"ABCDEFGH"}; // Column letter
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
}

void terminal_background_start(Game *game) {
    pthread_t thread;
    pthread_create(&thread, NULL, game_start, game);
}

void *terminal_background_turn() {
    if (terminal_last_game->ia_override) {
        // Ask IA
        ia_update(terminal_last_game, terminal_last_me, terminal_last_state);
    } else {
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

// Public functions

void terminal_init(Cell owner, int ia_override, void (*refresh_opponent)(Game *game, Cell me, State state), char address[ADDRESS_LENGTH], int port) {
    Game *game = game_new(owner, ia_override);
    strcpy(game->address, address);
    game->port = port;
    game->refresh = terminal_update;
    game->refresh_opponent = refresh_opponent;

    terminal_background_start(game);

    while (1) {
        sleep(1);
    }
}

void terminal_update(Game *game, Cell me, State state) {
    // Saving things (To send them to the main thread)
    terminal_last_game = game;
    terminal_last_me = me;
    terminal_last_state = state;

    // Display
    terminal_print(game->board);

    // End of the game
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

    // If it is my turn
    if (game->playing == me) {
        pthread_t thread;
        pthread_create(&thread, NULL, terminal_background_turn, NULL);
    }
}
