#ifndef NETWORK_H
#define NETWORK_H

/**
 * \file network.h
 * \brief Network management
 * 
 * Network management and comunication server/client
 */

#include "game.h"
#include "cell.h"
#include "state.h"

/**
 * \brief Initialize game in network mode
 * \param owner  The player
 * \param ia_override If the AI should play instead of the player
 * \param init Initialization function 
 * \param address Server adress
 * \param port Server port
 */
void network_init(Cell owner, int ia_override, void (*init)(Cell owner, int ia_override, void (*refresh_opponent)(Game *game, Cell me, State state), char address[ADDRESS_LENGTH], int port), char address[ADDRESS_LENGTH], int port);

/**
 * \brief Execute the next turn of the network game Exécute le prochain tour de jeu de la connexion réseau
 * \param game The game
 * \param me The player
 * \param state State of the game
 */
void network_update(Game *game, Cell me, State state);

#endif
