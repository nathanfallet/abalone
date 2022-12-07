#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "move.h"

// Initialisation

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

// Conversion d'une chaine de caractères en un mouvement et vice versa

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
        string[4] - '1'
    );
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

// Lecture et écriture d'une case de manière safe
// (on vérifie que les coordonnées sont valides sinon on ignore)

Cell read_cell(int x, int y, Board board) {
    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) {
        return CELL_EMPTY;
    }
    return board_get_cell(board, x, y);
}

void write_cell(int x, int y, Cell value, Board board) {
    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE) {
        return;
    }
    board_set_cell(board, x, y, value);
}

// Fonction utile

int sign(int x) {
    if (x < 0) {
        return -1;
    }
    if (x > 0) {
        return 1;
    }
    return 0;
}

// Check et application d'un mouvement sur le board

int move_line_one(Move move, Cell me, Board board, int apply) {
    // On vérifie que la case de départ contient bien un pion de la bonne couleur
    if (read_cell(move_get_from_line(move), move_get_from_column(move), board) != me) {
        return 0;
    }

    // On vérifie que la case d'arrivée est vide
    if (read_cell(move_get_to_line(move), move_get_to_column(move), board) != CELL_EMPTY) {
        return 0;
    }

    // On déplace le pion
    if (apply) {
        write_cell(move_get_to_line(move), move_get_to_column(move), me, board);
        write_cell(move_get_from_line(move), move_get_from_column(move), CELL_EMPTY, board);
    }

    return 1;
}

int move_line_two(Move move, Cell me, Board board, int apply) {
    // On vérifie que la case de départ contient bien un pion de la bonne couleur
    if (read_cell(move_get_from_line(move), move_get_from_column(move), board) != me) {
        return 0;
    }

    // On vérifie que la case intermédiaire contient bien un pion de la bonne couleur
    if (read_cell(move_get_from_line(move) + sign(move_get_to_line(move) - move_get_from_line(move)), move_get_from_column(move) + sign(move_get_to_column(move) - move_get_from_column(move)), board) != me) {
        return 0;
    }

    // Deux cas pour la case d'arrivée
    Cell arrivee = read_cell(move_get_to_line(move), move_get_to_column(move), board);
    if (arrivee == CELL_EMPTY) {
        // On déplace le pion
        if (apply) {
            write_cell(move_get_to_line(move), move_get_to_column(move), me, board);
            write_cell(move_get_from_line(move), move_get_from_column(move), CELL_EMPTY, board);
        }
        return 1;
    }
    if (arrivee == cell_opposite(me)) {
        int toLine2 = move_get_to_line(move) + sign(move_get_to_line(move) - move_get_from_line(move));
        int toColumn2 = move_get_to_column(move) + sign(move_get_to_column(move) - move_get_from_column(move));
        Cell arrivee2 = read_cell(toLine2, toColumn2, board);

        // On vérifie que la case d'arrivée est vide
        if (arrivee2 != CELL_EMPTY) {
            return 0;
        }

        // On déplace les pions
        if (apply) {
            write_cell(toLine2, toColumn2, cell_opposite(me), board);
            write_cell(move_get_to_line(move), move_get_to_column(move), me, board);
            write_cell(move_get_from_line(move), move_get_from_column(move), CELL_EMPTY, board);
        }
        return 1;
    }

    return 0;
}

