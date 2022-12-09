#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include "ia.h"

// Algorithme minimax. Il retourne une décision (move) et prend en compte le joueur qui joue ainsi que le board actuel

ScoredMove compare(Cell me, Cell playing, Board board, Move root, int profondeur, int max, int threshold) {
    // On récupère les moves possibles
    Move moves[MOVE_LIST_SIZE];
    move_available(playing, board, moves);

    ScoredMove move_selected = MOVE_NONE;
    Move move = MOVE_NONE;

    int i = 0;
    while ((move = moves[i]) != MOVE_NONE) {
        // Check du threshold
        if (move_selected != MOVE_NONE && (
            max ? threshold >= scored_move_score(move_selected) : threshold <= scored_move_score(move_selected)
        )) {
            break;
        }

        // Itération des moves possibles
        ScoredMove sc = MOVE_NONE;

        // On applique le move
        Board copy;
        board_clone(board, copy);
        if (move_apply(move, playing, copy, 1)) {
            State state = board_state(copy);
            if (state != STATE_PLAYING) {
                // On a atteint la fin du jeu (prioritaire)
                Cell winner = state == STATE_WIN_BLACK ? CELL_BLACK : CELL_WHITE;
                sc = scored_move_new(
                    move,
                    root != MOVE_NONE ? root : move,
                    winner == me ? WEIGHT_WIN : -WEIGHT_WIN
                );
            } else if (profondeur > 1) {
                // On continue plus profond
                int child_threshold = max ? INT_MAX : INT_MIN;
                if (move_selected != MOVE_NONE) {
                    child_threshold = scored_move_score(move_selected);
                }
                sc = compare(me, cell_opposite(playing), copy, move, profondeur - 1, max == 0, child_threshold);
                if (root != MOVE_NONE) {
                    sc = scored_move_new(
                        scored_move_move(sc),
                        root,
                        scored_move_score(sc)
                    );
                }
            } else {
                // On a atteint la profondeur max, on calcule le score
                sc = scored_move_new(
                    move,
                    root != MOVE_NONE ? root : move,
                    scored_move_compute(me, copy)
                );
            }

            // Check pour la sélection du move
            int selected_score = scored_move_score(move_selected);
            int score = scored_move_score(sc);
            if (sc != MOVE_NONE && (
                move_selected == MOVE_NONE ||
                (max ? score > selected_score : score < selected_score) ||
                (score == selected_score && rand() % 8 == 0)
            )) {
                move_selected = sc;
            }
        }

        // Move suivant
        i++;
    }

    if (move_selected == MOVE_NONE) {
        // Move par défaut (pour éviter les erreurs)
        return scored_move_new(root, root, 0);
    }
    return move_selected;
}

// Implémentation des fonctions de base pour intéragir avec le jeu

void ia_init(Cell owner, void (*refresh_opponent)(PGame game, Cell me, State state)) {
    PGame game = game_new(owner, 0);
    game->refresh = ia_update;
    game->refresh_opponent = refresh_opponent;

    game_start(game);
}

void ia_update(PGame game, Cell me, State state){
    // Fin de partie
    if (state != STATE_PLAYING) {
        return;
    }

    // Si c'est mon tour:
    if (game->playing == me) {
        Move move = ia_minimax(me, game->board, 4);
        game_turn(game, move);
    }
}

Move ia_minimax(Cell me, Board board, int profondeur) {
    ScoredMove move = compare(me, me, board, MOVE_NONE, profondeur, 1, INT_MIN);
    return scored_move_root(move);
}
