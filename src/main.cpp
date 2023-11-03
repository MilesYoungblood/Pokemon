#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"


#define SDL_MAIN_HANDLED

#include "Classes/Game/Game.h"

int main() {
    SDL_SetMainReady();

    Uint32 frameStart;
    Uint32 frameTime;
    Uint32 frameDelay;

    const Game game;

    while (game) {
        frameStart = SDL_GetTicks();

        Game::handleEvents();
        Game::update();
        Game::render();

        frameTime = SDL_GetTicks() - frameStart;
        frameDelay = 1000 / currentFps;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    return 0;
}


#pragma clang diagnostic pop