int move_line_three(Move move, Cell me, Board board, int apply) {
    // On vérifie que la case de départ contient bien un pion de la bonne couleur
    if (read_cell(move_get_from_line(move), move_get_from_column(move), board) != me) {
        return 0;
    }

    // On vérifie que les cases intermédiaires contientent bien un pion de la bonne couleur
    if (read_cell(move_get_from_line(move) + sign(move_get_to_line(move) - move_get_from_line(move)), move_get_from_column(move) + sign(move_get_to_column(move) - move_get_from_column(move)), board) != me) {
        return 0;
    }
    if (read_cell(move_get_from_line(move) + 2*sign(move_get_to_line(move) - move_get_from_line(move)), move_get_from_column(move) + 2*sign(move_get_to_column(move) - move_get_from_column(move)), board) != me) {
        return 0;
    }

    // Deux cas pour la case d'arrivée
    Cell arrivee = read_cell(move_get_to_line(move), move_get_to_column(move), board);
    if (arrivee == CELL_EMPTY) {
        // On déplace le pion
        if (apply) {
            write_cell(move_get_to_line(move), move_get_to_column(move), me, board);
            write_cell(move_get_from_line(move), move_get_from_column(move), CELL_EMPTY, board);
        }
        return 1;
    }
    if (arrivee == cell_opposite(me)) {
        int toLine2 = move_get_to_line(move) + sign(move_get_to_line(move) - move_get_from_line(move));
        int toColumn2 = move_get_to_column(move) + sign(move_get_to_column(move) - move_get_from_column(move));
        Cell arrivee2 = read_cell(toLine2, toColumn2, board);

        if (arrivee2 == CELL_EMPTY) {
            // On déplace le pion
            if (apply) {
                write_cell(toLine2, toColumn2, cell_opposite(me), board);
                write_cell(move_get_to_line(move), move_get_to_column(move), me, board);
                write_cell(move_get_from_line(move), move_get_from_column(move), CELL_EMPTY, board);
            }
            return 1;
        }
        if (arrivee2 == cell_opposite(me)) {
            int toLine3 = move_get_to_line(move) + 2*sign(move_get_to_line(move) - move_get_from_line(move));
            int toColumn3 = move_get_to_column(move) + 2*sign(move_get_to_column(move) - move_get_from_column(move));
            Cell arrivee3 = read_cell(toLine3, toColumn3, board);

            // On vérifie que la case d'arrivée est vide
            if (arrivee3 != CELL_EMPTY) {
                return 0;
            }

            // On déplace les pions
            if (apply) {
                write_cell(toLine3, toColumn3, cell_opposite(me), board);
                write_cell(toLine2, toColumn2, cell_opposite(me), board);
                write_cell(move_get_to_line(move), move_get_to_column(move), me, board);
                write_cell(move_get_from_line(move) + sign(move_get_to_line(move) - move_get_from_line(move)), move_get_from_column(move) + sign(move_get_to_column(move) - move_get_from_column(move)), me, board);
                write_cell(move_get_from_line(move) + 2*sign(move_get_to_line(move) - move_get_from_line(move)), move_get_from_column(move) + 2*sign(move_get_to_column(move) - move_get_from_column(move)), me, board);
                write_cell(move_get_from_line(move), move_get_from_column(move), CELL_EMPTY, board);
            }
            return 1;
        }
    }

    return 0;
}

int move_lateral_two(Move move, Cell me, Board board, int apply) {
    // On vérifie que la case de départ contient bien un pion de la bonne couleur
    if (read_cell(move_get_from_line(move), move_get_from_column(move), board) != me) {
        return 0;
    }

    // On vérifie que la case d'arrivée est vide
    if (read_cell(move_get_to_line(move), move_get_to_column(move), board) != CELL_EMPTY) {
        return 0;
    }

    // On vérifie que les cases intermédiaires sont bonnes
    Cell intermediare1 = read_cell(move_get_from_line(move), move_get_to_column(move), board);
    Cell intermediare2 = read_cell(move_get_to_line(move), move_get_from_column(move), board);
    if (intermediare1 == CELL_EMPTY && intermediare2 == me) {
        // On déplace les pions (on les échange quoi)
        if (apply) {
            write_cell(move_get_to_line(move), move_get_to_column(move), me, board);
            write_cell(move_get_from_line(move), move_get_from_column(move), CELL_EMPTY, board);
            write_cell(move_get_from_line(move), move_get_to_column(move), me, board);
            write_cell(move_get_to_line(move), move_get_from_column(move), CELL_EMPTY, board);
        }
        return 1;
    }
    if (intermediare1 == me && intermediare2 == CELL_EMPTY) {
        // On déplace les pions (on les échange quoi)
        if (apply) {
            write_cell(move_get_to_line(move), move_get_to_column(move), me, board);
            write_cell(move_get_from_line(move), move_get_from_column(move), CELL_EMPTY, board);
            write_cell(move_get_from_line(move), move_get_to_column(move), CELL_EMPTY, board);
            write_cell(move_get_to_line(move), move_get_from_column(move), me, board);
        }
        return 1;
    }

    return 0;
}

