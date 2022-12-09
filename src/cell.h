#ifndef CELL_H
#define CELL_H

#include "constants.h"

typedef unsigned char Cell;

/**
 * Vérifie si la cellule est occupée par un pion de couleur opposée
 * @param cell couleur ou état de la cellule (CELL_BLACK ou CELL_WHITE ou CELL_EMPTY)
 * @return la couleur noir/blanc/vide
*/
Cell cell_opposite(Cell cell);

#endif
