#include <assert.h>
#include "cell.test.h"

void test_cell_opposite() {
    assert(cell_opposite(CELL_BLACK) == CELL_WHITE);
    assert(cell_opposite(CELL_WHITE) == CELL_BLACK);
    assert(cell_opposite(CELL_EMPTY) == CELL_EMPTY);
}

void test_cell() {
    test_cell_opposite();
}
