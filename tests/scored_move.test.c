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
    //Priorité des scores :
    //1 - éjecter un pion adverse
    //2 - se faire éjecter
    //3 - éloigner un pion adverse du centre
    //4 - être aligné par 3
    //5 - être au centre
    //6 - être aligné par 2
    //7 - éloigner un pion adverse du centre dans plusieurs coup (distance)
    //8 - se faire éloigner du centre dans plusieurs coup (distance)
}

void test_scored_move_compute_victory() {
    Board board;
    board_create(board);
    board_set_cell(board, 1, 0, CELL_BLACK);
    board_set_cell(board, 2, 0, CELL_BLACK);
    board_set_cell(board, 7, 0, CELL_EMPTY);
    board_set_cell(board, 7, 1, CELL_EMPTY);
    Move move = move_from_string("C1:A1");
    move_apply(move, CELL_BLACK, board, 1);
    assert(scored_move_compute(CELL_BLACK, board) > 0);
}

void test_scored_move_compute_defeat() {
    Board board;
    board_create(board);
    Move move = move_create(0, 7, 0, 8);
    move_apply(move, CELL_WHITE, board, 1);
    assert(scored_move_compute(CELL_WHITE, board) < 0);
}

void test_scored_move_compute_center() {
    Board board, copy1, copy2;
    board_create(board);
    board_set_cell(board, 4, 2, CELL_BLACK);
    board_set_cell(board, 7, 7, CELL_EMPTY);
    Move move1 = move_from_string("E3:E4");
    Move move2 = move_from_string("E3:E2");
    board_clone(board, copy1);
    board_clone(board, copy2);
    move_apply(move1, CELL_BLACK, copy1, 1);
    move_apply(move2, CELL_BLACK, copy2, 1);
    assert(scored_move_compute(CELL_BLACK, copy1) > scored_move_compute(CELL_BLACK, copy2));
}

void test_scored_move_compute_two_push_one_bottom() {
    Board board, copy1, copy2;
    board_create(board);
    board_set_cell(board, 6, 7, CELL_WHITE);
    board_set_cell(board, 5, 7, CELL_BLACK);
    board_set_cell(board, 4, 7, CELL_BLACK);
    board_set_cell(board, 7, 7, CELL_EMPTY);
    board_set_cell(board, 6, 6, CELL_EMPTY);
    board_set_cell(board, 0, 7, CELL_EMPTY);
    Move move1 = move_from_string("E8:G8");
    Move move2 = move_from_string("F8:E7");
    board_clone(board, copy1);
    board_clone(board, copy2);
    move_apply(move1, CELL_BLACK, copy1, 1);
    move_apply(move2, CELL_BLACK, copy2, 1);
    //assert(scored_move_compute(CELL_BLACK, copy1) > scored_move_compute(CELL_BLACK, copy2));
}

void test_scored_move_compute_two_push_one_top() {
    Board board, copy1, copy2;
    board_create(board);
    board_set_cell(board, 6, 7, CELL_BLACK);
    board_set_cell(board, 6, 6, CELL_EMPTY);
    board_set_cell(board, 5, 7, CELL_WHITE);
    board_set_cell(board, 0, 7, CELL_EMPTY);
    Move move1 = move_from_string("H8:F8");
    Move move2 = move_from_string("G8:G7");
    board_clone(board, copy1);
    board_clone(board, copy2);
    move_apply(move1, CELL_BLACK, copy1, 1);
    move_apply(move2, CELL_BLACK, copy2, 1);
    // assert(scored_move_compute(CELL_BLACK, copy1)>scored_move_compute(CELL_BLACK, copy2));
}

void test_scored_move_compute_three_push_two_bottom() {
    Board board, copy1, copy2;
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
    board_clone(board, copy1);
    board_clone(board, copy2);
    move_apply(move1, CELL_BLACK, copy1, 1);
    move_apply(move2, CELL_BLACK, copy2, 1);
    assert(scored_move_compute(CELL_BLACK, copy1) > scored_move_compute(CELL_BLACK, copy2));
}

void test_scored_move_compute_three_push_two_top() {
    Board board, copy1, copy2;
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
    board_clone(board, copy1);
    board_clone(board, copy2);
    move_apply(move1, CELL_BLACK, copy1, 1);
    move_apply(move2, CELL_BLACK, copy2, 1);
    // assert(scored_move_compute(CELL_BLACK, copy1)>scored_move_compute(CELL_BLACK, copy2));
}

void test_scored_move_compute_two_push_one_right() {
    Board board, copy1, copy2;
    board_create(board);
    board_set_cell(board, 6, 6, CELL_WHITE);
    board_set_cell(board, 5, 6, CELL_BLACK);
    board_set_cell(board, 0, 7, CELL_EMPTY);
    Move move1 = move_from_string("G5:G7");
    Move move2 = move_from_string("G5:F6");
    board_clone(board, copy1);
    board_clone(board, copy2);
    move_apply(move1, CELL_BLACK, copy1, 1);
    move_apply(move2, CELL_BLACK, copy2, 1);
    // assert(scored_move_compute(CELL_BLACK, copy1)>scored_move_compute(CELL_BLACK, copy2));
}

