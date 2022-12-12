#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <time.h>
#include "ia.h"

/* Minimax algorithm. It returns a decision (move) and takes the player who plays and the actual board into account */

ScoredMove ia_minimax_compare(Cell me, Board board, Move root, int profondeur, int max, int threshold) {
    /* Recovering available Move */
    Move moves[MOVE_LIST_SIZE];
    move_available(max ? me : cell_opposite(me), board, moves);

    ScoredMove move_selected = MOVE_NONE;
    Move move = MOVE_NONE;

    int i = 0;
    while ((move = moves[i]) != MOVE_NONE) {
        /* Verification of threshold */
        if (move_selected != MOVE_NONE && (max ? threshold <= scored_move_score(move_selected) : threshold >= scored_move_score(move_selected))) {
            break;
        }

        /* Applying Move */
        Board copy;
        board_clone(board, copy);
        move_apply(move, max ? me : cell_opposite(me), copy, 1);
        ScoredMove sc = MOVE_NONE;

        State state = board_state(copy);
        if (state != STATE_PLAYING) {
            /* Reaching the end game (priority) */
            Cell winner = state == STATE_WIN_BLACK ? CELL_BLACK : CELL_WHITE;
            sc = scored_move_new(
                move,
                root != MOVE_NONE ? root : move,
                winner == me ? WEIGHT_WIN_DIRECT : -WEIGHT_WIN_DIRECT);

            /* If it's a assured victory, we're not even going to continue building the tree */
            if (winner == (max ? me : cell_opposite(me))) {
                return sc;
            }
        }
        else if (profondeur > 1) {
            /* We go deeper */
            int child_threshold = max ? INT_MIN : INT_MAX;
            if (move_selected != MOVE_NONE) {
                child_threshold = scored_move_score(move_selected);
            }
            sc = ia_minimax_compare(me, copy, move, profondeur - 1, max == 0, child_threshold);
            if (root != MOVE_NONE) {
                sc = scored_move_new(
                    scored_move_move(sc),
                    root,
                    scored_move_score(sc));
            }
        }
        else {
            /* We have reached maximum deep, we compute the score */
            sc = scored_move_new(
                move,
                root != MOVE_NONE ? root : move,
                scored_move_compute(me, copy));
        }

        /* Check for the Move selection */
        int selected_score = scored_move_score(move_selected);
        int score = scored_move_score(sc);
        if (move_selected == MOVE_NONE ||
            (max ? score > selected_score : score < selected_score) ||
            (score == selected_score && rand() % 8 == 0)) {
            move_selected = sc;
        }

        /* Next Move */
        i++;
    }

    return move_selected;
}

/* Implementation of basics functions to interact with the game */

void ia_update(Game *game, Cell me, State state) {
    /* End of game */
    if (state != STATE_PLAYING) {
        return;
    }

    /* If it's my turn : */
    if (game->playing == me) {
        Move move = ia_minimax(me, game->board, 4);
        game_turn(game, move);
    }
}

Move ia_minimax(Cell me, Board board, int profondeur) {
    /* Get a move */
    time_t start = time(NULL);
    ScoredMove move = ia_minimax_compare(me, board, MOVE_NONE, profondeur, 1, INT_MAX);
    time_t end = time(NULL);

    /* Sleep if we responded too quickly */
    #ifndef TEST
    if (difftime(end, start) < 3) {
        sleep(3 - difftime(end, start));
    }
    #endif

    return scored_move_root(move);
}
