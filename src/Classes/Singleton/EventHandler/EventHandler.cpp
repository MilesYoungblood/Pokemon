//
// Created by miles on 4/19/2024.
//

#include "../Game/Game.h"
#include "EventHandler.h"

bool EventHandler::pollEvent() {
    return SDL_PollEvent(&this->event) == 1;
}

bool EventHandler::waitEvent() {
    if  (SDL_WaitEvent(&this->event) == 0) {
        std::clog << "Error processing event: " << SDL_GetError() << '\n';
        Game::getInstance().terminate();
        return false;
    }
    return true;
}

void EventHandler::pushEvent() {
    SDL_Event commonEvent;
    SDL_memset(&commonEvent, 0, sizeof(commonEvent));

    commonEvent.type = SDL_USEREVENT;
    commonEvent.user.code = 1;
    commonEvent.user.data1 = nullptr;
    commonEvent.user.data2 = nullptr;

    if (SDL_PushEvent(&commonEvent) < 0) {
        std::clog << "Error pushing event: " << SDL_GetError() << '\n';
        Game::getInstance().terminate();
    }
}

SDL_EventType EventHandler::getEventType() const {
    return static_cast<SDL_EventType>(this->event.type);
}
