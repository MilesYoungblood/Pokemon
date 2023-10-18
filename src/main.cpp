#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"

#define SDL_MAIN_HANDLED

#include "Classes/Game/Game.h"

constexpr int FPS = 30;
constexpr int FRAME_DELAY = 1000 / FPS;

int main() {
    SDL_SetMainReady();

    Uint32 frameStart;
    Uint32 frameTime;

    Game game;

    while (game) {
        frameStart = SDL_GetTicks();

        Game::handleEvents();
        Game::update();
        Game::render();

        frameTime = SDL_GetTicks() - frameStart;

        if (FRAME_DELAY > frameTime) {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }

    return 0;
}


#pragma clang diagnostic pop

    /*
    player->setRestoreItems({ new Potion(5), new SuperPotion(5), new HyperPotion(5), new Ether(5) });
    player->setStatusItems({ new ParalyzeHeal(5), new BurnHeal(5), new IceHeal(5), new Antidote(5), new Awakening(5) });
    player->setPokeBalls({ new PokeBall(5), new GreatBall(5), new UltraBall(5), new MasterBall(1) });
    player->setBattleItems({ new XAttack(5), new XDefense(5), new XSpAttack(5), new XSpDefense(5), new XSpeed(5), new XAccuracy(5) });

    Route_1.setObstruction(1, 2);
    Route_1.setObstruction(1, 3);
    Route_1.setObstruction(5, 5);
    Route_1.setObstruction(4, 5);
    Route_1.setObstruction(3, 5);

        case Keys::ESC:
            threadsPaused = true;

            if (openMenu(player, maps, sizeof maps / sizeof maps[0], currentMapIndex)) {
                stopThreads = true;
                // detach all threads of the NPCs
                for (std::thread &thread : threads) {
                    thread.detach();
                }

                Player::destroyPlayer();
                return 0;
            }
            threadsPaused = false;

            goto renderMap;

        default:
            goto getInput;

        // the values of mapData are the new x, new y, and new map respectively
        const std::array<int, 3> mapData = currentMap->isExitPointHere(player->getX(), player->getY());
        if (mapData[2] != -1) {
            stopThreads = true;

            // detach all threads of the NPCs
            for (std::thread &thread : threads) {
                thread.join();
            }

            // set the player's new coordinates
            player->setCoordinates(mapData[0], mapData[1]);

            currentMapIndex = mapData[2];
            currentMap = maps[currentMapIndex];
            goto renderMap;
        }
    }
    */
