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

// TODO: Test move_apply and move_available

void test_move() {
    test_move_create();
    test_move_from_string();
    test_move_from_string_lowercase();
    test_move_to_string();
    // TODO: Call tests for move_apply and move_available
}
