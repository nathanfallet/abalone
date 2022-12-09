#ifndef BOARD_H
#define BOARD_H

#include "constants.h"
#include "cell.h"

typedef unsigned long Board[2];

/**
 * Crée un plateau par défaut
 * @param board Le plateau à créer
 */
void board_create(Board board);

/**
 * Clone un plateau
 * @param board Le plateau à cloner
 * @param target Le plateau cible
 */
void board_clone(Board board, Board target);

/**
 * Retourne la cellule à la position donnée
 * @param board Le plateau
 * @param line La ligne
 * @param column La colonne
 * @return La cellule
 */
Cell board_get_cell(Board board, int line, int column);

/**
 * Modifie la cellule à la position donnée
 * @param board Le plateau
 * @param line La ligne
 * @param column La colonne
 * @param cell La cellule
 */
void board_set_cell(Board board, int line, int column, Cell cell);

#endif