int move_lateral_three(Move move, Cell me, Board board, int apply) {
    // On vérifie que la case de départ contient bien un pion de la bonne couleur
    if (read_cell(move_get_from_line(move), move_get_from_column(move), board) != me) {
        return 0;
    }

    // On vérifie que la case d'arrivée est vide
    if (read_cell(move_get_to_line(move), move_get_to_column(move), board) != CELL_EMPTY) {
        return 0;
    }

    // On vérifie que les cases intermédiaires sont bonnes
    Cell intermediare1 = read_cell(move_get_from_line(move), move_get_to_column(move), board);
    Cell intermediare2 = read_cell(move_get_to_line(move), move_get_from_column(move), board);
    int dx = abs(move_get_to_column(move) - move_get_from_column(move));
    int dy = abs(move_get_to_line(move) - move_get_from_line(move));

    if (dy == 2 && intermediare1 == CELL_EMPTY && intermediare2 == me) {
        // On check les pions du milieu (on sait qu'on a des pions alignés verticalement)
        Cell milieu1 = read_cell(move_get_from_line(move) + sign(move_get_to_line(move) - move_get_from_line(move)), move_get_from_column(move), board);
        Cell milieu2 = read_cell(move_get_from_line(move) + sign(move_get_to_line(move) - move_get_from_line(move)), move_get_to_column(move), board);
        if (milieu1 != me || milieu2 != CELL_EMPTY) {
            return 0;
        }

        // On déplace les pions (on les échange quoi)
        if (apply) {
            write_cell(move_get_to_line(move), move_get_to_column(move), me, board);
            write_cell(move_get_from_line(move), move_get_from_column(move), CELL_EMPTY, board);
            write_cell(move_get_from_line(move), move_get_to_column(move), me, board);
            write_cell(move_get_to_line(move), move_get_from_column(move), CELL_EMPTY, board);
            write_cell(move_get_from_line(move) + sign(move_get_to_line(move) - move_get_from_line(move)), move_get_from_column(move), CELL_EMPTY, board);
            write_cell(move_get_from_line(move) + sign(move_get_to_line(move) - move_get_from_line(move)), move_get_to_column(move), me, board);
        }
        return 1;
    }
    if (dx == 2 && intermediare1 == me && intermediare2 == CELL_EMPTY) {
        // On check les pions du milieu (on sait qu'on a des pions alignés horizontalement)
        Cell milieu1 = read_cell(move_get_from_line(move), move_get_from_column(move) + sign(move_get_to_column(move) - move_get_from_column(move)), board);
        Cell milieu2 = read_cell(move_get_to_line(move), move_get_from_column(move) + sign(move_get_to_column(move) - move_get_from_column(move)), board);
        if (milieu1 != me || milieu2 != CELL_EMPTY) {
            return 0;
        }

        // On déplace les pions (on les échange quoi)
        if (apply) {
            write_cell(move_get_to_line(move), move_get_to_column(move), me, board);
            write_cell(move_get_from_line(move), move_get_from_column(move), CELL_EMPTY, board);
            write_cell(move_get_from_line(move), move_get_to_column(move), CELL_EMPTY, board);
            write_cell(move_get_to_line(move), move_get_from_column(move), me, board);
            write_cell(move_get_from_line(move), move_get_from_column(move) + sign(move_get_to_column(move) - move_get_from_column(move)), CELL_EMPTY, board);
            write_cell(move_get_to_line(move), move_get_from_column(move) + sign(move_get_to_column(move) - move_get_from_column(move)), me, board);
        }
        return 1;
    }

    return 0;
}

// Aiguillage

int move_apply(Move move, Cell me, Board board, int apply) {
    // Aguillage du déplacement selon sa catégorie
    int dx = abs(move_get_to_column(move) - move_get_from_column(move));
    int dy = abs(move_get_to_line(move) - move_get_from_line(move));

    if ((dx == 0 && dy == 1) || (dx == 1 && dy == 0)) {
        // Move 1 color
        return move_line_one(move, me, board, apply);
    }
    if ((dx == 0 && dy == 2) || (dx == 2 && dy == 0)) {
        // Move 2 colors in a line
        return move_line_two(move, me, board, apply);
    }
    if ((dx == 0 && dy == 3) || (dx == 3 && dy == 0)) {
        // Move 3 colors in a line
        return move_line_three(move, me, board, apply);
    }
    if (dx == 1 && dy == 1) {
        // Move 2 colors laterally
        return move_lateral_two(move, me, board, apply);
    }
    if ((dx == 2 && dy == 1) || (dx == 1 && dy == 2)) {
        // Move 3 colors laterally
        return move_lateral_three(move, me, board, apply);
    }

    return 0;
}

// Coups disponibles

