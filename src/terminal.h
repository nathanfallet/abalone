#ifndef TERMINAL_H
#define TERMINAL_H

/**
 * \file terminal.h
 * \brief Terminal management
 * 
 * Display management in terminal
 */

#include <stdlib.h>
#include <stdio.h>
#include "ia.h"
#include "game.h"
#include "cell.h"
#include "state.h"

/**
 * \brief Initialize terminal display
 * \param owner The player creating the game (CELL_BLACK ou CELL_WHITE)
 * \param ia_override If the AI should play instead of the player
 * \param refresh_opponent The Callback to actualize the opponent
 */
void terminal_init(Cell owner, int ia_override, void (*refresh_opponent)(Game *game, Cell me, State state), char address[ADDRESS_LENGTH], int port);

/**
 * \brief Actualize display of the plate in the terminal
 * \param game The game
 * \param me The player
 * \param state The state of the game
 */
void terminal_update(Game *game, Cell me, State state);

#endif
