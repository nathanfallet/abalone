#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "move.h"

/* Initialization */

Move move_create(unsigned char fromLine, unsigned char fromColumn, unsigned char toLine, unsigned char toColumn) {
    return (fromLine << 12) | (fromColumn << 8) | (toLine << 4) | toColumn;
}

unsigned char move_get_from_line(Move move) {
    return move >> 12;
}

unsigned char move_get_from_column(Move move) {
    return (move >> 8) & 15;
}

unsigned char move_get_to_line(Move move) {
    return (move >> 4) & 15;
}

unsigned char move_get_to_column(Move move) {
    return move & 15;
}

/*Converting a string to a Move and vice versa */

Move move_from_string(char *string) {
    char fromLine = string[0];
    if (fromLine >= 'a' && fromLine <= 'h') {
        fromLine -= 32;
    }
    char toLine = string[3];
    if (toLine >= 'a' && toLine <= 'h') {
        toLine -= 32;
    }
    return move_create(
        fromLine - 'A',
        string[1] - '1',
        toLine - 'A',
        string[4] - '1');
}

char *move_to_string(Move move) {
    static char string[6];
    string[0] = move_get_from_line(move) + 'A';
    string[1] = move_get_from_column(move) + '1';
    string[2] = ':';
    string[3] = move_get_to_line(move) + 'A';
    string[4] = move_get_to_column(move) + '1';
    string[5] = '\0';
    return string;
}

/* Utility function */

int sign(int x) {
    if (x < 0) {
        return -1;
    }
    if (x > 0) {
        return 1;
    }
    return 0;
}

/* Check and applying of a Move on the board */

int move_line_one(Move move, Cell me, Board board, int apply) {
    /* We check that the original cell contains a pawn of the right color */
    if (board_get_cell(board, move_get_from_line(move), move_get_from_column(move)) != me) {
        return 0;
    }

    /* We check that the destination cell is empty */
    if (board_get_cell(board, move_get_to_line(move), move_get_to_column(move)) != CELL_EMPTY) {
        return 0;
    }

    /* We move the pawn */
    if (apply) {
        board_set_cell(board, move_get_to_line(move), move_get_to_column(move), me);
        board_set_cell(board, move_get_from_line(move), move_get_from_column(move), CELL_EMPTY);
    }

    return 1;
}

int move_line_two(Move move, Cell me, Board board, int apply) {
    /* We check that the orginal cell contains a pawn of the right color */
    if (board_get_cell(board, move_get_from_line(move), move_get_from_column(move)) != me) {
        return 0;
    }

    /* We check that the middle cell contains a pawn of the right color */
    if (board_get_cell(board, move_get_from_line(move) + sign(move_get_to_line(move) - move_get_from_line(move)), move_get_from_column(move) + sign(move_get_to_column(move) - move_get_from_column(move))) != me) {
        return 0;
    }

    /* Two cases for the destination cell */
    Cell arrivee = board_get_cell(board, move_get_to_line(move), move_get_to_column(move));
    if (arrivee == CELL_EMPTY) {
        /* We move the pawn */
        if (apply) {
            board_set_cell(board, move_get_to_line(move), move_get_to_column(move), me);
            board_set_cell(board, move_get_from_line(move), move_get_from_column(move), CELL_EMPTY);
        }
        return 1;
    }
    if (arrivee == cell_opposite(me)) {
        int toLine2 = move_get_to_line(move) + sign(move_get_to_line(move) - move_get_from_line(move));
        int toColumn2 = move_get_to_column(move) + sign(move_get_to_column(move) - move_get_from_column(move));
        Cell arrivee2 = board_get_cell(board, toLine2, toColumn2);

        /* We check that the destination cell is empty */
        if (arrivee2 != CELL_EMPTY) {
            return 0;
        }

        /* We move the pawn */
        if (apply) {
            board_set_cell(board, toLine2, toColumn2, cell_opposite(me));
            board_set_cell(board, move_get_to_line(move), move_get_to_column(move), me);
            board_set_cell(board, move_get_from_line(move), move_get_from_column(move), CELL_EMPTY);
        }
        return 1;
    }

    return 0;
}

