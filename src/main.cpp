#include "Classes/Map/Map.h"
#include "Classes/Battle/Battle.h"

#include <mutex>

std::mutex mutex;

bool canMove = true;        // signals whether the player can move
bool keepMoving = true;     // signals whether the NPC can move

void turn(Map &map, Trainer &t, int index) {
    auto engage = [&map, &t, &index] {
        mutex.lock();
        keepMoving = false;
        canMove = false;

        map[index].moveToPlayer(map, t);
        t.face(&map[index]);

        map.print(t);

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        Battle(&t, &map[index]);
        map.print(t);

        keepMoving = true;
        canMove = true;
        mutex.unlock();
    };

    while (keepMoving) {
        switch (generateInteger(1, 6)) {
            case 1:
                map[index].face(&map[index]);
                map.print(t);

                if (map[index].hasVisionOf(&t) and map[index]) {
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
                map.print(t);

                if (map[index].hasVisionOf(&t) and map[index]) {
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

int main() {
    SetConsoleTitleA("Pokemon Game");
    ShowConsoleCursor(false);

    Trainer_1.setRestoreItems({ new Potion(5), new Ether(5) });
    Trainer_1.setStatusItems({ new ParalyzeHeal(5), new BurnHeal(5), new IceHeal(5), new Antidote(5), new Awakening(5) });
    Trainer_1.setPokeBalls({ new PokeBall(5), new GreatBall(5), new UltraBall(5) });
    Trainer_1.setBattleItems({ new XAttack(5), new XSpeed(5) });

    Route_1.setObstruction(1, 2);
    Route_1.setObstruction(1, 3);
    Route_1.setObstruction(5, 5);
    Route_1.setObstruction(4, 5);
    Route_1.setObstruction(3, 5);

    Map * maps[] = { &Route_1, &Route_2, &Route_3 };
    Map * currentMap = maps[0];

    auto engage = [&currentMap](int index) {
        mutex.lock();
        keepMoving = false;

        (*currentMap)[index].moveToPlayer(*currentMap, Trainer_1);
        Trainer_1.face(&(*currentMap)[index]);
        currentMap->print(Trainer_1);

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        Battle(&Trainer_1, &(*currentMap)[index]);
        currentMap->print(Trainer_1);

        mutex.unlock();
    };

updateMap:
    currentMap->print(Trainer_1);

    keepMoving = true;
    const int numNPCs = currentMap->numNPCs();

    // create threads for each NPC to check if the player is in sight/ turn the NPC
    std::thread threads[numNPCs];
    for (int i = 0; i < numNPCs; ++i) {
        threads[i] = std::thread(turn, std::ref(*currentMap), std::ref(Trainer_1), i);
    }

    while (true) {
        // only be able to input moves if not engaged in a battle
        if (not canMove) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            continue;
        }

        // checks if the player is in line of sight of any NPC
        for (int i = 0; i < numNPCs; ++i) {
            if ((*currentMap)[i].hasVisionOf(&Trainer_1) and (*currentMap)[i]) {
                engage(i);
            }
        }

retry:
        const char input = static_cast<char>(getch());

        // ultimately, pauses execution of the main thread if the player is spotted
        if (not canMove) {
            continue;
        }

        switch (input) {
            case 'w':
                if (not Trainer_1.isFacingNorth()) {
                    Trainer_1.faceNorth();
                    currentMap->print(Trainer_1);
                }
                else if (not currentMap->isObstructionHere(Trainer_1.getX(), Trainer_1.getY() - 1)) {
                    Trainer_1.moveNorth();
                    currentMap->print(Trainer_1);
                }
                break;

            case 'a':
                if (not Trainer_1.isFacingWest()) {
                    Trainer_1.faceWest();
                    currentMap->print(Trainer_1);
                }
                else if (not currentMap->isObstructionHere(Trainer_1.getX() - 1, Trainer_1.getY())) {
                    Trainer_1.moveWest();
                    currentMap->print(Trainer_1);
                }
                break;

            case 's':
                if (not Trainer_1.isFacingSouth()) {
                    Trainer_1.faceSouth();
                    currentMap->print(Trainer_1);
                }
                else if (not currentMap->isObstructionHere(Trainer_1.getX(), Trainer_1.getY() + 1)) {
                    Trainer_1.moveSouth();
                    currentMap->print(Trainer_1);
                }
                break;

            case 'd':
                if (not Trainer_1.isFacingEast()) {
                    Trainer_1.faceEast();
                    currentMap->print(Trainer_1);
                }
                else if (not currentMap->isObstructionHere(Trainer_1.getX() + 1, Trainer_1.getY())) {
                    Trainer_1.moveEast();
                    currentMap->print(Trainer_1);
                }
                break;

            // interact
            case keys::ENTER:
                for (int i = 0; i < numNPCs; ++i) {
                    if (Trainer_1.hasVisionOf(&(*currentMap)[i]) and not (*currentMap)[i].hasVisionOf(&Trainer_1)) {
                        (*currentMap)[i].face(&Trainer_1);
                        currentMap->print(Trainer_1);

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
                return 0;

            default:
                goto retry;
        }

        // the values of mapData are the new x, new y, and new map respectively
        const std::array<int, 3> mapData = currentMap->isExitPointHere(Trainer_1.getX(), Trainer_1.getY());
        if (mapData[2] != -1) {
            keepMoving = false;

            // detach all threads of the NPCs
            for (std::thread &thread : threads) {
                thread.join();
            }

            // set the player's new coordinates
            Trainer_1.setCoordinates(mapData[0], mapData[1]);

            currentMap = maps[mapData[2]];
            goto updateMap;
        }
    }
}
