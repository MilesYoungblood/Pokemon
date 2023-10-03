#include "Classes/Map/Map.h"
#include "Classes/Battle/Battle.h"
#include "Classes/Game/Game.h"

#include <mutex>
#include <fstream>

std::mutex mutex;

bool canMove = true;        // signals whether the player can move
bool keepMoving = true;     // signals whether the NPC can move

void turn(Map &map, Player *t, int index) {
    auto engage = [&map, &t, &index] {
        mutex.lock();
        keepMoving = false;
        canMove = false;

        map[index].moveToPlayer(map, *t);
        t->face(&map[index]);

        map.print(*t);

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        Battle(t, &map[index]);
        map.print(*t);

        keepMoving = true;
        canMove = true;
        mutex.unlock();
    };

    while (keepMoving) {
        switch (generateInteger(1, 6)) {
            case 1:
                map[index].face(&map[index]);
                map.print(*t);

                if (map[index].hasVisionOf(t) and map[index]) {
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
                map.print(*t);

                if (map[index].hasVisionOf(t) and map[index]) {
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

const char * saveFilePath = R"(C:\Users\Miles\Documents\GitHub\PokemonBattle\src\Data\SaveData.txt)";

int main() {
    SetConsoleTitleA("Pokemon Game");
    ShowConsoleCursor(false);

    Player * player = Player::getPlayer(1, 1);

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

    Map * maps[] = { &Route_1, &Route_2, &Route_3 };

    auto saveData = [&player, &maps, &currentMapIndex] {
        std::ofstream saveFile(saveFilePath);
        if (not saveFile) {
            throw std::runtime_error("Could not open file");
        }

        saveFile << currentMapIndex << '\n';
        saveFile << player->getX() << ' ' << player->getY() << '\n';

        //TODO save player's direction and model as well

        for (int i = 0; i < sizeof maps / sizeof maps[0]; ++i) {
            for (int j = 0; j < maps[i]->numNPCs(); ++i) {
                saveFile << i << ' ' << j << ' ' << (*maps)[i][j].canFight() << '\n';
            }
        }

        saveFile.close();
    };

    auto loadData = [&player, &currentMapIndex, &maps] {
        std::ifstream saveFile(saveFilePath);
        if (saveFile) {
            int currentMap;
            int x;
            int y;

            saveFile >> currentMap >> x >> y;

            currentMapIndex = currentMap;
            player->setCoordinates(x, y);

            // TODO load player's direction and model as well

            while (not saveFile.eof()) {
                int mapSpot;
                int npcSpot;
                bool canFight;

                saveFile >> mapSpot >> npcSpot >> canFight;
                (*maps)[mapSpot][npcSpot].setBattleStatus(canFight);
            }

            saveFile.close();
        }
    };

    auto resetData = [] {
        std::remove(saveFilePath);
    };

    loadData();
    Map * currentMap = maps[currentMapIndex];

    auto engage = [&player, &currentMap](int index) {
        mutex.lock();
        keepMoving = false;

        (*currentMap)[index].moveToPlayer(*currentMap, *player);
        player->face(&(*currentMap)[index]);
        currentMap->print(*player);

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
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
        threads[i] = std::thread(turn, std::ref(*currentMap), std::ref(player), i);
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

retry:
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
                std::cout << "Press 1 to quit,\n"
                          << "Press 2 to return";

                int option;
                option = getInt(1, 2);

                if (option == 1) {
                    system("cls");
                    printMessage("Do you want to save?\n");
                    std::cout << "Press 1 to save,\n"
                              << "Press 2 to not save,\n"
                              << "Press 3 to reset save data";

                    option = getInt(1, 3);
                    if (option == 1) {
                        saveData();
                    }
                    else if (option == 3) {
                        resetData();
                    }
                }
                else {
                    goto renderMap;
                }

                Player::destroyPlayer();

                return 0;

            default:
                goto retry;
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
