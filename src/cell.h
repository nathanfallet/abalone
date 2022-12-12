#ifndef CELL_H
#define CELL_H

/**
 * \file cell.h
 * \brief Board cell
 * 
 * Board cells management.
 * Cell also represent a player.
*/

#include "constants.h"

/**
 * \brief Board cell
 * 
 * Cell is either empty, black or white.
 * It also represent a player.
 * It is worth CELL_EMPTY, CELL_BLACK or CELL_WHITE.
 */
typedef unsigned char Cell;

/**
 * \brief Check if the cell is taken by an oponent pawn
 * \param color or state cell (CELL_BLACK or CELL_WHITE or CELL_EMPTY) 
 * \return the color black/white/empty
 */
Cell cell_opposite(Cell cell);

#endif
