//
// Created by Miles on 3/16/2024.
//

#include "../Game/Game.h"
#include "../KeyManager/KeyManager.h"
#include "Scene.h"

void Scene::handleEvents() {
    static SDL_Event event;
    if (SDL_PollEvent(&event) == 1) {
        KeyManager::getInstance().update();
        if (event.type == SDL_EventType::SDL_QUIT) {
            Game::getInstance().terminate();
        }
    }
}
