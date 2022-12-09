#include <assert.h>
#include "scored_move.test.h"

void test_scored_move_new() {
    Move m1 = move_create(1, 2, 3, 4);
    Move m2 = move_create(5, 6, 7, 8);
    ScoredMove scored_move = scored_move_new(m1, m2, 1234);
    assert(scored_move_move(scored_move) == m1);
    assert(scored_move_root(scored_move) == m2);
    assert(scored_move_score(scored_move) == 1234);
}

void test_scored_move_compute() {
    // TODO
}

void test_scored_move() {
    test_scored_move_new();
    test_scored_move_compute();
}
