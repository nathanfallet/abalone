#ifndef BOARD_H
#define BOARD_H

/**
 * \file board.h
 * \brief Gestion d'un plateau
 * 
 * Gestion d'un plateau de jeu via l'objet Board.
 */

#include "constants.h"
#include "cell.h"
#include "state.h"

/**
 * \brief Plateau de jeu
 * 
 * Un plateau de jeu est un tableau de 2 entiers non signés.
 * 
 * Le premier entier représente les pions noirs.
 * Le second entier représente les pions blans.
 * 
 * Chaque bit représente une cellule du plateau.
 * 
 * 0 = Cellule vide
 * 1 = Cellule pleine
 */
typedef unsigned long Board[2];

/**
 * \brief Crée un plateau par défaut
 * \param board Le plateau à créer
 */
void board_create(Board board);

/**
 * \brief Clone un plateau
 * \param board Le plateau à cloner
 * \param target Le plateau cible
 */
void board_clone(Board board, Board target);

/**
 * \brief Retourne la cellule à la position donnée
 * \param board Le plateau
 * \param line La ligne
 * \param column La colonne
 * \return La cellule
 */
Cell board_get_cell(Board board, int line, int column);

/**
 * \brief Modifie la cellule à la position donnée
 * \param board Le plateau
 * \param line La ligne
 * \param column La colonne
 * \param cell La cellule
 */
void board_set_cell(Board board, int line, int column, Cell cell);

/**
 * \brief Retourne l'état du plateau
 * \param board Le plateau
 * \return L'état du plateau
 */
State board_state(Board board);

#endif
