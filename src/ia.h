#ifndef IA_H
#define IA_H

/* existing libraries */
#include "board.h"
#include "game.h"
#include "list.h"
#include "constants.h"
#include "scored_move.h"
#include "state.h"

ScoredMove *compare(Cell me, Board board, Move *root, int profondeur, int max, int threshold);

void ia_init(Cell owner, void (*refresh_opponent)(PGame game, Cell me, State state));
void ia_update(PGame game, Cell me, State state);

#endif
