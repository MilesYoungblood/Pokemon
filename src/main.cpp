#include "Singleton/Game/Game.h"

int main() {
    SDL_SetMainReady();

    while (Game::getInstance().isRunning()) {
        const Uint64 frameStart = SDL_GetTicks64();

        Game::getInstance().handleEvents();
        Game::getInstance().update();
        Game::getInstance().render();

        const Uint64 frameTime = SDL_GetTicks64() - frameStart;

        if (const Uint64 frameDelay = 1000 / Game::getInstance().getFps(); frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    return 0;
}
