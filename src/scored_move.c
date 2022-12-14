#include <stdlib.h>
#include "scored_move.h"

ScoredMove scored_move_new(Move move, Move root, int score) {
    return move | (root << 16) | (((ScoredMove)score) << 32);
}

Move scored_move_move(ScoredMove scored_move) {
    return scored_move & 0xffff;
}

Move scored_move_root(ScoredMove scored_move) {
    return (scored_move >> 16) & 0xffff;
}

int scored_move_score(ScoredMove scored_move) {
    return (int)(scored_move >> 32);
}

int scored_move_compute(Cell me, Board board) {
    int score = 0;
    int pawns = 0;

    /* Iterate board */
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            /* Get current cell, and check things on it */
            Cell current = board_get_cell(board, i, j);
            if (current == CELL_EMPTY) {
                /* Skip in case of empty cell */
                continue;
            }

            /* Checks */
            int sign = current == me ? 1 : -1;

            /* Count the number of pawns */
            pawns += sign;

            /* Position of a point compared to the center */
            score += sign * WEIGHT_CENTER * (20 - abs(4 - i) - abs(4 - j) - abs(3 - i) - abs(3 - j));

            /* Looks the proximity to other pawns */
            for (int dir = 0; dir < 2; dir++) {
                int di = dir == 0 ? 1 : 0;
                int dj = dir == 1 ? 1 : 0;

                /* Checks if d pawns are aligned */
                int d = 1;
                while (d < 3 && board_get_cell(board, i + d * di, j + d * dj) == current) {
                    score += sign * WEIGHT_NEIGHBOUR;
                    for (int kdir = 0; kdir < 2; kdir++) {
                        int dk = kdir == 0 ? +1 : -1;
                        int count = 0;
                        int distance = 0;

                        /* Checks down on the same line/column if there's an opponent */
                        for (int k = d; k < BOARD_SIZE; k++) {
                            /* Counts the number of opponents' pawns on the same line/column */
                            if (board_get_cell(board, i + k * dk * di, j + k * dk * dj) == cell_opposite(current)) {
                                count += 1;
                                /* Save the distance to the first opponents' pawn */
                                if (distance == 0) {
                                    distance = k;
                                }
                            }
                        }

                        /* Checks if it's possible to push the opponents' pawns */
                        if (d == 1) {
                            if (count == 1) {
                                score += sign * 3 * WEIGHT_OPPOSITE / (distance + 1);
                            } else {
                                score -= sign * (WEIGHT_OPPOSITE - distance);
                            }
                        } else {
                            if (count <= 2) {
                                score += sign * 3 * WEIGHT_OPPOSITE / (distance + 1);
                            }
                        }
                    }
                    d++;
                }
            }
        }
    }

    if (pawns < 0) {
        score -= WEIGHT_WIN;
    } else if (pawns > 0) {
        score += WEIGHT_WIN;
    }

    return score;
}
