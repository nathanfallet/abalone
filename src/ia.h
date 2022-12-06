#ifndef IA_H
#define IA_H

/* existing libraries */
#include "game.h"
#include "list.h"
#include "constants.h"
#include "scored_move.h"
#include "state.h"

void ia_init(Cell owner, void (*actualiser_adversaire)(PGame game, Cell me, State state));
void ia_update(PGame game, Cell me, State state);

#endif
