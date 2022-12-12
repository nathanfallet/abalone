#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "network.h"

void network_connect(Game *game) {
    // Already connected
    if (game->fdclient != -1) {
        return;
    }

    // Connect
    if (strcmp(game->address, "") == 0) {
        // On est le serveur
        if ((game->fdsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
            printf("Could not create socket: %s\n", strerror(errno));
            exit(1);
        }
        int opt = 1;
        if (setsockopt(game->fdsocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) != 0) {
            printf("Could not set options to socket: %s\n", strerror(errno));
            exit(1);
        }
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port = htons(game->port);

        // Bind and listen
        if (bind(game->fdsocket, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
            printf("Could not bind socket: %s\n", strerror(errno));
            exit(1);
        }
        if (listen(game->fdsocket, 1) != 0) {
            printf("Could not listen on socket: %s\n", strerror(errno));
            exit(1);
        }

        // Accept connections
        game->fdclient = accept(game->fdsocket, NULL, NULL);
        if (game->fdclient == -1) {
            printf("Could not accept client on socket: %s\n", strerror(errno));
            exit(1);
        }
    }
    else {
        // On est le client
        game->fdclient = socket(AF_INET, SOCK_STREAM, 0);
        if (game->fdclient == -1) {
            printf("Could not create socket: %s\n", strerror(errno));
            exit(1);
        }
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(game->address);
        addr.sin_port = htons(game->port);

        // Connexion au serveur
        if (connect(game->fdclient, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
            printf("Could not connect to server: %s (I will retry in 1 second)\n", strerror(errno));
            sleep(1);
        }
    }
}

void network_disconnect(Game *game) {
    if (game->fdclient != -1) {
        close(game->fdclient);
        game->fdclient = -1;
    }
    if (game->fdsocket != -1) {
        close(game->fdsocket);
        game->fdsocket = -1;
    }
}

void network_init(Cell owner, int ia_override, void (*init)(Cell owner, int ia_override, void (*refresh_opponent)(Game *game, Cell me, State state), char address[ADDRESS_LENGTH], int port), char address[ADDRESS_LENGTH], int port) {
    // On init le reste comme d'habitude
    init(owner, ia_override, network_update, address, port);
}

void network_update(Game *game, Cell me, State state) {
    // If it is my turn
    if (game->playing == me) {
        if (game->last_move != MOVE_NONE) {
            // Send last move to opponent
            char *move = move_to_string(game->last_move);
            do {
                network_connect(game);
                int n = write(game->fdclient, move, 6);
                if (n <= 0) {
                    network_disconnect(game);
                }
            } while (game->fdclient == -1);
        }
    }

    // End of game
    if (state != STATE_PLAYING) {
        return;
    }

    if (game->playing == me) {
        // Receive opponent's move
        char *opponent_move = malloc(sizeof(char) * 6);
        int bytes = 0;
        Move result = MOVE_NONE;
        do {
            network_connect(game);
            int n = read(game->fdclient, opponent_move + bytes, sizeof(opponent_move) - bytes);
            if (n <= 0) {
                bytes = 0;
                network_disconnect(game);
            } else {
                bytes += n;
            }
            result = move_from_string(opponent_move);
            if (move_apply(result, me, game->board, 0) == 0) {
                result = MOVE_NONE;
            }
        } while (game->fdclient == -1 || bytes < 6 || result == MOVE_NONE);
        game_turn(game, result);
    }
}
