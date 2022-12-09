#include <assert.h>
#include "scored_move.test.h"

void test_scored_move_new() {
    Move m1 = move_create(1, 2, 3, 4);
    Move m2 = move_create(5, 6, 7, 8);
    ScoredMove scored_move = scored_move_new(m1, m2, 1234);
    assert(scored_move_move(scored_move) == m1);
    assert(scored_move_root(scored_move) == m2);
    assert(scored_move_score(scored_move) == 1234);
}

void test_scored_move_compute() {
    // TODO
    // les points par rapport au centre
    // la proximité entre nos pions
    // la proximité avec des pions adverses
}

void test_scored_move_compute_victory(){
    Board board;
    board_create(board);
    board_set_cell(board, 1, 0, CELL_BLACK);
    board_set_cell(board, 2, 0, CELL_BLACK);
    board_set_cell(board, 7, 0, CELL_EMPTY);
    board_set_cell(board, 7, 1, CELL_EMPTY);
    Move move = move_from_string("C1:A1");
    assert(scored_move_compute(move, CELL_BLACK, board)>0);
}

void test_scored_move_compute_defeat(){
    Board board;
    board_create(board);
    Move move = move_create(0,7,0,8);
    assert(scored_move_compute(move, CELL_WHITE, board)<0);
}

void test_scored_move_compute_center(){
    Board board;
    board_create(board);
    board_set_cell(board, 4, 2, CELL_BLACK);
    board_set_cell(board, 7, 7, CELL_EMPTY);
    Move move1 = move_from_string("E3:E4");
    Move move2 = move_from_string("E3:E2");
    assert(scored_move_compute(move1, CELL_BLACK, board)>scored_move_compute(move2, CELL_BLACK, board));
}

void test_scored_move() {
    test_scored_move_new();
    test_scored_move_compute();
    test_scored_move_compute_victory();
    test_scored_move_compute_defeat();
    test_scored_move_compute_center();
}
