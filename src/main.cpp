#include <SDL.h>
#include <SDL_image.h>
#include <SDL_timer.h>

#include "Classes/Battle/Battle.h"
#include "Classes/Map/Map.h"
#include "Functions/GameFunctions.h"

#include <mutex>

std::mutex m;

bool canMove = true;            // signals when the player can move
bool threadsPaused = false;     // signals when to pause all threads
bool stopThreads = false;       // signals when to end all threads

void turn(Player *player, Map &map, int index) {
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

#include "Data/Data.h"
#include "Classes/Game/Game.h"

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

const int SCROLL_SPEED = 300;

int main(__attribute__((unused)) int argc, __attribute__((unused)) char *argv[]) {
    Game game;

    game.init("Pokemon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT);

    while (game.running()) {
        game.handleEvents();
        game.update();
        game.render();
    }

    game.clean();
    return 0;


    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL: " << SDL_GetError();
    }

    SDL_Window *window = SDL_CreateWindow("Pokemon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    if (not window) {
        std::cerr << "Error creating window: " << SDL_GetError();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (not renderer) {
        std::cerr << "Error creating renderer: " << SDL_GetError();
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Surface *surface = IMG_Load(R"(C:\Users\Miles\Documents\GitHub\PokemonBattle\pokeball.png)");
    if (not surface) {
        std::cerr << "Error creating surface: " << SDL_GetError();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (not texture) {
        std::cerr << "Error creating texture: " << SDL_GetError();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Rect dest;

    SDL_QueryTexture(texture, nullptr, nullptr, &dest.w, &dest.h);

    dest.w /= 20;
    dest.h /= 20;

    dest.x = (WINDOW_WIDTH - dest.w) / 2;

    double y_pos = WINDOW_HEIGHT;
    while (dest.y >= -dest.h) {
        SDL_RenderClear(renderer);

        dest.y = static_cast<int>(y_pos);

        SDL_RenderCopy(renderer, texture, nullptr, &dest);
        SDL_RenderPresent(renderer);

        y_pos -= static_cast<double>(SCROLL_SPEED / 60.0);

        SDL_Delay(1000 / 60);
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
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

        // checks if the player is in line of sight of any NPC
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
}
