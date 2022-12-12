#ifndef GUI_H
#define GUI_H

/**
 * \file gui.h
 * \brief Graphic display
 * 
 * Graphic display whith GTK.
 */

#include <stdlib.h>
#include <stdio.h>
#include "ia.h"
#include "game.h"
#include "cell.h"
#include "move.h"

/**
 * \brief Initialize GTK display
 * \param owner The palyer who must create thge game (CELL_BLACK or CELL_WHITE)
 * \param ia_override If the AI must play instead of player
 * \param refresh_opponent The callback to refresh opponent
 */
void gui_init(Cell owner, int ia_override, void (*refresh_opponent)(Game *game, Cell me, State state), char address[ADDRESS_LENGTH], int port);

/**
 * \brief GTK Refesh GTK display
 * \param game The game
 * \param me The player
 * \param state the state of game
 */
void gui_update(Game *game, Cell me, State state);

#endif
