#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"

#define SDL_MAIN_HANDLED

#include "Classes/Battle/Battle.h"
#include "Classes/Game/Game.h"

#include <mutex>

std::mutex m;

__attribute__((unused)) bool canMove = true;            // signals when the player can move
bool threadsPaused = false;     // signals when to pause all threads
bool stopThreads = false;       // signals when to end all threads

__attribute__((unused)) void turn(Player *player, Map &map, int index) {
    auto engage = [&player, &map, &index] {
        m.lock();
        threadsPaused = true;
        canMove = false;

        map[index].moveToPlayer(map, player);
        player->face(&map[index]);

        map.print(player);

        printMessage("\n\nI challenge you to a Pokemon battle!");
        pressEnter();

        Battle(player, &map[index]);
        map.print(player);

        threadsPaused = false;
        canMove = true;
        m.unlock();
    };

    while (not stopThreads) {
        if (threadsPaused) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            continue;
        }

        switch (generateInteger(1, 6)) {
            case 1:
                map[index].face(&map[index]);
                map.print(player);

                if (map[index].hasVisionOf(player) and map[index]) {
                    engage();
                    return;
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                break;

            case 2:
                if (map[index].isFacingNorth() or map[index].isFacingSouth()) {
                    coinFlip() ? map[index].faceEast() : map[index].faceWest();
                }
                else if (map[index].isFacingEast() or map[index].isFacingWest()) {
                    coinFlip() ? map[index].faceNorth() : map[index].faceSouth();
                }
                map.print(player);

                if (map[index].hasVisionOf(player) and map[index]) {
                    engage();
                    return;
                }

                std::this_thread::sleep_for(std::chrono::milliseconds(500));
                break;

            default:
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
}

int main() {
    SDL_SetMainReady();

    const int FPS = 30;                     // Pokémon runs at 30 fps in overworld, and 60 fps during battles
    const int frameDelay = 1000 / FPS;

    Uint32 frameStart;
    Uint32 frameTime;

    Game game;

    // game loop
    while (game) {
        frameStart = SDL_GetTicks();

        Game::handleEvents();
        Game::update();
        Game::render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }

    Game::clean();
    return 0;
}


#pragma clang diagnostic pop

    /*
    SetConsoleTitleA("Pokemon");
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

        printMessage("\n\nI challenge you to a Pokemon battle!");
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
