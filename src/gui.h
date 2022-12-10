#ifndef GUI_H
#define GUI_H

/**
 * \file gui.h
 * \brief Affichage graphique
 * 
 * Affichage graphique avec GTK.
 */

#include <stdlib.h>
#include <stdio.h>
#include "ia.h"
#include "game.h"
#include "cell.h"
#include "move.h"

/**
 * \brief Initialise l'affichage GTK
 * \param owner Le joueur qui créé la partie (CELL_BLACK ou CELL_WHITE)
 * \param ia_override Si l'IA doit jouer à la place du joueur
 * \param refresh_opponent Le callback pour actualiser l'adversaire
 */
void gui_init(Cell owner, int ia_override, void (*refresh_opponent)(Game *game, Cell me, State state));

/**
 * \brief Actualise l'affichage dans GTK
 * \param game La partie
 * \param me Le joueur
 * \param state L'état de la partie
 */
void gui_update(Game *game, Cell me, State state);

#endif
