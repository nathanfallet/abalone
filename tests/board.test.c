#include <assert.h>
#include "board.test.h"

void test_board_create() {
    Board board;
    board_create(board);
    assert(board[0] == 18410152326737166336UL);
    assert(board[1] == 32511UL);
}

void test_board_clone() {
    Board board;
    board_create(board);
    Board target;
    board_clone(board, target);
    assert(board[0] == target[0]);
    assert(board[1] == target[1]);
}

void test_board_get_cell() {
    Board board;
    board_create(board);
    assert(board_get_cell(board, 0, 0) == CELL_WHITE);
    assert(board_get_cell(board, 3, 0) == CELL_EMPTY);
    assert(board_get_cell(board, 7, 0) == CELL_BLACK);
    assert(board_get_cell(board, 0, -1) == CELL_EMPTY);
    assert(board_get_cell(board, -1, 0) == CELL_EMPTY);
    assert(board_get_cell(board, 8, 7) == CELL_EMPTY);
    assert(board_get_cell(board, 7, 8) == CELL_EMPTY);
}

void test_board_set_cell() {
    Board board;
    board_create(board);
    board_set_cell(board, 0, 0, CELL_BLACK);
    board_set_cell(board, 0, 1, CELL_EMPTY);
    board_set_cell(board, 7, 0, CELL_WHITE);
    assert(board_get_cell(board, 0, 0) == CELL_BLACK);
    assert(board_get_cell(board, 0, 1) == CELL_EMPTY);
    assert(board_get_cell(board, 7, 0) == CELL_WHITE);
    board_set_cell(board, 0, -1, CELL_EMPTY);
    board_set_cell(board, -1, 0, CELL_EMPTY);
    board_set_cell(board, 8, 7, CELL_EMPTY);
    board_set_cell(board, 7, 8, CELL_EMPTY);
}

void test_board_state() {
    Board board;
    board_create(board);
    assert(board_state(board) == STATE_PLAYING);
    board_set_cell(board, 0, 0, CELL_EMPTY);
    assert(board_state(board) == STATE_WIN_BLACK);
    board_set_cell(board, 0, 0, CELL_WHITE);
    board_set_cell(board, 7, 0, CELL_EMPTY);
    assert(board_state(board) == STATE_WIN_WHITE);
}

void test_board() {
    test_board_create();
    test_board_clone();
    test_board_get_cell();
    test_board_set_cell();
    test_board_state();
}
