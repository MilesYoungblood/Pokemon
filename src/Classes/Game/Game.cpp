//
// Created by Miles on 10/2/2023.
//

#include "Game.h"

Game * Game::instancePtr = nullptr;
Player * Game::player = nullptr;
Map * Game::currentMap = nullptr;

Game::Game() {
    Game::instancePtr = nullptr;
    Game::currentMap = nullptr;

    Game::run();
}

Game *Game::createGame() {
    if (Game::instancePtr == nullptr) {
        Game::instancePtr = new Game();
    }
    return Game::instancePtr;
}

void Game::destroyGame() {
    delete Game::instancePtr;
}

void Game::run() {

}
