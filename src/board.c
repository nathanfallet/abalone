#include "board.h"

void board_create(Board board) {
    /* Set default board with a mask */
    board[0] = 18410152326737166336UL;
    board[1] = 32511UL;
}

void board_clone(Board board, Board target) {
    target[0] = board[0];
    target[1] = board[1];
}

Cell board_get_cell(Board board, int line, int column) {
    if (line < 0 || line >= BOARD_SIZE || column < 0 || column >= BOARD_SIZE) {
        return CELL_EMPTY;
    }
    if (board[0] >> (line * 8 + column) & 1) {
        return CELL_BLACK;
    }
    if (board[1] >> (line * 8 + column) & 1) {
        return CELL_WHITE;
    }
    return CELL_EMPTY;
}

void board_set_cell(Board board, int line, int column, Cell cell) {
    /* Outside of board */
    if (line < 0 || line >= BOARD_SIZE || column < 0 || column >= BOARD_SIZE) {
        return;
    }

    /* Reset previous cell */
    board[0] &= ~(1UL << (line * 8 + column));
    board[1] &= ~(1UL << (line * 8 + column));

    /* Apply correct cell */
    if (cell == CELL_BLACK) {
        board[0] |= 1UL << (line * 8 + column);
    } else if (cell == CELL_WHITE) {
        board[1] |= 1UL << (line * 8 + column);
    }
}
