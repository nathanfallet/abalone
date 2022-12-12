#ifndef BOARD_H
#define BOARD_H

/**
 * \file board.h
 * \brief Board management
 * 
 * Management of a game board via the Board object.
 */

#include "constants.h"
#include "cell.h"
#include "state.h"

/**
 * \brief Game board
 * 
 * Game board is a board of 2 unsigned intergres.
 * 
 * The first integer represents the black pawns.
 * The second integer represents the white pawns.
 * 
 * Chaque bit représente une cellule du plateau.
 * Each bit represents a board cell.
 * 
 * 0 = Empty cell
 * 1 = full cell 
 */
typedef unsigned long Board[2];

/**
 * \brief Create a default board
 * \param board The board to create
 */
void board_create(Board board);

/**
 * \brief Clone a board
 * \param board The board to clone
 * \param target The target board
 */
void board_clone(Board board, Board target);

/**
 * \brief Return the cell of desired position 
 * \param board The board
 * \param line The line
 * \param column The column
 * \return The cell
 */
Cell board_get_cell(Board board, int line, int column);

/**
 * \brief Modified the cell of desired position
 * \param board The board
 * \param line The line
 * \param column The column
 * \param cell The cell
 */
void board_set_cell(Board board, int line, int column, Cell cell);

/**
 * \brief Return the board state
 * \param board The board
 * \return The board state
 */
State board_state(Board board);

#endif
