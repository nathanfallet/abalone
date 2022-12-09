#ifndef CONSTANTS_H
#define CONSTANTS_H

#define BOARD_SIZE 8

/**
 * Cellule vide 
 */
#define CELL_EMPTY 0 

/**
 * Cellule noire 
 */
#define CELL_BLACK 1

/**
 * Cellule blanche
 */
#define CELL_WHITE 2

/**
 * Partie en cours
 */
#define STATE_PLAYING 0

/**
 * Partie terminée, victoire noire
 */
#define STATE_WIN_BLACK 1

/**
 * Partie terminée, victoire blanche
 */
#define STATE_WIN_WHITE 2

/**
 * Move vide
 */
#define MOVE_NONE 0

/**
 * Taille maximale de la liste des moves
 */
#define MOVE_LIST_SIZE 280

/**
 * Poids d'un move gagnant (dans scored_move_compute)
 */
#define WEIGHT_WIN 100000

/**
 * Poids d'un move gagnant (dans ia_minimax_compare directement)
 */
#define WEIGHT_WIN_DIRECT 1000000

/**
 * Poids quand un pion est voisin
 */
#define WEIGHT_NEIGHBOUR 2

/**
 * Poids quand un pion est proche
 */
#define WEIGHT_PROXIMITY 1

/**
 * Poids quand un pion est au centre
 */
#define WEIGHT_CENTER 5

/**
 * Poids quand un pion peut pousser un autre pion
 */
#define WEIGHT_OPPOSITE 3

/**
 * Nombre de pions par joueur
 */
#define PAWN_TOT 14

/**
 * Constante d'initialisation (aucune)
 */
#define INIT_NONE -1

/**
 * Constante d'initialisation (terminal)
 */
#define INIT_TERMINAL 0

/**
 * Constante d'initialisation (interface graphique)
 */
#define INIT_GUI 1

/**
 * Constante d'initialisation (réseau)
 */
#define INIT_NETWORK 2

/**
 * Constante d'initialisation par défaut
 */
#define INIT_DEFAULT INIT_GUI

/**
 * Taille maximale d'une adresse IP
 */
#define ADDRESS_LENGTH 16

/**
 * Couleurs dans le terminal
 */
#define color(param) printf("\033[%sm",param)

#endif
