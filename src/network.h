#ifndef NETWORK_H
#define NETWORK_H

/**
 * \file network.h
 * \brief Gestion du réseau
 * 
 * Gestion du réseau, et de la communication client/serveur.
 */

#include "game.h"
#include "cell.h"
#include "state.h"

/**
 * \brief Initialise la connexion réseau
 * \param owner La cellule du joueur
 * \param ia_override Si l'IA doit être désactivée
 * \param init La fonction d'initialisation
 * \param address L'adresse du serveur
 * \param port Le port du serveur
 */
void network_init(Cell owner, int ia_override, void (*init)(Cell owner, int ia_override, void (*actualiser_adversaire)(Game *game, Cell me, State state)), char address[ADDRESS_LENGTH], int port);

/**
 * \brief Exécute le prochain tour de jeu de la connexion réseau
 * \param game La partie
 * \param me La cellule du joueur
 * \param state L'état de la partie
 */
void network_update(Game *game, Cell me, State state);

#endif
