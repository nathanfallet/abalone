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

void test_move_apply_line_one() {
    Board board;
    board_create(board);
    Move move = move_from_string("A1:B1");
    assert(move_apply(move, CELL_WHITE, board, 1));
    assert(board_get_cell(board, 0, 0) == CELL_EMPTY);
    assert(board_get_cell(board, 1, 0) == CELL_WHITE);
}

void test_move_apply_line_two() {
    Board board;
    board_create(board);
    Move move = move_from_string("A2:C2");
    assert(move_apply(move, CELL_WHITE, board, 1));
    assert(board_get_cell(board, 0, 1) == CELL_EMPTY);
    assert(board_get_cell(board, 1, 1) == CELL_WHITE);
    assert(board_get_cell(board, 2, 1) == CELL_WHITE);
}

void test_move_apply_line_three() {
    Board board;
    board_create(board);
    Move move = move_from_string("B4:B1");
    assert(move_apply(move, CELL_WHITE, board, 1));
    assert(board_get_cell(board, 1, 3) == CELL_EMPTY);
    assert(board_get_cell(board, 1, 0) == CELL_WHITE);
    assert(board_get_cell(board, 1, 1) == CELL_WHITE);
    assert(board_get_cell(board, 1, 2) == CELL_WHITE);
}

void test_move_apply_lateral_two() {
    Board board;
    board_create(board);
    Move move = move_from_string("B2:C3");
    assert(move_apply(move, CELL_WHITE, board, 1));
    assert(board_get_cell(board, 1, 1) == CELL_EMPTY);
    assert(board_get_cell(board, 1, 2) == CELL_EMPTY);
    assert(board_get_cell(board, 2, 1) == CELL_WHITE);
    assert(board_get_cell(board, 2, 2) == CELL_WHITE);
}

void test_move_apply_lateral_three() {
    Board board;
    board_create(board);
    Move move = move_from_string("B2:C4");
    assert(move_apply(move, CELL_WHITE, board, 1));
    assert(board_get_cell(board, 1, 1) == CELL_EMPTY);
    assert(board_get_cell(board, 1, 2) == CELL_EMPTY);
    assert(board_get_cell(board, 1, 3) == CELL_EMPTY);
    assert(board_get_cell(board, 2, 1) == CELL_WHITE);
    assert(board_get_cell(board, 2, 2) == CELL_WHITE);
    assert(board_get_cell(board, 2, 3) == CELL_WHITE);
}

void test_move_apply_line_one_error() {
    Board board;
    board_create(board);
    Move move = move_from_string("A1:A2");
    assert(move_apply(move, CELL_WHITE, board, 1) == 0);
}

void test_move_apply_line_two_error() {
    Board board;
    board_create(board);
    Move move = move_from_string("A1:A3");
    assert(move_apply(move, CELL_WHITE, board, 1) == 0);
}

void test_move_apply_line_three_error() {
    Board board;
    board_create(board);
    Move move = move_from_string("A1:A4");
    assert(move_apply(move, CELL_WHITE, board, 1) == 0);
}

void test_move_apply_lateral_two_error() {
    Board board;
    board_create(board);
    Move move = move_from_string("A2:B3");
    assert(move_apply(move, CELL_WHITE, board, 1) == 0);
}

void test_move_apply_lateral_three_error() {
    Board board;
    board_create(board);
    Move move = move_from_string("A2:B4");
    assert(move_apply(move, CELL_WHITE, board, 1) == 0);
}

void test_move_available() {
    Board board;
    board_create(board);
    Move moves_white[MOVE_LIST_SIZE];
    move_available(CELL_WHITE, board, moves_white);
    assert(moves_white[0] == move_from_string("A1:B1"));
    assert(moves_white[1] == move_from_string("A2:C2"));
    assert(moves_white[2] == move_from_string("A3:C3"));
    assert(moves_white[3] == move_from_string("A4:C4"));
    assert(moves_white[4] == move_from_string("A5:C5"));
    assert(moves_white[5] == move_from_string("A6:C6"));
    assert(moves_white[6] == move_from_string("A7:C7"));
    assert(moves_white[7] == move_from_string("A8:B8"));
    assert(moves_white[8] == move_from_string("B2:C2"));
    assert(moves_white[9] == move_from_string("B2:B1"));
    assert(moves_white[10] == move_from_string("B3:B1"));
    assert(moves_white[11] == move_from_string("B2:C3"));
    assert(moves_white[12] == move_from_string("B4:B1"));
    assert(moves_white[13] == move_from_string("B2:C4"));
    assert(moves_white[14] == move_from_string("B3:C3"));
    assert(moves_white[15] == move_from_string("B3:C4"));
    assert(moves_white[16] == move_from_string("B3:C5"));
    assert(moves_white[17] == move_from_string("B4:C4"));
    assert(moves_white[18] == move_from_string("B4:C5"));
    assert(moves_white[19] == move_from_string("B4:C6"));
    assert(moves_white[20] == move_from_string("B5:C5"));
    assert(moves_white[21] == move_from_string("B5:C6"));
    assert(moves_white[22] == move_from_string("B5:B8"));
    assert(moves_white[23] == move_from_string("B5:C7"));
    assert(moves_white[24] == move_from_string("B6:C6"));
    assert(moves_white[25] == move_from_string("B6:B8"));
    assert(moves_white[26] == move_from_string("B6:C7"));
    assert(moves_white[27] == move_from_string("B7:B8"));
    assert(moves_white[28] == move_from_string("B7:C7"));
    assert(moves_white[29] == MOVE_NONE);
    Move moves_black[MOVE_LIST_SIZE];
    move_available(CELL_BLACK, board, moves_black);
    assert(moves_black[0] == move_from_string("G2:G1"));
    assert(moves_black[1] == move_from_string("G2:F2"));
    assert(moves_black[2] == move_from_string("G3:G1"));
    assert(moves_black[3] == move_from_string("H2:F2"));
    assert(moves_black[4] == move_from_string("G2:F3"));
    assert(moves_black[5] == move_from_string("G4:G1"));
    assert(moves_black[6] == move_from_string("G2:F4"));
    assert(moves_black[7] == move_from_string("G3:F3"));
    assert(moves_black[8] == move_from_string("H3:F3"));
    assert(moves_black[9] == move_from_string("G3:F4"));
    assert(moves_black[10] == move_from_string("G3:F5"));
    assert(moves_black[11] == move_from_string("G4:F4"));
    assert(moves_black[12] == move_from_string("H4:F4"));
    assert(moves_black[13] == move_from_string("G4:F5"));
    assert(moves_black[14] == move_from_string("G4:F6"));
    assert(moves_black[15] == move_from_string("G5:F5"));
    assert(moves_black[16] == move_from_string("H5:F5"));
    assert(moves_black[17] == move_from_string("G5:F6"));
    assert(moves_black[18] == move_from_string("G5:G8"));
    assert(moves_black[19] == move_from_string("G5:F7"));
    assert(moves_black[20] == move_from_string("G6:F6"));
    assert(moves_black[21] == move_from_string("G6:G8"));
    assert(moves_black[22] == move_from_string("H6:F6"));
    assert(moves_black[23] == move_from_string("G6:F7"));
    assert(moves_black[24] == move_from_string("G7:G8"));
    assert(moves_black[25] == move_from_string("G7:F7"));
    assert(moves_black[26] == move_from_string("H7:F7"));
    assert(moves_black[27] == move_from_string("H1:G1"));
    assert(moves_black[28] == move_from_string("H8:G8"));
    assert(moves_black[29] == MOVE_NONE);
}

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
    test_move_available();
}
