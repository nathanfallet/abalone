#ifndef GUI_H
#define GUI_H

/* existing libraries */
#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "cell.h"
#include "move.h"

void gui_init(Cell owner, void (*actualiser_adversaire)(PGame game, Cell me, State state));
void gui_update(PGame game, Cell me, State state);

#endif
