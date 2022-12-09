#include <assert.h>
#include "board.test.h"
#include "cell.test.h"
#include "game.test.h"
#include "ia.test.h"
#include "move.test.h"
#include "network.test.h"
#include "scored_move.test.h"

int main(int argc, char *argv[]) {
    test_board();
    test_cell();
    test_game();
    test_ia();
    test_move();
    test_network();
    test_scored_move();

    return 0;
}
