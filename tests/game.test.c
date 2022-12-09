#include <assert.h>
#include "game.test.h"



void test_game_turn_new_player() {
    PGame game = game_new(CELL_BLACK, 0);
    assert (game->playing == CELL_BLACK);
    Move move = move_from_string("H1:G1");
    game_turn(game, move);
    assert (game->playing == CELL_WHITE);
}


void test_game() {
 test_game_turn_new_player();
}
