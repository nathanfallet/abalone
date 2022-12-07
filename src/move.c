#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "move.h"

// Initialisation avec un pointeur 

Move *move_create(int fromLine, int fromColumn, int toLine, int toColumn) {
    Move *move = malloc(sizeof(Move));
    move->fromLine = fromLine;
    move->fromColumn = fromColumn;
    move->toLine = toLine;
    move->toColumn = toColumn;
    return move;
}

// Conversion d'une chaine de caractères en un mouvement et vice versa

Move move_from_string(char *str) {
    Move move;
    char fromLine = str[0];
    if (fromLine >= 'a' && fromLine <= 'h') {
        fromLine -= 32;
    }
    move.fromLine = fromLine - 'A';
    move.fromColumn = str[1] - '1';
    char toLine = str[3];
    if (toLine >= 'a' && toLine <= 'h') {
        toLine -= 32;
    }
    move.toLine = toLine - 'A';
    move.toColumn = str[4] - '1';
    return move;
}

char *move_to_string(Move move) {
    char *str = malloc(6 * sizeof(char));
    str[0] = move.fromLine + 'A';
    str[1] = move.fromColumn + '1';
    str[2] = ':';
    str[3] = move.toLine + 'A';
    str[4] = move.toColumn + '1';
    str[5] = '\0';
    return str;
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
    if (read_cell(move.fromLine, move.fromColumn, board) != me) {
        return 0;
    }

    // On vérifie que la case d'arrivée est vide
    if (read_cell(move.toLine, move.toColumn, board) != CELL_EMPTY) {
        return 0;
    }

    // On déplace le pion
    if (apply) {
        write_cell(move.toLine, move.toColumn, me, board);
        write_cell(move.fromLine, move.fromColumn, CELL_EMPTY, board);
    }

    return 1;
}

int move_line_two(Move move, Cell me, Board board, int apply) {
    // On vérifie que la case de départ contient bien un pion de la bonne couleur
    if (read_cell(move.fromLine, move.fromColumn, board) != me) {
        return 0;
    }

    // On vérifie que la case intermédiaire contient bien un pion de la bonne couleur
    if (read_cell(move.fromLine + sign(move.toLine - move.fromLine), move.fromColumn + sign(move.toColumn - move.fromColumn), board) != me) {
        return 0;
    }

    // Deux cas pour la case d'arrivée
    Cell arrivee = read_cell(move.toLine, move.toColumn, board);
    if (arrivee == CELL_EMPTY) {
        // On déplace le pion
        if (apply) {
            write_cell(move.toLine, move.toColumn, me, board);
            write_cell(move.fromLine, move.fromColumn, CELL_EMPTY, board);
        }
        return 1;
    }
    if (arrivee == cell_opposite(me)) {
        int toLine2 = move.toLine + sign(move.toLine - move.fromLine);
        int toColumn2 = move.toColumn + sign(move.toColumn - move.fromColumn);
        Cell arrivee2 = read_cell(toLine2, toColumn2, board);

        // On vérifie que la case d'arrivée est vide
        if (arrivee2 != CELL_EMPTY) {
            return 0;
        }

        // On déplace les pions
        if (apply) {
            write_cell(toLine2, toColumn2, cell_opposite(me), board);
            write_cell(move.toLine, move.toColumn, me, board);
            write_cell(move.fromLine, move.fromColumn, CELL_EMPTY, board);
        }
        return 1;
    }

    return 0;
}