int move_line_three(Move move, Cell me, Board board, int apply) {
    /* We check that the original cell contains a pawn of the right color */
    if (board_get_cell(board, move_get_from_line(move), move_get_from_column(move)) != me) {
        return 0;
    }

    /* We check that the middle cells contain a pawn of the right color */
    if (board_get_cell(board, move_get_from_line(move) + sign(move_get_to_line(move) - move_get_from_line(move)), move_get_from_column(move) + sign(move_get_to_column(move) - move_get_from_column(move))) != me) {
        return 0;
    }
    if (board_get_cell(board, move_get_from_line(move) + 2 * sign(move_get_to_line(move) - move_get_from_line(move)), move_get_from_column(move) + 2 * sign(move_get_to_column(move) - move_get_from_column(move))) != me) {
        return 0;
    }

    /* Two cases for the destination cell */
    Cell arrivee = board_get_cell(board, move_get_to_line(move), move_get_to_column(move));
    if (arrivee == CELL_EMPTY) {
        /* We move the pawn */
        if (apply) {
            board_set_cell(board, move_get_to_line(move), move_get_to_column(move), me);
            board_set_cell(board, move_get_from_line(move), move_get_from_column(move), CELL_EMPTY);
        }
        return 1;
    }
    if (arrivee == cell_opposite(me)) {
        int toLine2 = move_get_to_line(move) + sign(move_get_to_line(move) - move_get_from_line(move));
        int toColumn2 = move_get_to_column(move) + sign(move_get_to_column(move) - move_get_from_column(move));
        Cell arrivee2 = board_get_cell(board, toLine2, toColumn2);

        if (arrivee2 == CELL_EMPTY) {
            /* We move the pawn */
            if (apply) {
                board_set_cell(board, toLine2, toColumn2, cell_opposite(me));
                board_set_cell(board, move_get_to_line(move), move_get_to_column(move), me);
                board_set_cell(board, move_get_from_line(move), move_get_from_column(move), CELL_EMPTY);
            }
            return 1;
        }
        if (arrivee2 == cell_opposite(me)) {
            int toLine3 = move_get_to_line(move) + 2 * sign(move_get_to_line(move) - move_get_from_line(move));
            int toColumn3 = move_get_to_column(move) + 2 * sign(move_get_to_column(move) - move_get_from_column(move));
            Cell arrivee3 = board_get_cell(board, toLine3, toColumn3);

            /* We check that the destination cell is empty */
            if (arrivee3 != CELL_EMPTY) {
                return 0;
            }

            /* We move the pawns */
            if (apply) {
                board_set_cell(board, toLine3, toColumn3, cell_opposite(me));
                board_set_cell(board, toLine2, toColumn2, cell_opposite(me));
                board_set_cell(board, move_get_to_line(move), move_get_to_column(move), me);
                board_set_cell(board, move_get_from_line(move) + sign(move_get_to_line(move) - move_get_from_line(move)), move_get_from_column(move) + sign(move_get_to_column(move) - move_get_from_column(move)), me);
                board_set_cell(board, move_get_from_line(move) + 2 * sign(move_get_to_line(move) - move_get_from_line(move)), move_get_from_column(move) + 2 * sign(move_get_to_column(move) - move_get_from_column(move)), me);
                board_set_cell(board, move_get_from_line(move), move_get_from_column(move), CELL_EMPTY);
            }
            return 1;
        }
    }

    return 0;
}

