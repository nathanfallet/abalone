#include <assert.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include "network.test.h"

Game *game_client;
Game *game_server;
int has_played = 0;

void test_network_client_server_background_start(Game *game) {
    pthread_t thread;
    pthread_create(&thread, NULL, game_start, game);
}

void test_network_client_server_background_turn_client() {
    game_turn(game_client, move_from_string("H1:G1"));
}

void test_network_client_server_background_turn_server() {
    game_turn(game_server, move_from_string("A1:B1"));
}

void test_network_client_server_update_client(Game *game, Cell me, State state) {
    if (has_played) {
        return;
    }
    if (game->playing == me) {
        pthread_t thread;
        pthread_create(&thread, NULL, test_network_client_server_background_turn_client, NULL);
    }
}

void test_network_client_server_update_server(Game *game, Cell me, State state) {
    if (has_played) {
        return;
    }
    if (game->playing == me) {
        has_played = 1;
        pthread_t thread;
        pthread_create(&thread, NULL, test_network_client_server_background_turn_server, NULL);
    }
}

void test_network_client_server_init_client(Cell owner, int ia_override, void (*refresh_opponent)(Game *game, Cell me, State state), char address[ADDRESS_LENGTH], int port) {
    game_client = game_new(owner, ia_override);
    strcpy(game_client->address, address);
    game_client->port = port;
    game_client->refresh = test_network_client_server_update_client;
    game_client->refresh_opponent = refresh_opponent;
    test_network_client_server_background_start(game_client);
}

void test_network_client_server_init_server(Cell owner, int ia_override, void (*refresh_opponent)(Game *game, Cell me, State state), char address[ADDRESS_LENGTH], int port) {
    game_server = game_new(owner, ia_override);
    strcpy(game_server->address, address);
    game_server->port = port;
    game_server->refresh = test_network_client_server_update_server;
    game_server->refresh_opponent = refresh_opponent;
    test_network_client_server_background_start(game_server);
}

void test_network_client_server() {
    network_init(CELL_BLACK, 0, test_network_client_server_init_client, "127.0.0.1", 1234);
    network_init(CELL_WHITE, 0, test_network_client_server_init_server, "", 1234);
    
    while(!has_played) {
        sleep(1);
    }

    assert(board_get_cell(game_client->board, 0, 0) == CELL_EMPTY);
    assert(board_get_cell(game_client->board, 1, 0) == CELL_WHITE);
    assert(board_get_cell(game_server->board, 7, 0) == CELL_EMPTY);
    assert(board_get_cell(game_server->board, 6, 0) == CELL_BLACK);
}

void test_network() {
    test_network_client_server();
}
