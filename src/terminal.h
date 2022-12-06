#ifndef TERMINAL_H
#define TERMINAL_H

/* existing libraries */
#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "cell.h"
#include "state.h"

void terminal_init(Cell owner, void (*refresh_opponent)(PGame game, Cell me, State state));
void terminal_update(PGame game, Cell me, State state);
void terminal_update_no_print(PGame game, Cell me, State state);

#endif
