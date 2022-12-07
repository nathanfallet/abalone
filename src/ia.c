#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "ia.h"

// Algorithme minimax. Il retourne une décision (move) et prend en compte le joueur qui joue ainsi que le board actuel

ScoredMove *compare(Cell me, Board board, Move *root, int profondeur, int max, int threshold) {
    // Retourne le move avec le score le plus élevé/faible
    // On calcul le score si la profondeur atteint 0,
    // sinon on garde le plus grand/petit score des enfants
    
    List *moves= move_available(me, board);
    ScoredMove *move_selected = NULL;
    for (int i=1; i <= list_taille(moves); i++) {
        // Itération des moves possibles
        Move *move = list_accede(i, moves);
        ScoredMove *sc;

        // Cas de la profondeur
        if (profondeur > 0) {
            // On continue plus profond
            Board copy;
            board_clone(board, copy);
            if (move_apply(*move, me, copy, 1)) {
                sc = compare(cell_opposite(me), copy, move, profondeur - 1, max == 0, threshold);
                if (root != NULL) {
                    sc->root = root;
                }
            }
        } else {
            // On a atteint la profondeur max, on calcule le score
            sc = score_move_new(
                move,
                root != NULL ? root : move,
                compute_score(*move, me, board)
            );
        }

        // Check pour la sélection du move
        if (sc != NULL && (
            move_selected == NULL ||
            (max ? sc->score > move_selected->score : sc->score < move_selected->score) ||
            (sc->score = move_selected->score && rand() % 2)
        )) {
            move_selected=sc;
        }
    }

    if (move_selected == NULL) {
        // Move par défaut (pour éviter les erreurs)
        return score_move_new(root, root, 0);
    }
    return move_selected;
}

Move minimax(Cell me, Board board, int profondeur) {
    ScoredMove *move = compare(me, board, NULL, profondeur, 1, 0);
    return *move->root;
}

// Implémentation des fonctions de base pour intéragir avec le jeu

void ia_init(Cell owner, void (*refresh_opponent)(PGame game, Cell me, State state)) {
    PGame game = new_game(owner);
    game->refresh = ia_update;
    game->refresh_opponent = refresh_opponent;

    game_start(game);
}

void ia_update(PGame game, Cell me, State state){
    // Fin de partie 
    if (state != In_progress) {
        return;
    }

    // Si c'est mon tour:
    if (game->playing == me) {
        Move move = minimax(me, game->board, 3);
        game_turn(game, move);
    }
}
