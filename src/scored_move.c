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
            // point par rapport au centre
            if (current == me)
                score += WEIGHT_CENTER * (20 - abs(4 - i) - abs(4 - j) - abs(3 - i) - abs(3 - j));
            if (current == cell_opposite(me))
                score -= 2 * WEIGHT_CENTER * (20 - abs(4 - i) - abs(4 - j - abs(3 - i) - abs(3 - j)));
            // Count the number of pawns
            if (current == me)
                pawn_me += 1;
            if (current == cell_opposite(me))
                pawn_opponent += 1;
            // Regarde la proximité par rapport au autres pions
            if (current == me) {
                // regarde si on est aligné à 2 verticalement
                if (board_get_cell(board, i + 1, j) == me) {
                    score += WEIGHT_NEIGHBOUR;
                    // regarde vers le bas si on est sur la même colonne que l'adversaire
                    for (int k = i + 1; k < BOARD_SIZE; k++) {
                        // compte le nombre d'aversaire sur la colonne
                        if (board_get_cell(board, i + k, j) == cell_opposite(me)) {
                            count += 1;
                            // enregistre la distance du plus proche adversaire
                            if (distance == 0) {
                                distance = k;
                            }
                        }
                    }
                    // vérifie si on peut pousser l'aversaire sur la colonne ou non
                    if (count == 1) {
                        score += 3 * WEIGHT_OPPOSITE / (distance + 1);
                    }
                    else {
                        score -= WEIGHT_OPPOSITE - distance;
                    }
                    count = 0;
                    distance = 0;
                    // regarde vers le haut si on est sur la même colonne que l'adversaire
                    for (int k = i; k > 0; k--) {
                        // compte le nombre d'aversaire sur la colonne
                        if (board_get_cell(board, i + k, j) == cell_opposite(me)) {
                            count += 1;
                            // enregistre la distance du plus proche adversaire
                            if (distance == 0) {
                                distance = k;
                            }
                        }
                    }
                    // vérifie si on peut pousser l'aversaire sur la colonne ou non
                    if (count == 1) {
                        score += 3 * WEIGHT_OPPOSITE / (distance + 1);
                    }
                    else {
                        score -= WEIGHT_OPPOSITE - distance;
                    }
                    count = 0;
                    distance = 0;
                    // regarde si on est aligné à 3 verticalement
                    if (board_get_cell(board, i + 2, j) == me) {
                        score += 2 * WEIGHT_NEIGHBOUR;
                        // regarde vers le bas si on est sur la même colonne que l'adversaire
                        for (int k = i + 2; k < BOARD_SIZE; k++) {
                            // compte le nombre d'aversaire sur la colonne
                            if (board_get_cell(board, i + k, j) == cell_opposite(me)) {
                                count += 1;
                                // enregistre la distance du plus proche adversaire
                                if (distance == 0) {
                                    distance = k;
                                }
                            }
                        }
                        // vérifie si on peut pousser l'aversaire sur la colonne ou non
                        if (count <= 2) {
                            score += 3 * WEIGHT_OPPOSITE / (distance + 1);
                        }
                        count = 0;
                        distance = 0;
                        // regarde vers le haut si on est sur la même colonne que l'adversaire
                        for (int k = i - 2; k > 0; k--) {
                            // compte le nombre d'aversaire sur la colonne
                            if (board_get_cell(board, i + k, j) == cell_opposite(me)) {
                                count += 1;
                                // enregistre la distance du plus proche adversaire
                                if (distance == 0) {
                                    distance = k;
                                }
                            }
                        }
                        // vérifie si on peut pousser l'aversaire sur la colonne ou non
                        if (count <= 2) {
                            score += 3 * WEIGHT_OPPOSITE;
                        }
                        count = 0;
                        distance = 0;
                    }
                }
                // regarde si on est aligné à 2 horizontalement
                if (board_get_cell(board, i, j + 1) == me) {
                    score += WEIGHT_NEIGHBOUR;
                    // regarde vers la droite si on est sur la même ligne que l'adversaire
                    for (int k = j; k < BOARD_SIZE; k++) {
                        // compte le nombre d'aversaire sur la ligne
                        if (board_get_cell(board, i, j + k) == cell_opposite(me)) {
                            count += 1;
                            // enregistre la distance du plus proche adversaire
                            if (distance == 0) {
                                distance = k;
                            }
                        }
                    }
                    // vérifie si on peut pousser l'aversaire sur la ligne ou non
                    if (count == 1) {
                        score += 3 * WEIGHT_OPPOSITE / (distance + 1);
                    }
                    else {
                        score -= WEIGHT_OPPOSITE - distance;
                    }
                    count = 0;
                    distance = 0;
                    // regarde vers la gauche si on est sur la même ligne que l'adversaire
                    for (int k = j; k > 0; k--) {
                        // compte le nombre d'aversaire sur la ligne
                        if (board_get_cell(board, i, j + k) == cell_opposite(me)) {
                            count += 1;
                            // enregistre la distance du plus proche adversaire
                            if (distance == 0) {
                                distance = k;
                            }
                        }
                    }
                    // vérifie si on peut pousser l'aversaire sur la ligne ou non
                    if (count == 1) {
                        score += 3 * WEIGHT_OPPOSITE / (distance + 1);
                    }
                    else {
                        score -= WEIGHT_OPPOSITE - distance;
                    }
                    count = 0;
                    distance = 0;
                    // regarde si on est aligné à 3 horizontalement
                    if (board_get_cell(board, i, j + 2) == me) {
                        score += 2 * WEIGHT_NEIGHBOUR;
                        // regarde vers la droite si on est sur la même ligne que l'adversaire
                        for (int k = j + 2; k < BOARD_SIZE; k++) {
                            // compte le nombre d'aversaire sur la ligne
                            if (board_get_cell(board, i, j + k) == cell_opposite(me)) {
                                count += 1;
                                // enregistre la distance du plus proche adversaire
                                if (distance == 0) {
                                    distance = k;
                                }
                            }
                        }
                        // vérifie si on peut pousser l'aversaire sur la ligne ou non
                        if (count <= 2) {
                            score += 3 * WEIGHT_OPPOSITE / (distance + 1);
                        }
                        count = 0;
                        distance = 0;
                        // regarde vers la gauche si on est sur la même ligne que l'adversaire
                        for (int k = j - 2; k > 0; k--) {
                            // compte le nombre d'aversaire sur la ligne
                            if (board_get_cell(board, i, j + k) == cell_opposite(me)) {
                                count += 1;
                                // enregistre la distance du plus proche adversaire
                                if (distance == 0) {
                                    distance = k;
                                }
                            }
                        }
                        // vérifie si on peut pousser l'aversaire sur la ligne ou non
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