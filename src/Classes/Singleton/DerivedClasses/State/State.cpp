//
// Created by Miles on 3/16/2024.
//

#include "../Game/Game.h"
#include "State.h"

void State::handleEvents() {
    static SDL_Event event;
    if (SDL_PollEvent(&event) == 1 and event.type == SDL_EventType::SDL_QUIT) {
        Game::getInstance().terminate();
    }
}