int move_line_three(Move move, Cell me, Board board, int apply) {
    // On vérifie que la case de départ contient bien un pion de la bonne couleur
    if (read_cell(move.fromLine, move.fromColumn, board) != me) {
        return 0;
    }

    // On vérifie que les cases intermédiaires contientent bien un pion de la bonne couleur
    if (read_cell(move.fromLine + sign(move.toLine - move.fromLine), move.fromColumn + sign(move.toColumn - move.fromColumn), board) != me) {
        return 0;
    }
    if (read_cell(move.fromLine + 2*sign(move.toLine - move.fromLine), move.fromColumn + 2*sign(move.toColumn - move.fromColumn), board) != me) {
        return 0;
    }

    // Deux cas pour la case d'arrivée
    Cell arrivee = read_cell(move.toLine, move.toColumn, board);
    if (arrivee == CELL_EMPTY) {
        // On déplace le pion
        if (apply) {
            write_cell(move.toLine, move.toColumn, me, board);
            write_cell(move.fromLine, move.fromColumn, CELL_EMPTY, board);
        }
        return 1;
    }
    if (arrivee == cell_opposite(me)) {
        int toLine2 = move.toLine + sign(move.toLine - move.fromLine);
        int toColumn2 = move.toColumn + sign(move.toColumn - move.fromColumn);
        Cell arrivee2 = read_cell(toLine2, toColumn2, board);

        if (arrivee2 == CELL_EMPTY) {
            // On déplace le pion
            if (apply) {
                write_cell(toLine2, toColumn2, cell_opposite(me), board);
                write_cell(move.toLine, move.toColumn, me, board);
                write_cell(move.fromLine, move.fromColumn, CELL_EMPTY, board);
            }
            return 1;
        }
        if (arrivee2 == cell_opposite(me)) {
            int toLine3 = move.toLine + 2*sign(move.toLine - move.fromLine);
            int toColumn3 = move.toColumn + 2*sign(move.toColumn - move.fromColumn);
            Cell arrivee3 = read_cell(toLine3, toColumn3, board);

            // On vérifie que la case d'arrivée est vide
            if (arrivee3 != CELL_EMPTY) {
                return 0;
            }

            // On déplace les pions
            if (apply) {
                write_cell(toLine3, toColumn3, cell_opposite(me), board);
                write_cell(toLine2, toColumn2, cell_opposite(me), board);
                write_cell(move.toLine, move.toColumn, me, board);
                write_cell(move.fromLine + sign(move.toLine - move.fromLine), move.fromColumn + sign(move.toColumn - move.fromColumn), me, board);
                write_cell(move.fromLine + 2*sign(move.toLine - move.fromLine), move.fromColumn + 2*sign(move.toColumn - move.fromColumn), me, board);
                write_cell(move.fromLine, move.fromColumn, CELL_EMPTY, board);
            }
            return 1;
        }
    }

    return 0;
}

int move_lateral_two(Move move, Cell me, Board board, int apply) {
    // On vérifie que la case de départ contient bien un pion de la bonne couleur
    if (read_cell(move.fromLine, move.fromColumn, board) != me) {
        return 0;
    }

    // On vérifie que la case d'arrivée est vide
    if (read_cell(move.toLine, move.toColumn, board) != CELL_EMPTY) {
        return 0;
    }

    // On vérifie que les cases intermédiaires sont bonnes
    Cell intermediare1 = read_cell(move.fromLine, move.toColumn, board);
    Cell intermediare2 = read_cell(move.toLine, move.fromColumn, board);
    if (intermediare1 == CELL_EMPTY && intermediare2 == me) {
        // On déplace les pions (on les échange quoi)
        if (apply) {
            write_cell(move.toLine, move.toColumn, me, board);
            write_cell(move.fromLine, move.fromColumn, CELL_EMPTY, board);
            write_cell(move.fromLine, move.toColumn, me, board);
            write_cell(move.toLine, move.fromColumn, CELL_EMPTY, board);
        }
        return 1;
    }
    if (intermediare1 == me && intermediare2 == CELL_EMPTY) {
        // On déplace les pions (on les échange quoi)
        if (apply) {
            write_cell(move.toLine, move.toColumn, me, board);
            write_cell(move.fromLine, move.fromColumn, CELL_EMPTY, board);
            write_cell(move.fromLine, move.toColumn, CELL_EMPTY, board);
            write_cell(move.toLine, move.fromColumn, me, board);
        }
        return 1;
    }

    return 0;
}