void test_scored_move_compute_two_push_one_left() {
    Board board, copy1, copy2;
    board_create(board);
    board_set_cell(board, 6, 1, CELL_WHITE);
    board_set_cell(board, 5, 1, CELL_BLACK);
    board_set_cell(board, 0, 0, CELL_EMPTY);
    Move move1 = move_from_string("G4:G2");
    Move move2 = move_from_string("G3:F4");
    board_clone(board, copy1);
    board_clone(board, copy2);
    move_apply(move1, CELL_BLACK, copy1, 1);
    move_apply(move2, CELL_BLACK, copy2, 1);
    // assert(scored_move_compute(CELL_BLACK, copy1)>scored_move_compute(CELL_BLACK, copy2));
}

void test_scored_move_compute_three_push_two_right() {
    Board board, copy1, copy2;
    board_create(board);
    board_set_cell(board, 6, 6, CELL_WHITE);
    board_set_cell(board, 6, 5, CELL_WHITE);
    board_set_cell(board, 0, 0, CELL_EMPTY);
    board_set_cell(board, 0, 1, CELL_EMPTY);
    board_set_cell(board, 6, 0, CELL_BLACK);
    board_set_cell(board, 5, 0, CELL_BLACK);
    Move move1 = move_from_string("G3:G6");
    Move move2 = move_from_string("G3:F5");
    board_clone(board, copy1);
    board_clone(board, copy2);
    move_apply(move1, CELL_BLACK, copy1, 1);
    move_apply(move2, CELL_BLACK, copy2, 1);
    //assert(scored_move_compute(CELL_BLACK, copy1)>scored_move_compute(CELL_BLACK, copy2));
}

void test_scored_move_compute_three_push_two_left() {
    Board board, copy1, copy2;
    board_create(board);
    board_set_cell(board, 6, 1, CELL_WHITE);
    board_set_cell(board, 6, 2, CELL_WHITE);
    board_set_cell(board, 0, 0, CELL_EMPTY);
    board_set_cell(board, 1, 1, CELL_EMPTY);
    board_set_cell(board, 6, 7, CELL_BLACK);
    board_set_cell(board, 5, 7, CELL_BLACK);
    Move move1 = move_from_string("G6:G3");
    Move move2 = move_from_string("G4:F6");
    board_clone(board, copy1);
    board_clone(board, copy2);
    move_apply(move1, CELL_BLACK, copy1, 1);
    move_apply(move2, CELL_BLACK, copy2, 1);
    // assert(scored_move_compute(CELL_BLACK, copy1)>scored_move_compute(CELL_BLACK, copy2));
}

void test_scored_move_compute_rule_one_over_two() {
    Board board, copy1, copy2;
    board_create(board);
    board_set_cell(board, 1, 0, CELL_BLACK);
    board_set_cell(board, 7, 0, CELL_WHITE);
    board_set_cell(board, 0, 0, CELL_EMPTY);
    Move move1 = move_from_string("B1:C1");
    Move move2 = move_from_string("H3:H1");
    board_clone(board, copy1);
    board_clone(board, copy2);
    move_apply(move1, CELL_BLACK, copy1, 1);
    move_apply(move2, CELL_BLACK, copy2, 1);
    assert(scored_move_compute(CELL_BLACK, copy1)<scored_move_compute(CELL_BLACK, copy2));
}

void test_scored_move_compute_rule_two_over_three(){
    Board board, copy1, copy2;
    board_create(board);
    board_set_cell(board, 1, 0, CELL_BLACK);
    board_set_cell(board, 4, 2, CELL_BLACK);
    board_set_cell(board, 4, 3, CELL_BLACK);
    board_set_cell(board, 4, 4, CELL_WHITE);
    board_set_cell(board, 0, 0, CELL_EMPTY);
    board_set_cell(board, 7, 0, CELL_EMPTY);
    board_set_cell(board, 6, 1, CELL_EMPTY);
    board_set_cell(board, 6, 2, CELL_EMPTY);
    Move move1 = move_from_string("B1:C1");
    Move move2 = move_from_string("E3:E5");
    board_clone(board, copy1);
    board_clone(board, copy2);
    move_apply(move1, CELL_BLACK, copy1, 1);
    move_apply(move2, CELL_BLACK, copy2, 1);
    //assert(scored_move_compute(CELL_BLACK, copy1)>scored_move_compute(CELL_BLACK, copy2));
}

void test_scored_move_compute_rule_three_over_four(){
    Board board, copy1, copy2;
    board_create(board);
    board_set_cell(board, 4, 1, CELL_BLACK);
    board_set_cell(board, 4, 3, CELL_BLACK);
    board_set_cell(board, 4, 4, CELL_BLACK);
    board_set_cell(board, 4, 5, CELL_WHITE);
    board_set_cell(board, 6, 1, CELL_EMPTY);
    board_set_cell(board, 6, 2, CELL_EMPTY);
    board_set_cell(board, 6, 3, CELL_EMPTY);
    board_set_cell(board, 1, 5, CELL_EMPTY);
    Move move1 = move_from_string("E2:E3");
    Move move2 = move_from_string("E4:E6");
    board_clone(board, copy1);
    board_clone(board, copy2);
    move_apply(move1, CELL_BLACK, copy1, 1);
    move_apply(move2, CELL_BLACK, copy2, 1);
    //assert(scored_move_compute(CELL_BLACK, copy1)<scored_move_compute(CELL_BLACK, copy2));
}

