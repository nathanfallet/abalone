#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "network.h"

int fdsocket;
int fdclient;

void network_init(Cell owner, void (*init)(Cell owner, void (*actualiser_adversaire)(PGame game, Cell me, State state)), char address[ADDRESS_LENGTH], int port) {
    if (address == NULL) {
        // On est le serveur
        if ((fdsocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
            printf("Error: Could not create socket: %s\n", strerror(errno));
            exit(1);
        }
        int opt = 1;
        if (setsockopt(fdsocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) != 0) {
            printf("Error: Could not set options to socket: %s\n", strerror(errno));
            exit(1);
        }
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port = htons(port);

        // Bind and listen
        if (bind(fdsocket, (struct sockaddr *) &addr, sizeof(addr)) != 0) {
            printf("Error: Could not bind socket: %s\n", strerror(errno));
            exit(1);
        }
        if (listen(fdsocket, 1) != 0) {
            printf("Error: Could not listen on socket: %s\n", strerror(errno));
            exit(1);
        }

        // Accept connections
        fdclient = accept(fdsocket, NULL, NULL);
        if (fdclient == -1) {
            printf("Error: Could not accept client on socket: %s\n", strerror(errno));
            exit(1);
        }
    } else {
        // On est le client
        fdclient = socket(AF_INET, SOCK_STREAM, 0);
        if (fdclient == -1) {
            printf("Error: Could not create socket: %s\n", strerror(errno));
            exit(1);
        }
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = inet_addr(address);
        addr.sin_port = htons(port);
        if (connect(fdclient, (struct sockaddr *) &addr, sizeof(addr)) != 0) {
            printf("Error: Could not connect socket: %s\n", strerror(errno));
            exit(1);
        }
    }

    // Et on init le reste comme d'habitude
    init(owner, network_update);
}

void network_update(PGame game, Cell me, State state) {
    // End of game
    if (state != In_progress) {
        return;
    }

    // If it is my turn
    if (game->playing == me) {
        if (game->has_last_move) {
            // Send last move to opponent
            char *move = move_to_string(game->last_move);
            write(fdclient, move, sizeof(move));
        }

        // Receive opponent's move
        // String is 6 chars long ("A1:A2\0")
        char *opponent_move = malloc(sizeof(char) * 6);
        read(fdclient, opponent_move, sizeof(opponent_move));
        Move result = move_from_string(opponent_move);
        game_turn(game, result);
    }
}
