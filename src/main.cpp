#include "Classes/Map/Map.h"
#include "Classes/Battle/Battle.h"
#include "Classes/Game/Game.h"

#include <mutex>
#include <fstream>

std::mutex mutex;

bool canMove = true;        // signals whether the player can move
bool keepMoving = true;     // signals whether the NPC can move

void turn(Player *player, Map &map, int index) {
    auto engage = [&player, &map, &index] {
        mutex.lock();
        keepMoving = false;
        canMove = false;

        map[index].moveToPlayer(map, *player);
        player->face(&map[index]);

        map.print(*player);

        printMessage("\n\nOur eyes met! You know what this means right?");
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));

        Battle(player, &map[index]);
        map.print(*player);

        keepMoving = true;
        canMove = true;
        mutex.unlock();
    };

    while (keepMoving) {
        switch (generateInteger(1, 6)) {
            case 1:
                map[index].face(&map[index]);
                map.print(*player);

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
                map.print(*player);

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

// for me to work between my laptop and desktop
static bool desktop = false;

const char *saveFilePath = desktop ?
        R"(C:\Users\Miles\Documents\GitHub\PokemonBattle\src\Data\SaveData.txt)" :
        R"(C:\Users\Miles Youngblood\OneDrive\Documents\GitHub\PokemonBattle\src\Data\SaveData.txt)";

void saveData(Player *player, Map *maps[], int numMaps, int &currentMapIndex) {
    std::ofstream saveFile(saveFilePath);
    if (not saveFile) {
        throw std::runtime_error("Could not open file");
    }

    auto saveDirection = [&saveFile](Entity *entity) {
        if (entity->isFacingNorth()) {
            saveFile << 0;
        }
        else if (entity->isFacingEast()) {
            saveFile << 1;
        }
        else if (entity->isFacingSouth()) {
            saveFile << 2;
        }
        else if (entity->isFacingWest()){
            saveFile << 3;
        }
    };

    saveFile << currentMapIndex << '\n';
    saveFile << player->getX() << ' ' << player->getY() << ' ';
    saveDirection(player);

    for (int i = 0; i < numMaps; ++i) {
        for (int j = 0; j < maps[i]->numNPCs(); ++i) {
            saveFile << '\n' << i << ' ' << j << ' ' << (*maps)[i][j].canFight() << ' ';
            saveDirection(&(*maps)[i][j]);
        }
    }

    saveFile.close();
}

void loadData(Player *player, Map *maps[], int &currentMapIndex) {
    std::ifstream saveFile(saveFilePath);

    auto loadDirection = [&saveFile](Entity *entity) {
        int direction;
        saveFile >> direction;

        switch (direction) {
            case 0:
                entity->faceNorth();
                break;

            case 1:
                entity->faceEast();
                break;

            case 2:
                entity->faceSouth();
                break;

            case 3:
                entity->faceWest();
                break;

            default:
                throw std::runtime_error("Unexpected error: lambda loadDirection");
        }
    };

    if (saveFile) {
        int currentMap;
        int x;
        int y;

        saveFile >> currentMap >> x >> y;

        currentMapIndex = currentMap;
        player->setCoordinates(x, y);
        loadDirection(player);

        while (not saveFile.eof()) {
            int mapSpot;
            int npcSpot;
            bool canFight;

            saveFile >> mapSpot >> npcSpot >> canFight;
            (*maps)[mapSpot][npcSpot].setBattleStatus(canFight);
            loadDirection(&(*maps)[mapSpot][npcSpot]);
        }

        saveFile.close();
    }
}

void eraseData() {
    std::remove(saveFilePath);
}

#include "Data/Data.h"

int main() {
    SetConsoleTitleA("Pokemon Game");
    ShowConsoleCursor(false);

    Player *player = Player::getPlayer(1, 1);

    player->addPokemon(new Greninja({ new WaterShuriken, new DarkPulse, new IceBeam, new Extrasensory }));
    player->addPokemon(new Charizard({ new Flamethrower, new AirSlash, new DragonPulse, new SolarBeam }));
    player->addPokemon(new Hydreigon({ new DarkPulse, new DragonPulse, new Flamethrower, new FocusBlast }));

    player->setRestoreItems({ new Potion(5), new SuperPotion(5), new HyperPotion(5), new Ether(5) });
    player->setStatusItems({ new ParalyzeHeal(5), new BurnHeal(5), new IceHeal(5), new Antidote(5), new Awakening(5) });
    player->setPokeBalls({ new PokeBall(5), new GreatBall(5), new UltraBall(5) });
    player->setBattleItems({ new XAttack(5), new XSpeed(5) });

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
        mutex.lock();
        keepMoving = false;

        (*currentMap)[index].moveToPlayer(*currentMap, *player);
        player->face(&(*currentMap)[index]);
        currentMap->print(*player);

        printMessage("\n\nOur eyes met! You know what this means right?");
        std::cin.ignore();

        Battle(player, &(*currentMap)[index]);
        currentMap->print(*player);

        mutex.unlock();
    };

renderMap:
    currentMap->print(*player);

    keepMoving = true;
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
                    currentMap->print(*player);
                }
                else if (not currentMap->isObstructionHere(player->getX(), player->getY() - 1)) {
                    player->moveNorth();
                    currentMap->print(*player);
                }
                break;

            case 'a':
                if (not player->isFacingWest()) {
                    player->faceWest();
                    currentMap->print(*player);
                }
                else if (not currentMap->isObstructionHere(player->getX() - 1, player->getY())) {
                    player->moveWest();
                    currentMap->print(*player);
                }
                break;

            case 's':
                if (not player->isFacingSouth()) {
                    player->faceSouth();
                    currentMap->print(*player);
                }
                else if (not currentMap->isObstructionHere(player->getX(), player->getY() + 1)) {
                    player->moveSouth();
                    currentMap->print(*player);
                }
                break;

            case 'd':
                if (not player->isFacingEast()) {
                    player->faceEast();
                    currentMap->print(*player);
                }
                else if (not currentMap->isObstructionHere(player->getX() + 1, player->getY())) {
                    player->moveEast();
                    currentMap->print(*player);
                }
                break;

            // interact
            case keys::ENTER:
                for (int i = 0; i < numNPCs; ++i) {
                    if (player->hasVisionOf(&(*currentMap)[i]) and not (*currentMap)[i].hasVisionOf(player)) {
                        (*currentMap)[i].face(player);
                        currentMap->print(*player);

                        if ((*currentMap)[i]) {
                            engage(i);
                        }
                        break;
                    }
                }
                break;

            case keys::ESC:
                keepMoving = false;
                // detach all threads of the NPCs
                for (std::thread &thread : threads) {
                    thread.join();
                }

                system("cls");
                printMessage("Do you want to quit?\n");
                std::cout << "\tPress 1 to quit,\n"
                          << "\tPress 2 to return";

                int option;
                option = getInt(1, 2);

                if (option == 1) {
                    system("cls");
                    printMessage("Do you want to save?\n");
                    std::cout << "\tPress 1 to save,\n"
                              << "\tPress 2 to not save,\n"
                              << "\tPress 3 to reset save data";

                    option = getInt(1, 3);
                    if (option == 1) {
                        saveData(player, maps, sizeof maps / sizeof maps[0], currentMapIndex);
                    }
                    else if (option == 3) {
                        eraseData();
                    }
                }
                else {
                    goto renderMap;
                }

                Player::destroyPlayer();

                return 0;

            default:
                goto getInput;
        }

        // the values of mapData are the new x, new y, and new map respectively
        const std::array<int, 3> mapData = currentMap->isExitPointHere(player->getX(), player->getY());
        if (mapData[2] != -1) {
            keepMoving = false;

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
