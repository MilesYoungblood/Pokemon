//
// Created by Miles on 3/16/2024.
//

#include "../Game/Game.h"
#include "../EventHandler/EventHandler.h"
#include "../KeyManager/KeyManager.h"
#include "Scene.h"

void Scene::setState(const State x) {
    this->currentState = x;
}

bool Scene::getState(const State x) const {
    return this->currentState == x;
}

void Scene::handleEvents() {
    if (EventHandler::getInstance().pollEvent()) {
        KeyManager::getInstance().update();
        if (EventHandler::getInstance().getEventType() == SDL_QUIT) {
            Game::getInstance().terminate();
        }
    }
}
