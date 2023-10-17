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
    SetConsoleTitleA("Pokémon");
    ShowConsoleCursor(false);

    Player *player = Player::getPlayer();

    player->setRestoreItems({ new Potion(5), new SuperPotion(5), new HyperPotion(5), new Ether(5) });
    player->setStatusItems({ new ParalyzeHeal(5), new BurnHeal(5), new IceHeal(5), new Antidote(5), new Awakening(5) });
    player->setPokeBalls({ new PokeBall(5), new GreatBall(5), new UltraBall(5), new MasterBall(1) });
    player->setBattleItems({ new XAttack(5), new XDefense(5), new XSpAttack(5), new XSpDefense(5), new XSpeed(5), new XAccuracy(5) });

    Route_1.setObstruction(1, 2);
    Route_1.setObstruction(1, 3);
    Route_1.setObstruction(5, 5);
    Route_1.setObstruction(4, 5);
    Route_1.setObstruction(3, 5);

    int currentMapIndex = 0;

    Map *maps[] = { &Route_1, &Route_2, &Route_3 };

    loadData(player, maps, currentMapIndex);
    Map *currentMap = maps[currentMapIndex];

    auto engage = [&player, &currentMap](int index) {
        m.lock();
        threadsPaused = true;
        m.unlock();

        (*currentMap)[index].moveToPlayer(*currentMap, player);
        player->face(&(*currentMap)[index]);
        currentMap->print(player);

        printMessage("\n\nI challenge you to a Pokémon battle!");
        pressEnter();

        Battle(player, &(*currentMap)[index]);

        currentMap->print(player);

        m.lock();
        threadsPaused = false;
        m.unlock();
    };

renderMap:
    currentMap->print(player);

    stopThreads = false;
    const int numNPCs = currentMap->numNPCs();

    // create threads for each NPC to check if the player is in sight/ turn the NPC
    std::thread threads[numNPCs];
    for (int i = 0; i < numNPCs; ++i) {
        threads[i] = std::thread(turn, player, std::ref(*currentMap), i);
    }

    while (true) {
        // only be able to input moves if not engaged in a battle
        if (not canMove) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            continue;
        }

        // checks if the player is in LoS for any NPC
        for (int i = 0; i < numNPCs; ++i) {
            if ((*currentMap)[i].hasVisionOf(player) and (*currentMap)[i]) {
                engage(i);
            }
        }

getInput:
        const char input = static_cast<char>(_getch());

        // ultimately, pauses execution of the main thread if the player is spotted
        if (not canMove) {
            continue;
        }

        switch (input) {
            case 'w':
                if (not player->isFacingNorth()) {
                    player->faceNorth();
                    currentMap->print(player);
                }
                else if (not currentMap->isObstructionHere(player->getX(), player->getY() - 1)) {
                    player->moveNorth();
                    currentMap->print(player);
                }
                break;

            case 'a':
                if (not player->isFacingWest()) {
                    player->faceWest();
                    currentMap->print(player);
                }
                else if (not currentMap->isObstructionHere(player->getX() - 1, player->getY())) {
                    player->moveWest();
                    currentMap->print(player);
                }
                break;

            case 's':
                if (not player->isFacingSouth()) {
                    player->faceSouth();
                    currentMap->print(player);
                }
                else if (not currentMap->isObstructionHere(player->getX(), player->getY() + 1)) {
                    player->moveSouth();
                    currentMap->print(player);
                }
                break;

            case 'd':
                if (not player->isFacingEast()) {
                    player->faceEast();
                    currentMap->print(player);
                }
                else if (not currentMap->isObstructionHere(player->getX() + 1, player->getY())) {
                    player->moveEast();
                    currentMap->print(player);
                }
                break;

            // interact
            case Keys::ENTER:
                for (int i = 0; i < numNPCs; ++i) {
                    if (player->hasVisionOf(&(*currentMap)[i]) and not (*currentMap)[i].hasVisionOf(player)) {
                        (*currentMap)[i].face(player);
                        currentMap->print(player);

                        if ((*currentMap)[i]) {
                            engage(i);
                        }
                        break;
                    }
                }
                break;

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
        }

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
