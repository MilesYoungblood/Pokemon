#include "Classes/Singleton/DerivedClasses/Game/Game.h"

int main() {
    SDL_SetMainReady();

    Uint32 frameStart;
    Uint32 frameTime;
    Uint32 frameDelay;

    while (Game::getInstance().isRunning()) {
        frameStart = SDL_GetTicks64();

        Game::getInstance().handleEvents();
        Game::getInstance().update();
        Game::getInstance().render();

        frameTime = SDL_GetTicks64() - frameStart;
        frameDelay = 1000 / Game::getInstance().getFps();

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    return 0;
}
