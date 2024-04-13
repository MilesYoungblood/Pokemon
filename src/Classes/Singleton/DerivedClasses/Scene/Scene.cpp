//
// Created by Miles on 3/16/2024.
//

#include "../Game/Game.h"
#include "../KeyManager/KeyManager.h"
#include "Scene.h"

bool Scene::waitEvent() {
    if (SDL_WaitEvent(&this->event) == 0) {
        std::clog << "Error processing event: " << SDL_GetError() << '\n';
        Game::getInstance().terminate();
        return false;
    }
    return true;
}

SDL_EventType Scene::getEventType() const {
    return static_cast<SDL_EventType>(this->event.type);
}

void Scene::pushEvent() {
    SDL_Event commonEvent;
    if (SDL_PushEvent(&commonEvent) < 0) {
        std::clog << "Error pushing event: " << SDL_GetError() << '\n';
        Game::getInstance().terminate();
    }
}

void Scene::handleEvents() {
    if (SDL_PollEvent(&this->event) == 1) {
        KeyManager::getInstance().update();
        if (event.type == SDL_EventType::SDL_QUIT) {
            Game::getInstance().terminate();
        }
    }
}
