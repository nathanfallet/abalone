#ifndef CELL_H
#define CELL_H

/**
 * \file cell.h
 * \brief Cellule de plateau
 * 
 * Gestion des cellules de plateau.
 * Une cellule représente aussi un joueur.
*/

#include "constants.h"

/**
 * \brief Cellule de plateau
 * 
 * Une cellule est soit vide, soit noire, soit blanche.
 * Elle représente aussi un joueur.
 * Elle vaut CELL_EMPTY, CELL_BLACK ou CELL_WHITE.
 */
typedef unsigned char Cell;

/**
 * \brief Vérifie si la cellule est occupée par un pion de couleur opposée
 * \param cell couleur ou état de la cellule (CELL_BLACK ou CELL_WHITE ou CELL_EMPTY)
 * \return la couleur noir/blanc/vide
 */
Cell cell_opposite(Cell cell);

#endif
