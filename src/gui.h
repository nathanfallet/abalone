#ifndef GUI_H
#define GUI_H

/* existing libraries */
#include <stdlib.h>
#include <stdio.h>
#include "ia.h"
#include "game.h"
#include "cell.h"
#include "move.h"

void gui_init(Cell owner, int ia_override, void (*refresh_opponent)(PGame game, Cell me, State state));
void gui_update(PGame game, Cell me, State state);

#endif
