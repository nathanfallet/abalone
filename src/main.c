#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "terminal.h"
#include "gui.h"
#include "ia.h"
#include "network.h"

void print_help() {
    printf("Usage: ./abalone [options]\n");
    printf(" -l <noir/blanc> : jeu local contre l'IA\n");
    printf(" -s <port> : lancer un serveur sur le port donné\n");
    printf(" -c <adresse>:<port> : se connecter à un serveur distant\n");
}

void default_init(Cell me, void (*update)(PGame game, Cell me, State state)) {
    //terminal_init(me, update);
    gui_init(me, update);
}

int main(int argc, char* argv[]){
    // Check arg count; else show help
    if (argc != 3) {
        print_help();
        return 1;
    }

    switch (argv[1][1]) {
        case 'l':
            if (strcmp(argv[2], "noir") == 0) {
                default_init(Black, ia_update);
            } else if (strcmp(argv[2], "blanc") == 0) {
                default_init(White, ia_update);
            } else {
                print_help();
                return 1;
            }
            break;
        case 's':
            network_init(White, default_init, NULL, atoi(argv[2]));
            break;
        case 'c':
            network_init(Black, default_init, strtok(argv[2], ":"), atoi(strtok(NULL, ":")));
            break;
        default:
            print_help();
            return 1;
    }

    return 0;
}
