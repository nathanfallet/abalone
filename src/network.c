#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "network.h"

void network_init(Cell owner, void (*init)(Cell owner, void (*actualiser_adversaire)(PGame game, Cell me, State state)), char address[ADDRESS_LENGTH], int port) {
    // TODO: Initialiser la connexion réseau (client ou serveur)

    // Et on init le reste comme d'habitude
    init(owner, network_update);
}

void network_update(PGame game, Cell me, State state){
    // TODO: Envoyer le coup joué à l'adversaire et attendre sa réponse
}
