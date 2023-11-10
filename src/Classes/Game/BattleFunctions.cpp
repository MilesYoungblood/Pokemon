//
// Created by Miles Youngblood on 10/25/2023.
//

#include "Game.h"

void Game::handleBattleEvents() {
    if (Game::event.type == SDL_QUIT) {
        Game::isRunning = false;
    }
}

void Game::updateBattle() {

}

void Game::renderBattle() {

}