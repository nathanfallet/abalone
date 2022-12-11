#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "constants.h"
#include "terminal.h"
#include "gui.h"
#include "ia.h"
#include "network.h"

void print_help() {
    printf("Usage: ./abalone [options] (-m <me/ia>)\n");
    printf(" -l <noir/blanc> : jeu local contre l'IA\n");
    printf(" -s <port> : lancer un serveur sur le port donné\n");
    printf(" -c <adresse>:<port> : se connecter à un serveur distant\n");
}

void default_init(Cell me, int ia_override, void (*update)(Game *game, Cell me, State state), char address[ADDRESS_LENGTH], int port) {
    if (INIT_DEFAULT == INIT_TERMINAL) {
        terminal_init(me, ia_override, update, address, port);
    }
    else if (INIT_DEFAULT == INIT_GUI) {
        gui_init(me, ia_override, update, address, port);
    }
}

int main(int argc, char *argv[]) {
    // Init du random
    srand(time(NULL));

    // Status
    int init = INIT_NONE;
    Cell me = CELL_BLACK;
    int ia_override = -1;
    char address[ADDRESS_LENGTH] = "";
    int port = 0;

    // Handle arguments
    int i = 1;
    while (i < argc) {
        if (argv[i][0] != '-') {
            print_help();
            return 1;
        }
        switch (argv[i][1]) {
        case 'l':
            if (strcmp(argv[i + 1], "noir") == 0) {
                init = INIT_DEFAULT;
            }
            else if (strcmp(argv[i + 1], "blanc") == 0) {
                init = INIT_DEFAULT;
                me = CELL_WHITE;
            }
            else {
                print_help();
                return 1;
            }
            break;
        case 's':
            init = INIT_NETWORK;
            me = CELL_WHITE;
            port = atoi(argv[i + 1]);
            break;
        case 'c':
            init = INIT_NETWORK;
            strcpy(address, strtok(argv[i + 1], ":"));
            port = atoi(strtok(NULL, ":"));
            break;
        case 'm':
            if (strcmp(argv[i + 1], "me") == 0) {
                ia_override = 0;
            }
            else if (strcmp(argv[i + 1], "ia") == 0) {
                ia_override = 1;
            }
            else {
                print_help();
                return 1;
            }
            break;
        default:
            print_help();
            return 1;
        }
        i += 2;
    }

    // IA override default value
    if (ia_override == -1) {
        ia_override = init == INIT_NETWORK;
    }

    // Call
    switch (init) {
    case INIT_DEFAULT:
        default_init(me, ia_override, ia_update, address, port);
        break;
    case INIT_NETWORK:
        network_init(me, ia_override, default_init, address, port);
        break;
    default:
        print_help();
        return 1;
    }

    return 0;
}