void test_scored_move_compute_rule_four_over_five(){
    Board board, copy1, copy2;
    board_create(board);
    board_set_cell(board, 5, 3, CELL_BLACK);
    board_set_cell(board, 7, 3, CELL_EMPTY);
    Move move1 = move_from_string("H5:H4");
    Move move2 = move_from_string("G3:E3");
    board_clone(board, copy1);
    board_clone(board, copy2);
    move_apply(move1, CELL_BLACK, copy1, 1);
    move_apply(move2, CELL_BLACK, copy2, 1);
    assert(scored_move_compute(CELL_BLACK, copy1)>scored_move_compute(CELL_BLACK, copy2));
}

void test_scored_move_compute_rule_five_over_six(){
    Board board, copy1, copy2;
    board_create(board);
    board_set_cell(board, 4, 5, CELL_BLACK);
    board_set_cell(board, 4, 7, CELL_BLACK);
    board_set_cell(board, 6, 5, CELL_EMPTY);
    board_set_cell(board, 7, 7, CELL_EMPTY);
    Move move1 = move_from_string("E6:E5");
    Move move2 = move_from_string("E6:E7");
    board_clone(board, copy1);
    board_clone(board, copy2);
    move_apply(move1, CELL_BLACK, copy1, 1);
    move_apply(move2, CELL_BLACK, copy2, 1);
    assert(scored_move_compute(CELL_BLACK, copy1)>scored_move_compute(CELL_BLACK, copy2));
}

void test_scored_move_compute_rule_six_over_seven(){
    Board board, copy1, copy2;
    board_create(board);
    board_set_cell(board, 3, 6, CELL_BLACK);
    board_set_cell(board, 5, 6, CELL_BLACK);
    board_set_cell(board, 5, 7, CELL_BLACK);
    board_set_cell(board, 6, 7, CELL_BLACK);
    board_set_cell(board, 3, 7, CELL_WHITE);
    board_set_cell(board, 7, 7, CELL_EMPTY);
    board_set_cell(board, 6, 6, CELL_EMPTY);
    board_set_cell(board, 7, 6, CELL_EMPTY);
    board_set_cell(board, 6, 5, CELL_EMPTY);
    board_set_cell(board, 0, 7, CELL_EMPTY);
    Move move1 = move_from_string("D7:E7");
    Move move2 = move_from_string("G8:E8");
    board_clone(board, copy1);
    board_clone(board, copy2);
    move_apply(move1, CELL_BLACK, copy1, 1);
    move_apply(move2, CELL_BLACK, copy2, 1);
    //assert(scored_move_compute(CELL_BLACK, copy1)>scored_move_compute(CELL_BLACK, copy2));
}

void test_scored_move_compute_rule_seven_over_eight(){
    Board board, copy1, copy2;
    board_create(board);
    board_set_cell(board, 2, 2, CELL_WHITE);
    board_set_cell(board, 2, 3, CELL_WHITE);
    board_set_cell(board, 2, 4, CELL_WHITE);
    board_set_cell(board, 2, 6, CELL_BLACK);
    board_set_cell(board, 5, 1, CELL_WHITE);
    board_set_cell(board, 5, 3, CELL_BLACK);
    board_set_cell(board, 5, 4, CELL_BLACK);
    board_set_cell(board, 5, 5, CELL_BLACK);
    board_set_cell(board, 1, 3, CELL_EMPTY);
    board_set_cell(board, 1, 4, CELL_EMPTY);
    board_set_cell(board, 1, 5, CELL_EMPTY);
    board_set_cell(board, 1, 6, CELL_EMPTY);
    board_set_cell(board, 6, 1, CELL_EMPTY);
    board_set_cell(board, 6, 2, CELL_EMPTY);
    board_set_cell(board, 6, 3, CELL_EMPTY);
    board_set_cell(board, 6, 4, CELL_EMPTY);
    Move move1 = move_from_string("F6:F3");
    Move move2 = move_from_string("C7:D7");
    board_clone(board, copy1);
    board_clone(board, copy2);
    move_apply(move1, CELL_BLACK, copy1, 1);
    move_apply(move2, CELL_BLACK, copy2, 1);
    //assert(scored_move_compute(CELL_BLACK, copy1)>scored_move_compute(CELL_BLACK, copy2));
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
    test_scored_move_compute_rule_one_over_two();
    test_scored_move_compute_rule_two_over_three();
    test_scored_move_compute_rule_three_over_four();
    test_scored_move_compute_rule_four_over_five();
    test_scored_move_compute_rule_five_over_six();
    test_scored_move_compute_rule_six_over_seven();
    test_scored_move_compute_rule_seven_over_eight();
}