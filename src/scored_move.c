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
    int pawn_me = 0;
    int pawn_opponent = 0;

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            Cell current = board_get_cell(board, i, j);
            int distance = 0;
            int count = 0;
            //position of a point compared to the center
            if (current == me)
                score += WEIGHT_CENTER * (20 - abs(4 - i) - abs(4 - j) - abs(3 - i) - abs(3 - j));
            if (current == cell_opposite(me))
                score -= 2 * WEIGHT_CENTER * (20 - abs(4 - i) - abs(4 - j) - abs(3 - i) - abs(3 - j));
            // Count the number of pawns
            if (current == me)
                pawn_me += 1;
            if (current == cell_opposite(me))
                pawn_opponent += 1;
            // Looks the proximity to other pawns
            if (current == me) {
                // checks if 2 pawns are aligned vertically
                if (board_get_cell(board, i + 1, j) == me) {
                    score += WEIGHT_NEIGHBOUR;
                    // checks down on the same column if there's an opponent
                    for (int k = i + 1; k < BOARD_SIZE; k++) {
                        // counts the number of opponents' pawns on the same column
                        if (board_get_cell(board, i + k, j) == cell_opposite(me)) {
                            count += 1;
                            // saves the distance to the first opponents' pawn
                            if (distance == 0) {
                                distance = k;
                            }
                        }
                    }
                    // checks if it's possible to push the opponents' pawns on the column
                    if (count == 1) {
                        score += 3 * WEIGHT_OPPOSITE / (distance + 1);
                    }
                    else {
                        score -= WEIGHT_OPPOSITE - distance;
                    }
                    count = 0;
                    distance = 0;
                    // checks down on the same column if there's an opponent
                    for (int k = i; k > 0; k--) {
                        // counts the number of opponents' pawns on the same column
                        if (board_get_cell(board, i + k, j) == cell_opposite(me)) {
                            count += 1;
                            // saves the distance to the first opponents' pawn
                            if (distance == 0) {
                                distance = k;
                            }
                        }
                    }
                    // checks if it's possible to push the opponents' pawns on the column
                    if (count == 1) {
                        score += 3 * WEIGHT_OPPOSITE / (distance + 1);
                    }
                    else {
                        score -= WEIGHT_OPPOSITE - distance;
                    }
                    count = 0;
                    distance = 0;
                    // checks if 3 pawns are aligned vertically
                    if (board_get_cell(board, i + 2, j) == me) {
                        score += WEIGHT_NEIGHBOUR;
                        // checks up on the same column if there's an opponent
                        for (int k = i + 2; k < BOARD_SIZE; k++) {
                            // counts the number of opponents' pawns on the same column
                            if (board_get_cell(board, i + k, j) == cell_opposite(me)) {
                                count += 1;
                                // saves the distance to the first opponents' pawn
                                if (distance == 0) {
                                    distance = k;
                                }
                            }
                        }
                        // checks if it's possible to push the opponents' pawns on the column
                        if (count <= 2) {
                            score += 3 * WEIGHT_OPPOSITE / (distance + 1);
                        }
                        count = 0;
                        distance = 0;
                        // checks up if opponents' pawns are on the same column as ours
                        for (int k = i - 2; k > 0; k--) {
                            // counts the number of opponents' pawns on the same column
                            if (board_get_cell(board, i + k, j) == cell_opposite(me)) {
                                count += 1;
                                // saves the distance to the first opponents' pawn
                                if (distance == 0) {
                                    distance = k;
                                }
                            }
                        }
                        // checks if it's possible to push the opponents' pawns on the column
                        if (count <= 2) {
                            score += 3 * WEIGHT_OPPOSITE / (distance + 1);
                        }
                        count = 0;
                        distance = 0;
                    }
                }
                // checks if 2 of our pawns are aligned horizontally
                if (board_get_cell(board, i, j + 1) == me) {
                    score += WEIGHT_NEIGHBOUR;
                    // looks to the right if opponents' pawns are on the same line as ours
                    for (int k = j; k < BOARD_SIZE; k++) {
                        // counts the number of opponents' pawns on the same line
                        if (board_get_cell(board, i, j + k) == cell_opposite(me)) {
                            count += 1;
                            // saves the distance to the first opponents' pawn
                            if (distance == 0) {
                                distance = k;
                            }
                        }
                    }
                    // checks if it's possible to push the opponents' pawns on the line
                    if (count == 1) {
                        score += 3 * WEIGHT_OPPOSITE / (distance + 1);
                    }
                    else {
                        score -= WEIGHT_OPPOSITE - distance;
                    }
                    count = 0;
                    distance = 0;
                    /// looks to the left if opponents' pawns are on the same line as ours
                    for (int k = j; k > 0; k--) {
                        // counts the number of opponents' pawns on the same line
                        if (board_get_cell(board, i, j + k) == cell_opposite(me)) {
                            count += 1;
                            // saves the distance to the first opponents' pawn
                            if (distance == 0) {
                                distance = k;
                            }
                        }
                    }
                    // checks if it's possible to push the opponents' pawns on the line
                    if (count == 1) {// counts the number of opponents' pawns on the same column
                        score += 3 * WEIGHT_OPPOSITE / (distance + 1);
                    }
                    else {
                        score -= WEIGHT_OPPOSITE - distance;
                    }
                    count = 0;
                    distance = 0;
                    // checks if 3 of our pawns are aligned horizontally
                    if (board_get_cell(board, i, j + 2) == me) {
                        score += WEIGHT_NEIGHBOUR;
                        // looks to the right if opponents' pawns are on the same line as ours
                        for (int k = j + 2; k < BOARD_SIZE; k++) {
                            // counts the number of opponents' pawns on the same line
                            if (board_get_cell(board, i, j + k) == cell_opposite(me)) {
                                count += 1;
                                // saves the distance to the first opponents' pawn
                                if (distance == 0) {
                                    distance = k;
                                }
                            }
                        }
                        // checks if it's possible to push the opponents' pawns on the line
                        if (count <= 2) {
                            score += 3 * WEIGHT_OPPOSITE / (distance + 1);
                        }
                        count = 0;
                        distance = 0;
                        // looks to the left if opponents' pawns are on the same line as ours
                        for (int k = j - 2; k > 0; k--) {
                            // counts the number of opponents' pawns on the same line
                            if (board_get_cell(board, i, j + k) == cell_opposite(me)) {
                                count += 1;
                                // saves the distance to the first opponents' pawn
                                if (distance == 0) {
                                    distance = k;
                                }
                            }
                        }
                        // checks if it's possible to push the opponents' pawns on the line
                        if (count <= 2) {
                            score += 3 * WEIGHT_OPPOSITE / (distance + 1);
                        }
                    }
                }
            }
        }
    }

    if (pawn_me < PAWN_TOT) {
        score -= WEIGHT_WIN;
    }
    if (pawn_opponent < PAWN_TOT) {
        score += WEIGHT_WIN;
    }

    return score;
}
