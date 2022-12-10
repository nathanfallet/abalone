#ifndef CONSTANTS_H
#define CONSTANTS_H

#define BOARD_SIZE 8

/**
 * \brief Cellule vide 
 */
#define CELL_EMPTY 0 

/**
 * \brief Cellule noire 
 */
#define CELL_BLACK 1

/**
 * \brief Cellule blanche
 */
#define CELL_WHITE 2

/**
 * \brief Partie en cours
 */
#define STATE_PLAYING 0

/**
 * \brief Partie terminée, victoire noire
 */
#define STATE_WIN_BLACK 1

/**
 * \brief Partie terminée, victoire blanche
 */
#define STATE_WIN_WHITE 2

/**
 * \brief Move vide
 */
#define MOVE_NONE 0

/**
 * \brief Taille maximale de la liste des moves
 */
#define MOVE_LIST_SIZE 280

/**
 * \brief Poids d'un move gagnant (dans scored_move_compute)
 */
#define WEIGHT_WIN 100000

/**
 * \brief Poids d'un move gagnant (dans ia_minimax_compare directement)
 */
#define WEIGHT_WIN_DIRECT 1000000

/**
 * \brief Poids quand un pion est voisin
 */
#define WEIGHT_NEIGHBOUR 2

/**
 * \brief Poids quand un pion est proche
 */
#define WEIGHT_PROXIMITY 1

/**
 * \brief Poids quand un pion est au centre
 */
#define WEIGHT_CENTER 3

/**
 * \brief Poids quand un pion peut pousser un autre pion
 */
#define WEIGHT_OPPOSITE 3

/**
 * \brief Nombre de pions par joueur
 */
#define PAWN_TOT 14

/**
 * \brief Constante d'initialisation (aucune)
 */
#define INIT_NONE -1

/**
 * \brief Constante d'initialisation (terminal)
 */
#define INIT_TERMINAL 0

/**
 * \brief Constante d'initialisation (interface graphique)
 */
#define INIT_GUI 1

/**
 * \brief Constante d'initialisation (réseau)
 */
#define INIT_NETWORK 2

/**
 * \brief Constante d'initialisation par défaut
 */
#define INIT_DEFAULT INIT_GUI

/**
 * \brief Taille maximale d'une adresse IP
 */
#define ADDRESS_LENGTH 16

/**
 * \brief Couleurs dans le terminal
 */
#define color(param) printf("\033[%sm",param)

#endif
