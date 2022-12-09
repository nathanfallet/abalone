#include <assert.h>
#include "ia.test.h"



void test_ia_update() {
	PGame game = game_new(CELL_BLACK, 0);
	ia_update (game, CELL_BLACK, STATE_PLAYING);
	assert (game->playing == CELL_WHITE);
}


void test_ia() {
    test_ia_update();
}
