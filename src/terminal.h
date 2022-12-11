#ifndef TERMINAL_H
#define TERMINAL_H

/**
 * \file terminal.h
 * \brief Gestion du terminal
 * 
 * Gestion de l'affichage dans le terminal.
 */

#include <stdlib.h>
#include <stdio.h>
#include "ia.h"
#include "game.h"
#include "cell.h"
#include "state.h"

/**
 * \brief Initialise l'affichage dans le terminal
 * \param owner Le joueur qui créé la partie (CELL_BLACK ou CELL_WHITE)
 * \param ia_override Si l'IA doit jouer à la place du joueur
 * \param refresh_opponent Le callback pour actualiser l'adversaire
 */
void terminal_init(Cell owner, int ia_override, void (*refresh_opponent)(Game *game, Cell me, State state), char address[ADDRESS_LENGTH], int port);

/**
 * \brief Actualise l'affichage du terrain dans le terminal
 * \param game La partie
 * \param me Le joueur
 * \param state L'état de la partie
 */
void terminal_update(Game *game, Cell me, State state);

#endif
