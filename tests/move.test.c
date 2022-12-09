#include <assert.h>
#include <string.h>
#include "move.test.h"

void test_move_create() {
    Move move = move_create(1, 2, 3, 4);
    assert(move_get_from_line(move) == 1);
    assert(move_get_from_column(move) == 2);
    assert(move_get_to_line(move) == 3);
    assert(move_get_to_column(move) == 4);
}

void test_move_from_string() {
    Move move = move_from_string("B3:D5");
    assert(move_get_from_line(move) == 1);
    assert(move_get_from_column(move) == 2);
    assert(move_get_to_line(move) == 3);
    assert(move_get_to_column(move) == 4);
}

void test_move_from_string_lowercase() {
    Move move = move_from_string("b3:d5");
    assert(move_get_from_line(move) == 1);
    assert(move_get_from_column(move) == 2);
    assert(move_get_to_line(move) == 3);
    assert(move_get_to_column(move) == 4);
}

void test_move_to_string() {
    Move move = move_create(1, 2, 3, 4);
    char *string = move_to_string(move);
    assert(strcmp(string, "B3:D5") == 0);
}

// test move

void  test_move_apply_line_one(){
    Board board;
    board_create(board);
    Move move = move_from_string("A1:B1");
    assert (move_apply(move, CELL_WHITE, board, 1));
    assert (board_get_cell(board, 0, 0) == CELL_EMPTY);
    assert (board_get_cell(board, 1, 0) == CELL_WHITE);
}

void  test_move_apply_line_two(){
    Board board;
    board_create(board);
    Move move = move_from_string("A2:C2");
    assert (move_apply(move, CELL_WHITE, board, 1));
    assert (board_get_cell(board, 0, 1) == CELL_EMPTY);
    assert (board_get_cell(board, 1, 1) == CELL_WHITE);
        assert (board_get_cell(board, 2, 1) == CELL_WHITE);
}

void  test_move_apply_line_three(){
    Board board;
    board_create(board);
    Move move = move_from_string("B4:B1");
    assert (move_apply(move, CELL_WHITE, board, 1));
    assert (board_get_cell(board, 1, 3) == CELL_EMPTY);
    assert (board_get_cell(board, 1, 0) == CELL_WHITE);
    assert (board_get_cell(board, 1, 1) == CELL_WHITE);
    assert (board_get_cell(board, 1, 2) == CELL_WHITE);
}

void  test_move_apply_lateral_two(){
    Board board;
    board_create(board);
    Move move = move_from_string("B2:C3");
    assert (move_apply(move, CELL_WHITE, board, 1));
    assert (board_get_cell(board, 1, 1) == CELL_EMPTY);
    assert (board_get_cell(board, 1, 2) == CELL_EMPTY);
    assert (board_get_cell(board, 2, 1) == CELL_WHITE);
    assert (board_get_cell(board, 2, 2) == CELL_WHITE);
}

void  test_move_apply_lateral_three(){
    Board board;
    board_create(board);
    Move move = move_from_string("B2:C4");
    assert (move_apply(move, CELL_WHITE, board, 1));
    assert (board_get_cell(board, 1, 1) == CELL_EMPTY);
    assert (board_get_cell(board, 1, 2) == CELL_EMPTY);
    assert (board_get_cell(board, 1, 3) == CELL_EMPTY);
    assert (board_get_cell(board, 2, 1) == CELL_WHITE);
    assert (board_get_cell(board, 2, 2) == CELL_WHITE);
    assert (board_get_cell(board, 2, 3) == CELL_WHITE);
}

// Test move invalide
 void  test_move_apply_line_one_error(){
    Board board;
    board_create(board);
    Move move = move_from_string("A1:A2");
    assert (move_apply(move, CELL_WHITE, board, 1)==0);
}

 void  test_move_apply_line_two_error(){
    Board board;
    board_create(board);
    Move move = move_from_string("A1:A3");
    assert (move_apply(move, CELL_WHITE, board, 1)==0);
}

 void  test_move_apply_line_three_error(){
    Board board;
    board_create(board);
    Move move = move_from_string("A1:A4");
    assert (move_apply(move, CELL_WHITE, board, 1)==0);
}


 void  test_move_apply_lateral_two_error(){
    Board board;
    board_create(board);
    Move move = move_from_string("A2:B3");
    assert (move_apply(move, CELL_WHITE, board, 1)==0);
}

 void  test_move_apply_lateral_three_error(){
    Board board;
    board_create(board);
    Move move = move_from_string("A2:B4");
    assert (move_apply(move, CELL_WHITE, board, 1)==0);
}





// TODO: Test move_apply and move_available

void test_move() {
    test_move_create();
    test_move_from_string();
    test_move_from_string_lowercase();
    test_move_to_string();
    test_move_apply_line_one();
    test_move_apply_line_two();
    test_move_apply_line_three();
    test_move_apply_lateral_two();
    test_move_apply_lateral_three();
    test_move_apply_line_one_error();
    test_move_apply_line_two_error();
    test_move_apply_line_three_error();
    test_move_apply_lateral_two_error();
    test_move_apply_lateral_three_error();
    // TODO: Call tests for move_apply and move_available
}
