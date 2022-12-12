#ifndef MOVE_H
#define MOVE_H

/**
 * \file move.h
 * \brief Move management
 * 
 * Move management with the necessary checks
 */

#include "constants.h"
#include "board.h"
#include "cell.h"

/**
 * \brief Represents a movement
 * 
 * A movement is represented by a 16-bits integer,
 * with the 4 most significant bits for the starting line,
 * the next 4 bits for the starting column,
 * the next 4 bits for the destination line and
 * the 4 least significant bits for the destination column.
 */
typedef unsigned short Move;

/**
 * \brief Create a move
 * \param fromLine The starting line of the move
 * \param fromColumn The starting column of the move
 * \param toLine The destination line of the move
 * \param toColumn The destination column of the move
 * \return Move creates
 */
Move move_create(unsigned char fromLine, unsigned char fromColumn, unsigned char toLine, unsigned char toColumn);

/**
 * \brief Read the starting line of a move
 * \param move The move we want to read
 * \return The starting line of the move
 */
unsigned char move_get_from_line(Move move);

/**
 * \brief Read the starting column of a move
 * \param move The move we want to read
 * \return The starting column of the move
 */
unsigned char move_get_from_column(Move move);

/**
 * \brief Read the destination line of a move
 * \param move The move we want to read
 * \return The destination line of the move 
 */
unsigned char move_get_to_line(Move move);

/**
 * \brief Read the destination column of a move
 * \param move The move we want to read
 * \return The destination column of the move
 */
unsigned char move_get_to_column(Move move);

/**
 * \brief Convert string to move
 * \param string Is the string corresponding to a move,
 * We can use lowercase or uppercase letters. This string
 * allows the player to enter the move they wish to make
 * \return The move corresponding to the string
 */
Move move_from_string(char *string);

/**
 * \brief Convert move to string
 * \param move The move that we want to convert
 * \return The string corresponding to the move
 */
char *move_to_string(Move move);

/**
 * \brief Check the validity of a move and apply if it is possible
 * \param move The move that we want to apply
 * \param me Is the color of the player since the validity of the
 * move varies according to the color of the pawns
 * \param board Represents the board at the moment that we want to
 * apply the move
 * \param apply If apply is 0, only allows to check the validity of a move
 * If apply is 1, allows to check the validity of a move and apply it if it is possible
 * \return If the move is possible (0 for error and 1 for valid)
 */
int move_apply(Move move, Cell me, Board board, int apply);

/**
 * \brief List all possible moves
 * \param me Is the color of the player whose possible moves
 * on the board we want to know
 * \param board Represents the board at the moment that we want to know all the 
 * possible moves
 * \param array Recover all the possible moves for the player "me"
 */
void move_available(Cell me, Board board, Move array[MOVE_LIST_SIZE]);

#endif
