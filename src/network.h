#ifndef NETWORK_H
#define NETWORK_H

#include "game.h"
#include "cell.h"
#include "state.h"

void network_init(Cell owner, void (*init)(Cell owner, void (*actualiser_adversaire)(PGame game, Cell me, State state)), char address[ADDRESS_LENGTH], int port);
void network_update(PGame game, Cell me, State state);

#endif
