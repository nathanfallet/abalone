#include "cell.h"

Cell cell_opposite(Cell cell) {
    if (cell == CELL_BLACK) {
        return CELL_WHITE;
    }
    if (cell == CELL_WHITE) {
        return CELL_BLACK;
    }
    return CELL_EMPTY;
}
