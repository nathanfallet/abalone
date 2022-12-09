#ifndef GUI_H
#define GUI_H

/* existing libraries */
#include <stdlib.h>
#include <stdio.h>
#include "ia.h"
#include "game.h"
#include "cell.h"
#include "move.h"


/**
 * initialise l'affichage GTK
 * @param owner Le joueur qui créé la partie (CELL_BLACK ou CELL_WHITE)
 * @param ia_override Si l'IA doit jouer à la place du joueur
 * @param refresh_opponent Le callback pour actualiser l'adversaire
*/
void gui_init(Cell owner, int ia_override, void (*refresh_opponent)(PGame game, Cell me, State state));

/**
 * actualise l'affichage dans GTK
 * @param game La partie
 * @param me Le joueur
 * @param state L'état de la partie
*/
void gui_update(PGame game, Cell me, State state);

#endif