int move_lateral_three(Move move, Cell me, Board board, int apply) {
    // On vérifie que la case de départ contient bien un pion de la bonne couleur
    if (read_cell(move.fromLine, move.fromColumn, board) != me) {
        return 0;
    }

    // On vérifie que la case d'arrivée est vide
    if (read_cell(move.toLine, move.toColumn, board) != CELL_EMPTY) {
        return 0;
    }

    // On vérifie que les cases intermédiaires sont bonnes
    Cell intermediare1 = read_cell(move.fromLine, move.toColumn, board);
    Cell intermediare2 = read_cell(move.toLine, move.fromColumn, board);
    int dx = abs(move.toColumn - move.fromColumn);
    int dy = abs(move.toLine - move.fromLine);

    if (dy == 2 && intermediare1 == CELL_EMPTY && intermediare2 == me) {
        // On check les pions du milieu (on sait qu'on a des pions alignés verticalement)
        Cell milieu1 = read_cell(move.fromLine + sign(move.toLine - move.fromLine), move.fromColumn, board);
        Cell milieu2 = read_cell(move.fromLine + sign(move.toLine - move.fromLine), move.toColumn, board);
        if (milieu1 != me || milieu2 != CELL_EMPTY) {
            return 0;
        }

        // On déplace les pions (on les échange quoi)
        if (apply) {
            write_cell(move.toLine, move.toColumn, me, board);
            write_cell(move.fromLine, move.fromColumn, CELL_EMPTY, board);
            write_cell(move.fromLine, move.toColumn, me, board);
            write_cell(move.toLine, move.fromColumn, CELL_EMPTY, board);
            write_cell(move.fromLine + sign(move.toLine - move.fromLine), move.fromColumn, CELL_EMPTY, board);
            write_cell(move.fromLine + sign(move.toLine - move.fromLine), move.toColumn, me, board);
        }
        return 1;
    }
    if (dx == 2 && intermediare1 == me && intermediare2 == CELL_EMPTY) {
        // On check les pions du milieu (on sait qu'on a des pions alignés horizontalement)
        Cell milieu1 = read_cell(move.fromLine, move.fromColumn + sign(move.toColumn - move.fromColumn), board);
        Cell milieu2 = read_cell(move.toLine, move.fromColumn + sign(move.toColumn - move.fromColumn), board);
        if (milieu1 != me || milieu2 != CELL_EMPTY) {
            return 0;
        }

        // On déplace les pions (on les échange quoi)
        if (apply) {
            write_cell(move.toLine, move.toColumn, me, board);
            write_cell(move.fromLine, move.fromColumn, CELL_EMPTY, board);
            write_cell(move.fromLine, move.toColumn, CELL_EMPTY, board);
            write_cell(move.toLine, move.fromColumn, me, board);
            write_cell(move.fromLine, move.fromColumn + sign(move.toColumn - move.fromColumn), CELL_EMPTY, board);
            write_cell(move.toLine, move.fromColumn + sign(move.toColumn - move.fromColumn), me, board);
        }
        return 1;
    }

    return 0;
}

// Aiguillage