int move_lateral_two(Move move, Cell me, Board board, int apply) {
    /* We check that the original cell contains a pawn of the right color */
    if (board_get_cell(board, move_get_from_line(move), move_get_from_column(move)) != me) {
        return 0;
    }

    /* We check that the destination cell is empty */
    if (board_get_cell(board, move_get_to_line(move), move_get_to_column(move)) != CELL_EMPTY) {
        return 0;
    }

    /* We check that the middle cells contain a pawn of the right color */
    Cell intermediare1 = board_get_cell(board, move_get_from_line(move), move_get_to_column(move));
    Cell intermediare2 = board_get_cell(board, move_get_to_line(move), move_get_from_column(move));
    if (intermediare1 == CELL_EMPTY && intermediare2 == me) {
        /* We move the pawns (we exchange them) */
        if (apply) {
            board_set_cell(board, move_get_to_line(move), move_get_to_column(move), me);
            board_set_cell(board, move_get_from_line(move), move_get_from_column(move), CELL_EMPTY);
            board_set_cell(board, move_get_from_line(move), move_get_to_column(move), me);
            board_set_cell(board, move_get_to_line(move), move_get_from_column(move), CELL_EMPTY);
        }
        return 1;
    }
    if (intermediare1 == me && intermediare2 == CELL_EMPTY) {
        /* We move the pawns (we exchange them) */
        if (apply) {
            board_set_cell(board, move_get_to_line(move), move_get_to_column(move), me);
            board_set_cell(board, move_get_from_line(move), move_get_from_column(move), CELL_EMPTY);
            board_set_cell(board, move_get_from_line(move), move_get_to_column(move), CELL_EMPTY);
            board_set_cell(board, move_get_to_line(move), move_get_from_column(move), me);
        }
        return 1;
    }

    return 0;
}

int move_lateral_three(Move move, Cell me, Board board, int apply) {
    /* We check that the original cell contains a pawn of the right color */
    if (board_get_cell(board, move_get_from_line(move), move_get_from_column(move)) != me) {
        return 0;
    }

    /* We check that the destination cell is empty */
    if (board_get_cell(board, move_get_to_line(move), move_get_to_column(move)) != CELL_EMPTY) {
        return 0;
    }

    /* We check that the middle cells contain a pawn of the right color */
    Cell intermediare1 = board_get_cell(board, move_get_from_line(move), move_get_to_column(move));
    Cell intermediare2 = board_get_cell(board, move_get_to_line(move), move_get_from_column(move));
    int dx = abs(move_get_to_column(move) - move_get_from_column(move));
    int dy = abs(move_get_to_line(move) - move_get_from_line(move));

    if (dy == 2 && intermediare1 == CELL_EMPTY && intermediare2 == me) {
        /* We check the middle cells (we know that we have pawns aligned vertically) */
        Cell milieu1 = board_get_cell(board, move_get_from_line(move) + sign(move_get_to_line(move) - move_get_from_line(move)), move_get_from_column(move));
        Cell milieu2 = board_get_cell(board, move_get_from_line(move) + sign(move_get_to_line(move) - move_get_from_line(move)), move_get_to_column(move));
        if (milieu1 != me || milieu2 != CELL_EMPTY) {
            return 0;
        }

        /* We move the pawns (we exchange them) */
        
        if (apply) {
            board_set_cell(board, move_get_to_line(move), move_get_to_column(move), me);
            board_set_cell(board, move_get_from_line(move), move_get_from_column(move), CELL_EMPTY);
            board_set_cell(board, move_get_from_line(move), move_get_to_column(move), me);
            board_set_cell(board, move_get_to_line(move), move_get_from_column(move), CELL_EMPTY);
            board_set_cell(board, move_get_from_line(move) + sign(move_get_to_line(move) - move_get_from_line(move)), move_get_from_column(move), CELL_EMPTY);
            board_set_cell(board, move_get_from_line(move) + sign(move_get_to_line(move) - move_get_from_line(move)), move_get_to_column(move), me);
        }
        return 1;
    }
    if (dx == 2 && intermediare1 == me && intermediare2 == CELL_EMPTY) {
        /* We check the middle cells (we know that we have pawns aligned vertically) */
        Cell milieu1 = board_get_cell(board, move_get_from_line(move), move_get_from_column(move) + sign(move_get_to_column(move) - move_get_from_column(move)));
        Cell milieu2 = board_get_cell(board, move_get_to_line(move), move_get_from_column(move) + sign(move_get_to_column(move) - move_get_from_column(move)));
        if (milieu1 != me || milieu2 != CELL_EMPTY) {
            return 0;
        }

        /* We move the pawns (we exchange them) */
        if (apply) {
            board_set_cell(board, move_get_to_line(move), move_get_to_column(move), me);
            board_set_cell(board, move_get_from_line(move), move_get_from_column(move), CELL_EMPTY);
            board_set_cell(board, move_get_from_line(move), move_get_to_column(move), CELL_EMPTY);
            board_set_cell(board, move_get_to_line(move), move_get_from_column(move), me);
            board_set_cell(board, move_get_from_line(move), move_get_from_column(move) + sign(move_get_to_column(move) - move_get_from_column(move)), CELL_EMPTY);
            board_set_cell(board, move_get_to_line(move), move_get_from_column(move) + sign(move_get_to_column(move) - move_get_from_column(move)), me);
        }
        return 1;
    }

    return 0;
}

