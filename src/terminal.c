#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "terminal.h"

#define color(param) printf("\033[%sm",param)

// Fonctions internes

Move terminal_read() {
    char input[6];
    scanf("%s", input);
    return move_from_string(input);
}

int display(PGame game){

    char *alpha = {"ABCDEFGH"};  // colonne lettre
    printf("\n   ");
    for(int i=1; i<=8; i++){
        printf("  %i ", i );
    }
    printf("\n");
    printf("   +-------------------------------+ \n");
    for(int i=0; i<8; i++){
        printf(" %c ",alpha[i]);
        for (int j=0; j<8 ; j++){
            printf("| ");
            switch (game->board[i][j]) {
                case Black:

                    color("31" );
                    printf("⬤ ");

                    color("00");
                    break;
                case White:

                    color("34" );
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

void terminal_update_intern(PGame game, Cell me, State state, int affichage) {
    if (affichage) {
        // Affichage
        display(game);
    }

    // Fin de la partie
    switch (state) {
        case Win_black:
            printf("Le joueur Black a gagné !\n");
            return;
        case Win_white:
            printf("Le joueur White a gagné !\n");
            return;
        case Out_of_time:
            printf("Temps écoulé !\n");
            return;
        default:
            break;
    }

    // Si c'est mon tour:
    if (game->playing == me) {
        printf("Votre coup : ");
        Move move = terminal_read();
        game_turn(game, move);
    }
}

// Fonctions publiques

void terminal_init(Cell owner, void (*refresh_opponent)(PGame game, Cell me, State state)){
    PGame game = new_game(owner);
    game->refresh = terminal_update;
    game->refresh_opponent = refresh_opponent;

    game_start(game);
}

void terminal_update(PGame game, Cell me, State state){
    terminal_update_intern(game, me, state, 1);
}

void terminal_update_no_print(PGame game, Cell me, State state) {
    terminal_update_intern(game, me, state, 0);
}

/*   example color
printf("\033[31m");        // write in red
printf("My text in RED\n");
printf("\033[00m");

      case NOIR    : printf("\033[30m" ); break;
      case ROUGE   : printf("\033[31m" ); break;
      case VERT    : printf("\033[32m" ); break;
      case ORANGE  : printf("\033[33m" ); break;
      case BLEU    : printf("\033[34m" ); break;
      case MAGENTA : printf("\033[35m" ); break;
      case CYAN    : printf("\033[36m" ); break;
      case BLANC   : printf("\033[37m" ); break;
      case JAUNE   : printf("\033[00m" ); break;
*/

