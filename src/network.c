#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "network.h"

char saved_address[ADDRESS_LENGTH];
int saved_port;
int fdsocket = -1;
int fdclient = -1;

void network_connect() {
    // Already connected
    if (fdclient != -1) {
        return;
    }

    // Connect
    if (strcmp(saved_address, "") == 0) {
        // On est le serveur
        if ((fdsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
            printf("Could not create socket: %s\n", strerror(errno));
            exit(1);
        }
        int opt = 1;
        if (setsockopt(fdsocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) != 0) {
            printf("Could not set options to socket: %s\n", strerror(errno));
            exit(1);
        }
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port = htons(saved_port);

        // Bind and listen
        if (bind(fdsocket, (struct sockaddr *) &addr, sizeof(addr)) != 0) {
            printf("Could not bind socket: %s\n", strerror(errno));
            exit(1);
        }
        if (listen(fdsocket, 1) != 0) {
            printf("Could not listen on socket: %s\n", strerror(errno));
            exit(1);
        }

        // Accept connections
        fdclient = accept(fdsocket, NULL, NULL);
        if (fdclient == -1) {
            printf("Could not accept client on socket: %s\n", strerror(errno));
            exit(1);
        }
    } else {
        // On est le client
        fdclient = socket(AF_INET, SOCK_STREAM, 0);
        if (fdclient == -1) {
            printf("Could not create socket: %s\n", strerror(errno));
            exit(1);
        }
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(saved_address);
        addr.sin_port = htons(saved_port);

        // Connexion au serveur
        if (connect(fdclient, (struct sockaddr *) &addr, sizeof(addr)) != 0) {
            printf("Could not connect to server: %s (I will retry in 1 second)\n", strerror(errno));
            sleep(1);
        }
    }
}

void network_disconnect() {
    if (fdclient != -1) {
        close(fdclient);
        fdclient = -1;
    }
    if (fdsocket != -1) {
        close(fdsocket);
        fdsocket = -1;
    }
}

void network_init(Cell owner, int ia_override, void (*init)(Cell owner, int ia_override, void (*actualiser_adversaire)(PGame game, Cell me, State state)), char address[ADDRESS_LENGTH], int port) {
    // Save address and port
    strcpy(saved_address, address);
    saved_port = port;

    // Et on init le reste comme d'habitude
    init(owner, ia_override, network_update);
}

void network_update(PGame game, Cell me, State state) {
    // If it is my turn
    if (game->playing == me) {
        if (game->has_last_move) {
            // Send last move to opponent
            char *move = move_to_string(game->last_move);
            do {
                network_connect();
                int n = write(fdclient, move, 6);
                if (n <= 0) {
                    network_disconnect();
                }
            } while(fdclient == -1);
        }
    }

    // End of game
    if (state != STATE_PLAYING) {
        return;
    }
    
    if (game->playing == me) {
        // Receive opponent's move
        char *opponent_move = malloc(sizeof(char) * 6);
        Move result = MOVE_NONE;
        do {
            network_connect();
            int n = read(fdclient, opponent_move, sizeof(opponent_move));
            if (n <= 0) {
                network_disconnect();
            }
            result = move_from_string(opponent_move);
            if (move_apply(result, me, game->board, 0) == 0) {
                result = MOVE_NONE;
            }
        } while(fdclient == -1 || result == MOVE_NONE);
        game_turn(game, result);
    }
}
