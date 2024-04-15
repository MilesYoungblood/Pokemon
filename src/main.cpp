#include "Classes/Singleton/DerivedClasses/Game/Game.h"

int main() {
    SDL_SetMainReady();

    while (Game::getInstance().isRunning()) {
        const Uint32 frameStart = SDL_GetTicks64();

        Game::getInstance().handleEvents();
        Game::getInstance().update();
        Game::getInstance().render();

        const Uint32 frameTime = SDL_GetTicks64() - frameStart;

        if (const Uint32 frameDelay = 1000 / Game::getInstance().getFps(); frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    return 0;
}
