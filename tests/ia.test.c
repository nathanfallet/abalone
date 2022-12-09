#include <assert.h>
#include "ia.test.h"

void test_ia_update() {
	PGame game = game_new(CELL_BLACK, 0);
	ia_update(game, CELL_BLACK, STATE_PLAYING);
	assert(game->playing == CELL_WHITE);
}

void test_ia_minimax_victory() {
	Board board;
	board_create(board);
	board_set_cell(board, 1, 0, CELL_BLACK);
	board_set_cell(board, 2, 0, CELL_BLACK);
	board_set_cell(board, 7, 0, CELL_EMPTY);
	board_set_cell(board, 7, 1, CELL_EMPTY);
	assert(ia_minimax(CELL_BLACK, board, 1) == move_from_string("C1:A1"));
	assert(ia_minimax(CELL_BLACK, board, 2) == move_from_string("C1:A1"));
	assert(ia_minimax(CELL_BLACK, board, 3) == move_from_string("C1:A1"));
	assert(ia_minimax(CELL_BLACK, board, 4) == move_from_string("C1:A1"));
}

void test_ia() {
	test_ia_update();
	test_ia_minimax_victory();
}