void move_available(Cell me, Board board, Move array[MOVE_LIST_SIZE]) {
    // Liste le nombre de déplacement possible        
    int index = 0;
    
    for(int line = 0; line < BOARD_SIZE; line++) {
        for(int col=0; col<BOARD_SIZE; col++) {
            // déplacement pion solo
            // on vérifie si la case a droite est libre
            if (col < BOARD_SIZE - 1 && move_line_one(move_create(line, col, line, col+1), me, board, 0)) {
                array[index] = move_create(line, col, line, col+1);
                index++;
            }
            // on vérifie si la case en bas est libre
            if (line < BOARD_SIZE - 1 && move_line_one(move_create(line, col, line+1, col), me, board, 0)) {
                array[index] = move_create(line, col, line+1, col);
                index++;
            }
            // on vérifie si la case en gauche est libre
            if (col > 0 && move_line_one(move_create(line, col, line, col-1), me, board, 0)) {
                array[index] = move_create(line, col, line, col-1);
                index++;
            }
            // on vérifie si la case en haut est libre
            if (line > 0 && move_line_one(move_create(line, col, line-1, col), me, board, 0)) {
                array[index] = move_create(line, col, line-1, col);
                index++;
            }

            // déplacement 2 pions
            // en ligne
            // on vérifie si le déplacement en ligne 2 pions vers la droite (libre ou pion ennemi)
            if (col < BOARD_SIZE - 2 && move_line_two(move_create(line, col, line, col+2), me, board, 0)) {
                array[index] = move_create(line, col, line, col+2);
                index++;
            }
            // on vérifie si le déplacement en ligne 2 pions vers le bas
            if (line < BOARD_SIZE - 2 && move_line_two(move_create(line, col, line+2, col), me, board, 0)) {
                array[index] = move_create(line, col, line+2, col);
                index++;
            }
            // on vérifie si le déplacement en ligne 2 pions vers la gauche
            if (col > 0 && move_line_two(move_create(line, col+1, line, col-1), me, board, 0)) {
                array[index] = move_create(line, col+1, line, col-1);
                index++;
            }
            // on vérifie si le déplacement en ligne 2 pions vers le haut
            if (line > 0 && move_line_two(move_create(line+1, col, line-1, col), me, board, 0)) {
                array[index] = move_create(line+1, col, line-1, col);
                index++;
            }
            // latéralle
            // on vérifie si le déplacement en ligne 2 pions horizontale vers le haut
            if (col < BOARD_SIZE - 1 && line > 0 && move_lateral_two(move_create(line, col, line-1, col+1), me, board, 0)) {
                array[index] = move_create(line, col, line-1, col+1);
                index++;
            }
            // on vérifie si le déplacement en ligne 2 pions horizontale vers le bas
            if (col < BOARD_SIZE - 1 && line < BOARD_SIZE - 1 && move_lateral_two(move_create(line, col, line+1, col+1), me, board, 0)) {
                array[index] = move_create(line, col, line+1, col+1);
                index++;
            }
            // on vérifie si le déplacement en ligne 2 pions verticale vers la gauche
            if (col > 0 && line < BOARD_SIZE - 1 && move_lateral_two(move_create(line, col, line+1, col-1), me, board, 0)) {
                array[index] = move_create(line, col, line+1, col-1);
                index++;
            }
            // on vérifie si le déplacement en ligne 2 pions verticale vers la droite
            if (col < BOARD_SIZE - 1 && line < BOARD_SIZE - 1 && move_lateral_two(move_create(line, col, line+1, col+1), me, board, 0)) {
                array[index] = move_create(line, col, line+1, col+1);
                index++;
            }

            // déplacement 3 pions
            // en ligne
            // on vérifie si le déplacement en ligne 3 pions vers la droite (libre ou pion ennemi)
            if (col < BOARD_SIZE - 3 && move_line_three(move_create(line, col, line, col+3), me, board, 0)) {
                array[index] = move_create(line, col, line, col+3);
                index++;
            }
            // on vérifie si le déplacement en ligne 3 pions vers le bas
            if (line < BOARD_SIZE - 3 && move_line_three(move_create(line, col, line+3, col), me, board, 0)) {
                array[index] = move_create(line, col, line+3, col);
                index++;
            }
            // on vérifie si le déplacement en ligne 3 pions vers la gauche
            if (col > 0 && move_line_three(move_create(line, col+2, line, col-1), me, board, 0)) {
                array[index] = move_create(line, col+2, line, col-1);
                index++;
            }
            // on vérifie si le déplacement en ligne 3 pions vers le haut
            if (line > 0 && move_line_three(move_create(line+2, col, line-1, col), me, board, 0)) {
                array[index] = move_create(line+2, col, line-1, col);
                index++;
            }
            // latéralle
            // on vérifie si le déplacement en ligne 3 pions horizontale vers le haut
            if (col < BOARD_SIZE - 2 && line > 0 && move_lateral_three(move_create(line, col, line-1, col+2), me, board, 0)) {
                array[index] = move_create(line, col, line-1, col+2);
                index++;
            }
            // on vérifie si le déplacement en ligne 3 pions horizontale vers le bas
            if (col < BOARD_SIZE - 2 && line < BOARD_SIZE - 1 && move_lateral_three(move_create(line, col, line+1, col+2), me, board, 0)) {
                array[index] = move_create(line, col, line+1, col+2);
                index++;
            }
            // on vérifie si le déplacement en ligne 3 pions verticale vers la gauche
            if (col > 0 && line < BOARD_SIZE - 2 && move_lateral_three(move_create(line, col, line+2, col-1), me, board, 0)) {
                array[index] = move_create(line, col, line+2, col-1);
                index++;
            }
            // on vérifie si le déplacement en ligne 3 pions verticale vers la droite
            if (col < BOARD_SIZE - 1 && line < BOARD_SIZE - 2 && move_lateral_three(move_create(line, col, line+2, col+1), me, board, 0)) {
                array[index] = move_create(line, col, line+2, col+1);
                index++;
            }
        }
    }

    /* End of array */
    array[index] = MOVE_NONE;
}
