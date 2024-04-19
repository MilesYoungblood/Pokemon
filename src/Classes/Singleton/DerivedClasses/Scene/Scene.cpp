//
// Created by Miles on 3/16/2024.
//

#include "../Game/Game.h"
#include "../KeyManager/KeyManager.h"
#include "Scene.h"

void Scene::setState(const State x) {
    this->currentState = x;
}

bool Scene::getState(const State x) const {
    return this->currentState == x;
}

void Scene::pushEvent() {
    SDL_Event commonEvent;
    SDL_memset(&commonEvent, 0, sizeof(commonEvent));

    commonEvent.type = SDL_USEREVENT;
    commonEvent.user.code = 1;
    commonEvent.user.data1 = nullptr;
    commonEvent.user.data2 = nullptr;

    if (const int value = SDL_PushEvent(&commonEvent); value < 0) {
        std::clog << "Error pushing event: " << SDL_GetError() << '\n';
        Game::getInstance().terminate();
    }
}

void Scene::handleEvents() {
    if (SDL_PollEvent(&this->event) == 1) {
        KeyManager::getInstance().update();
        if (event.type == SDL_QUIT) {
            Game::getInstance().terminate();
        }
    }
}

bool Scene::pollEvent() {
    return SDL_PollEvent(&this->event) == 1;
}

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
