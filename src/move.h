#ifndef MOVE_H
#define MOVE_H

/**
 * \file move.h
 * \brief Gestion d'un mouvement
 * 
 * Gestion d'un mouvement, avec les vérifications nécessaires
 */

#include "constants.h"
#include "board.h"
#include "cell.h"

/**
 * Représente un mouvement
 */
typedef unsigned short Move;

/**
 * \brief Créé un mouvement
 * \param fromLine La ligne de départ du mouvement
 * \param fromColumn La colonne de départ du mouvement
 * \param toLine La ligne d'arrivée du mouvement
 * \param toColumn La colonne d'arrivée du mouvement
 * \return Le mouvement crée
 */
Move move_create(unsigned char fromLine, unsigned char fromColumn, unsigned char toLine, unsigned char toColumn);

/**
 * \brief Lire la ligne de départ du mouvement
 * \param move Le mouvement que l'on veut lire
 * \return La ligne de départ du mouvement
 */
unsigned char move_get_from_line(Move move);

/**
 * \brief Lire la colonne de départ du mouvement
 * \param move Le mouvement que l'on veut lire
 * \return La colonne de départ du mouvement
 */
unsigned char move_get_from_column(Move move);

/**
 * \brief Lire la ligne d'arrivée du mouvement
 * \param move Le mouvement que l'on veut lire
 * \return La ligne d'arrivée du mouvement
 */
unsigned char move_get_to_line(Move move);

/**
 * \brief Lire la colonne d'arrivée du mouvement
 * \param move Le mouvement que l'on veut lire
 * \return La colonne d'arrivée du mouvement
 */
unsigned char move_get_to_column(Move move);

/**
 * \brief Convertir la chaîne de caractère en un mouvement
 * \param string Est la chaîne de caractère correspondant à un mouvement
 * on peut utiliser des lettres minuscules ou majuscules. Cette chaîne de
 * caractères permet au joueur d'entrer le mouvement qu'il souhaite faire
 * \return Le mouvement correspondant à la chaîne correspondante
 */
Move move_from_string(char *string);

/**
 * \brief Convertir le mouvement en une chaîne de caractères
 * \param move Le mouvement que l'on veut convertir
 * \return La chaîne de caractères correspondante au mouvement
 */
char *move_to_string(Move move);

/**
 * \brief Vérifier la validité du mouvement et l'appliquer le cas échéant
 * \param move Le mouvement que l'on veut appliquer
 * \param me Correspond à la couleur du joueur puisque la validité du
 * mouvement varie en fonction de la couleur des pions
 * \param board Représente le plateau au moment où l'on veut appliquer le
 * mouvement
 * \param apply Si apply vaut 0, permet uniquement de vérifier la validité du mouvement
 * Si apply vaut 1, permet de vérifier la validité du mouvement et l'applique le cas échéant
 * \return si le move est valide (0 pour erreur et 1 pour valide)
 */
int move_apply(Move move, Cell me, Board board, int apply);

/**
 * \brief Lister le nombre de mouvement possible
 * \param me Correspond à la couleur du joueur dont on veut savoir les mouvements
 * possibles sur le plateau
 * \param board Représente le plateau au moment où l'on veut savoir tous les
 * mouvements possibles
 * \param array Récupère tous les mouvements possibles du joueur "me"
 */
void move_available(Cell me, Board board, Move array[MOVE_LIST_SIZE]);

#endif
