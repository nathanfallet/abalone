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

void test_scored_move_compute_two_push_one_bottom(){
    Board board;
    board_create(board);
    board_set_cell(board, 6, 7, CELL_WHITE);
    board_set_cell(board, 5, 7, CELL_BLACK);
    board_set_cell(board, 4, 7, CELL_BLACK);
    board_set_cell(board, 7, 7, CELL_EMPTY);
    board_set_cell(board, 6, 6, CELL_EMPTY);
    board_set_cell(board, 0, 7, CELL_EMPTY);
    Move move1 = move_from_string("E8:H8");
    Move move2 = move_from_string("F8:D8");
    assert(scored_move_compute(move1, CELL_BLACK, board)>scored_move_compute(move2, CELL_BLACK, board));
}

void test_scored_move_compute_two_push_one_top(){
    Board board;
    board_create(board);
    board_set_cell(board, 6, 7, CELL_BLACK);
    board_set_cell(board, 6, 6, CELL_EMPTY);
    board_set_cell(board, 5, 7, CELL_WHITE);
    board_set_cell(board, 0, 7, CELL_EMPTY);
    Move move1 = move_from_string("H8:F8");
    Move move2 = move_from_string("G8:G7");
    //assert(scored_move_compute(move1, CELL_BLACK, board)>scored_move_compute(move2, CELL_BLACK, board));
}

void test_scored_move_compute_three_push_two_bottom(){
    Board board;
    board_create(board);
    board_set_cell(board, 7, 7, CELL_EMPTY);
    board_set_cell(board, 6, 6, CELL_EMPTY);
    board_set_cell(board, 7, 6, CELL_EMPTY);
    board_set_cell(board, 0, 7, CELL_EMPTY);
    board_set_cell(board, 1, 6, CELL_EMPTY);
    board_set_cell(board, 6, 7, CELL_WHITE);
    board_set_cell(board, 5, 7, CELL_WHITE);
    board_set_cell(board, 4, 7, CELL_BLACK);
    board_set_cell(board, 3, 7, CELL_BLACK);
    board_set_cell(board, 2, 7, CELL_BLACK);
    Move move1 = move_from_string("C8:F8");
    Move move2 = move_from_string("C8:E7");
    assert(scored_move_compute(move1, CELL_BLACK, board)>scored_move_compute(move2, CELL_BLACK, board));
}

void test_scored_move_compute_three_push_two_top(){
    Board board;
    board_create(board);
    board_set_cell(board, 7, 7, CELL_EMPTY);
    board_set_cell(board, 6, 6, CELL_EMPTY);
    board_set_cell(board, 7, 6, CELL_EMPTY);
    board_set_cell(board, 0, 7, CELL_EMPTY);
    board_set_cell(board, 1, 6, CELL_EMPTY);
    board_set_cell(board, 6, 7, CELL_BLACK);
    board_set_cell(board, 5, 7, CELL_BLACK);
    board_set_cell(board, 4, 7, CELL_BLACK);
    board_set_cell(board, 3, 7, CELL_WHITE);
    board_set_cell(board, 2, 7, CELL_WHITE);
    Move move1 = move_from_string("G8:D8");
    Move move2 = move_from_string("G8:E7");
    //assert(scored_move_compute(move1, CELL_BLACK, board)>scored_move_compute(move2, CELL_BLACK, board));
}

void test_scored_move_compute_two_push_one_right(){
    Board board;
    board_create(board);
    board_set_cell(board, 6, 6, CELL_WHITE);
    board_set_cell(board, 5, 6, CELL_BLACK);
    board_set_cell(board, 0, 7, CELL_EMPTY);
    Move move1 = move_from_string("G5:G7");
    Move move2 = move_from_string("G5:F6");
    //assert(scored_move_compute(move1, CELL_BLACK, board)>scored_move_compute(move2, CELL_BLACK, board));
}

void test_scored_move_compute_two_push_one_left(){
    Board board;
    board_create(board);
    board_set_cell(board, 6, 1, CELL_WHITE);
    board_set_cell(board, 5, 1, CELL_BLACK);
    board_set_cell(board, 0, 0, CELL_EMPTY);
    Move move1 = move_from_string("G4:G2");
    Move move2 = move_from_string("G3:F4");
    //assert(scored_move_compute(move1, CELL_BLACK, board)>scored_move_compute(move2, CELL_BLACK, board));
}

void test_scored_move_compute_three_push_two_right(){
    Board board;
    board_create(board);
    board_set_cell(board, 6, 6, CELL_WHITE);
    board_set_cell(board, 6, 5, CELL_BLACK);
    board_set_cell(board, 0, 0, CELL_EMPTY);
    board_set_cell(board, 0, 1, CELL_EMPTY);
    board_set_cell(board, 6, 0, CELL_BLACK);
    board_set_cell(board, 5, 0, CELL_BLACK);
    Move move1 = move_from_string("G3:G6");
    Move move2 = move_from_string("G3:E5");
    //assert(scored_move_compute(move1, CELL_BLACK, board)>scored_move_compute(move2, CELL_BLACK, board));
}

void test_scored_move_compute_three_push_two_left(){
    Board board;
    board_create(board);
    board_set_cell(board, 6, 1, CELL_WHITE);
    board_set_cell(board, 6, 2, CELL_WHITE);
    board_set_cell(board, 0, 0, CELL_EMPTY);
    board_set_cell(board, 1, 1, CELL_EMPTY);
    board_set_cell(board, 6, 7, CELL_BLACK);
    board_set_cell(board, 5, 7, CELL_BLACK);
    Move move1 = move_from_string("G6:G3");
    Move move2 = move_from_string("G4:F6");
    //assert(scored_move_compute(move1, CELL_BLACK, board)>scored_move_compute(move2, CELL_BLACK, board));
}

void test_scored_move() {
    test_scored_move_new();
    test_scored_move_compute();
    test_scored_move_compute_victory();
    test_scored_move_compute_defeat();
    test_scored_move_compute_center();
    test_scored_move_compute_two_push_one_bottom();
    test_scored_move_compute_two_push_one_top();
    test_scored_move_compute_three_push_two_bottom();
    test_scored_move_compute_three_push_two_top();
    test_scored_move_compute_two_push_one_right();
    test_scored_move_compute_two_push_one_left();
    test_scored_move_compute_three_push_two_right();
    test_scored_move_compute_three_push_two_left();
}