int move_apply(Move move, Cell me, Board board, int apply) {
    // Aguillage du déplacement selon sa catégorie
    int dx = abs(move.toColumn - move.fromColumn);
    int dy = abs(move.toLine - move.fromLine);

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

List *move_available(Cell me, Board board) {
    // Liste le nombre de déplacement possible        
    List *list = list_init();
    
    for(int line = 0; line < BOARD_SIZE; line++) {
        for(int col=0; col<BOARD_SIZE; col++) {
            // déplacement pion solo
            // on vérifie si la case a droite est libre
            if (col < BOARD_SIZE - 1 && move_line_one((Move){line, col, line, col+1}, me, board, 0)) {
                list_insere(move_create(line, col, line, col+1), list_taille(list)+1, list);
            }
            // on vérifie si la case en bas est libre
            if (line < BOARD_SIZE - 1 && move_line_one((Move){line, col, line+1, col}, me, board, 0)) {
                list_insere(move_create(line, col, line+1, col), list_taille(list)+1, list);
            }
            // on vérifie si la case en gauche est libre
            if (col > 0 && move_line_one((Move){line, col, line, col-1}, me, board, 0)) {
                list_insere(move_create(line, col, line, col-1), list_taille(list)+1, list);
            }
            // on vérifie si la case en haut est libre
            if (line > 0 && move_line_one((Move){line, col, line-1, col}, me, board, 0)) {
                list_insere(move_create(line, col, line-1, col), list_taille(list)+1, list);
            }

            // déplacement 2 pions
            // en ligne
            // on vérifie si le déplacement en ligne 2 pions vers la droite (libre ou pion ennemi)
            if (col < BOARD_SIZE - 2 && move_line_two((Move){line, col, line, col+2}, me, board, 0)) {
                list_insere(move_create(line, col, line, col+2), list_taille(list)+1, list);
            }
            // on vérifie si le déplacement en ligne 2 pions vers le bas
            if (line < BOARD_SIZE - 2 && move_line_two((Move){line, col, line+2, col}, me, board, 0)) {
                list_insere(move_create(line, col, line+2, col), list_taille(list)+1, list);
            }
            // on vérifie si le déplacement en ligne 2 pions vers la gauche
            if (col > 0 && move_line_two((Move){line, col+1, line, col-1}, me, board, 0)) {
                list_insere(move_create(line, col+1, line, col-1), list_taille(list)+1, list);
            }
            // on vérifie si le déplacement en ligne 2 pions vers le haut
            if (line > 0 && move_line_two((Move){line+1, col, line-1, col}, me, board, 0)) {
                list_insere(move_create(line+1, col, line-1, col), list_taille(list)+1, list);
            }
            // latéralle
            // on vérifie si le déplacement en ligne 2 pions horizontale vers le haut
            if (col < BOARD_SIZE - 1 && line > 0 && move_lateral_two((Move){line, col, line-1, col+1}, me, board, 0)) {
                list_insere(move_create(line, col, line-1, col+1), list_taille(list)+1, list);
            }
            // on vérifie si le déplacement en ligne 2 pions horizontale vers le bas
            if (col < BOARD_SIZE - 1 && line < BOARD_SIZE - 1 && move_lateral_two((Move){line, col, line+1, col+1}, me, board, 0)) {
                list_insere(move_create(line, col, line+1, col+1), list_taille(list)+1, list);
            }
            // on vérifie si le déplacement en ligne 2 pions verticale vers la gauche
            if (col > 0 && line < BOARD_SIZE - 1 && move_lateral_two((Move){line, col, line+1, col-1}, me, board, 0)) {
                list_insere(move_create(line, col, line+1, col-1), list_taille(list)+1, list);
            }
            // on vérifie si le déplacement en ligne 2 pions verticale vers la droite
            if (col < BOARD_SIZE - 1 && line < BOARD_SIZE - 1 && move_lateral_two((Move){line, col, line+1, col+1}, me, board, 0)) {
                list_insere(move_create(line, col, line+1, col+1), list_taille(list)+1, list);
            }

            // déplacement 3 pions
            // en ligne
            // on vérifie si le déplacement en ligne 3 pions vers la droite (libre ou pion ennemi)
            if (col < BOARD_SIZE - 3 && move_line_three((Move){line, col, line, col+3}, me, board, 0)) {
                list_insere(move_create(line, col, line, col+3), list_taille(list)+1, list);
            }
            // on vérifie si le déplacement en ligne 3 pions vers le bas
            if (line < BOARD_SIZE - 3 && move_line_three((Move){line, col, line+3, col}, me, board, 0)) {
                list_insere(move_create(line, col, line+3, col), list_taille(list)+1, list);
            }
            // on vérifie si le déplacement en ligne 3 pions vers la gauche
            if (col > 0 && move_line_three((Move){line, col+2, line, col-1}, me, board, 0)) {
                list_insere(move_create(line, col+2, line, col-1), list_taille(list)+1, list);
            }
            // on vérifie si le déplacement en ligne 3 pions vers le haut
            if (line > 0 && move_line_three((Move){line+2, col, line-1, col}, me, board, 0)) {
                list_insere(move_create(line+2, col, line-1, col), list_taille(list)+1, list);
            }
            // latéralle
            // on vérifie si le déplacement en ligne 3 pions horizontale vers le haut
            if (col < BOARD_SIZE - 2 && line > 0 && move_lateral_three((Move){line, col, line-1, col+2}, me, board, 0)) {
                list_insere(move_create(line, col, line-1, col+2), list_taille(list)+1, list);
            }
            // on vérifie si le déplacement en ligne 3 pions horizontale vers le bas
            if (col < BOARD_SIZE - 2 && line < BOARD_SIZE - 1 && move_lateral_three((Move){line, col, line+1, col+2}, me, board, 0)) {
                list_insere(move_create(line, col, line+1, col+2), list_taille(list)+1, list);
            }
            // on vérifie si le déplacement en ligne 3 pions verticale vers la gauche
            if (col > 0 && line < BOARD_SIZE - 2 && move_lateral_three((Move){line, col, line+2, col-1}, me, board, 0)) {
                list_insere(move_create(line, col, line+2, col-1), list_taille(list)+1, list);
            }
            // on vérifie si le déplacement en ligne 3 pions verticale vers la droite
            if (col < BOARD_SIZE - 1 && line < BOARD_SIZE - 2 && move_lateral_three((Move){line, col, line+2, col+1}, me, board, 0)) {
                list_insere(move_create(line, col, line+2, col+1), list_taille(list)+1, list);
            }
        }
    }

    return list;
}