/* Routing moves */

int move_apply(Move move, Cell me, Board board, int apply) {
    /* Routing moves according to its category */
    int dx = abs(move_get_to_column(move) - move_get_from_column(move));
    int dy = abs(move_get_to_line(move) - move_get_from_line(move));

    if ((dx == 0 && dy == 1) || (dx == 1 && dy == 0)) {
        /* Move 1 color */
        return move_line_one(move, me, board, apply);
    }
    if ((dx == 0 && dy == 2) || (dx == 2 && dy == 0)) {
        /* Move 2 colors in a line */
        return move_line_two(move, me, board, apply);
    }
    if ((dx == 0 && dy == 3) || (dx == 3 && dy == 0)) {
        /* Move 3 colors in a line */
        return move_line_three(move, me, board, apply);
    }
    if (dx == 1 && dy == 1) {
        /* Move 2 colors laterally */
        return move_lateral_two(move, me, board, apply);
    }
    if ((dx == 2 && dy == 1) || (dx == 1 && dy == 2)) {
        /* Move 3 colors laterally */
        return move_lateral_three(move, me, board, apply);
    }

    return 0;
}

/* Available Move */

void move_available(Cell me, Board board, Move array[MOVE_LIST_SIZE]) {
    /* List all possible moves */
    int index = 0;

    for (int line = 0; line < BOARD_SIZE; line++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            /* Check that current cell is mine */
            if (board_get_cell(board, line, col) != me) {
                continue;
            }

            /* Single pawn move */
            /* We check that the right cell is empty */
            if (col < BOARD_SIZE - 1 && move_line_one(move_create(line, col, line, col + 1), me, board, 0)) {
                array[index] = move_create(line, col, line, col + 1);
                index++;
            }
            /* We check that the bottom cell is empty */
            if (line < BOARD_SIZE - 1 && move_line_one(move_create(line, col, line + 1, col), me, board, 0)) {
                array[index] = move_create(line, col, line + 1, col);
                index++;
            }
            /* We check that the left cell is empty */
            if (col > 0 && move_line_one(move_create(line, col, line, col - 1), me, board, 0)) {
                array[index] = move_create(line, col, line, col - 1);
                index++;
            }
            /* We check that the top cell is empty */
            if (line > 0 && move_line_one(move_create(line, col, line - 1, col), me, board, 0)) {
                array[index] = move_create(line, col, line - 1, col);
                index++;
            }

            /* Two pawns move */
            /* Moving in line */
            /* We check that the move is in line with 2 pawns to the right is possible (empty or enemy pawn) */
            if (col < BOARD_SIZE - 2 && move_line_two(move_create(line, col, line, col + 2), me, board, 0)) {
                array[index] = move_create(line, col, line, col + 2);
                index++;
            }
            /* We check that the move is in line with 2 pawns to the bottom is possible */
            if (line < BOARD_SIZE - 2 && move_line_two(move_create(line, col, line + 2, col), me, board, 0)) {
                array[index] = move_create(line, col, line + 2, col);
                index++;
            }
            /* We check that the move is in line with 2 pawns to the left is possible */
            if (col > 0 && move_line_two(move_create(line, col + 1, line, col - 1), me, board, 0)) {
                array[index] = move_create(line, col + 1, line, col - 1);
                index++;
            }
            /* We check that the move is in line with 2 pawns to the top */
            if (line > 0 && move_line_two(move_create(line + 1, col, line - 1, col), me, board, 0)) {
                array[index] = move_create(line + 1, col, line - 1, col);
                index++;
            }
            /* lateral move */
            /* We check that the move is in line with 2 pawns horizontal to the top */
            if (col < BOARD_SIZE - 1 && line > 0 && board_get_cell(board, line, col + 1) == me && move_lateral_two(move_create(line, col, line - 1, col + 1), me, board, 0)) {
                array[index] = move_create(line, col, line - 1, col + 1);
                index++;
            }
            /* We check that the move is in line with 2 pawns horizontal to the bottom */
            if (col < BOARD_SIZE - 1 && line < BOARD_SIZE - 1 && board_get_cell(board, line, col + 1) == me && move_lateral_two(move_create(line, col, line + 1, col + 1), me, board, 0)) {
                array[index] = move_create(line, col, line + 1, col + 1);
                index++;
            }
            /* We check that the move is in line with 2 pawns horizontal to the left */
            if (col > 0 && line < BOARD_SIZE - 1 && board_get_cell(board, line + 1, col) == me && move_lateral_two(move_create(line, col, line + 1, col - 1), me, board, 0)) {
                array[index] = move_create(line, col, line + 1, col - 1);
                index++;
            }
            /* We check that the move is in line with 2 pawns vertical to the right */
            if (col < BOARD_SIZE - 1 && line < BOARD_SIZE - 1 && board_get_cell(board, line + 1, col) == me && move_lateral_two(move_create(line, col, line + 1, col + 1), me, board, 0)) {
                array[index] = move_create(line, col, line + 1, col + 1);
                index++;
            }

            /* Three pawns move */
            /* In line move */
            /* We check that the move is in line with 3 pawns to the right (empty or enemy pawns) */
            if (col < BOARD_SIZE - 3 && move_line_three(move_create(line, col, line, col + 3), me, board, 0)) {
                array[index] = move_create(line, col, line, col + 3);
                index++;
            }
            /* We check that the move is in line with 3 pawns to the bottom */
            if (line < BOARD_SIZE - 3 && move_line_three(move_create(line, col, line + 3, col), me, board, 0)) {
                array[index] = move_create(line, col, line + 3, col);
                index++;
            }
            /* We check that the move is in line with 3 pawns to the left */
            if (col > 0 && move_line_three(move_create(line, col + 2, line, col - 1), me, board, 0)) {
                array[index] = move_create(line, col + 2, line, col - 1);
                index++;
            }
            /* We check that the move is in line with 3 pawns to the top */
            if (line > 0 && move_line_three(move_create(line + 2, col, line - 1, col), me, board, 0)) {
                array[index] = move_create(line + 2, col, line - 1, col);
                index++;
            }
            /* lateral move */
            /* We check that the move is in line with 3 pawns horizontal to the top */
            if (col < BOARD_SIZE - 2 && line > 0 && move_lateral_three(move_create(line, col, line - 1, col + 2), me, board, 0)) {
                array[index] = move_create(line, col, line - 1, col + 2);
                index++;
            }
            /* We check that the move is in line with 3 pawns horizontal to the bottom */
            if (col < BOARD_SIZE - 2 && line < BOARD_SIZE - 1 && move_lateral_three(move_create(line, col, line + 1, col + 2), me, board, 0)) {
                array[index] = move_create(line, col, line + 1, col + 2);
                index++;
            }
            /* We check that the move is in line with 3 pawns vertically to the left */
            if (col > 0 && line < BOARD_SIZE - 2 && move_lateral_three(move_create(line, col, line + 2, col - 1), me, board, 0)) {
                array[index] = move_create(line, col, line + 2, col - 1);
                index++;
            }
            /* We check that the move is in line with 3 pawns vertical to the right */
            if (col < BOARD_SIZE - 1 && line < BOARD_SIZE - 2 && move_lateral_three(move_create(line, col, line + 2, col + 1), me, board, 0)) {
                array[index] = move_create(line, col, line + 2, col + 1);
                index++;
            }
        }
    }

    /* End of array */
    array[index] = MOVE_NONE;
}
