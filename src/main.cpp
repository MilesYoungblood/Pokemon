#include "Functions/CoreFunctions.h"
#include "Classes/Map/Map.h"

bool canMove = true;
bool keepMoving = true;

void turn(Map &map, Trainer &t, int index) {
    while (keepMoving) {
        if (generateInteger(1, 3) == 1) {
            map[index].face(&map[index]);
            map.print(t);

            if (map[index].hasVisionOf(&t) and not map[index].isDefeated()) {
                keepMoving = false;
                canMove = false;

                map[index].moveToPlayer(map, t);
                t.face(&map[index]);

                map.print(t);

                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                engageBattle(t, &map[index], false);
                map.print(t);

                keepMoving = true;
                canMove = true;
                return;
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        else {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
}

#include "Data/Data.h"

int main() {
    ShowConsoleCursor(false);

    Trainer_1.setItems({{ new Potion(5), new Ether(5) }, { new ParalyzeHeal(2) }, {}, {}});

    Route_1.setObstruction(1, 2);
    Route_1.setObstruction(1, 3);
    Route_1.setObstruction(5, 5);
    Route_1.setObstruction(4, 5);
    Route_1.setObstruction(3, 5);

    Map * maps[] = { &Route_1, &Route_2, &Route_3 };
    Map * currentMap = maps[0];

    recreate:
    const int numNPCs = (*currentMap).numNPCs();
    (*currentMap).print(Trainer_1);

    // keepMoving is true if at least one NPC is not defeated
    keepMoving = false;
    for (int i = 0; i < numNPCs; ++i) {
        if (not (*currentMap)[i].isDefeated()) {
            keepMoving = true;
        }
    }

    // create threads for each NPC to check if the player is in sight/ turn the NPC
    std::thread threads[numNPCs];
    for (int i = 0; i < numNPCs; ++i) {
        threads[i] = std::thread(turn, std::ref(*currentMap), std::ref(Trainer_1), i);
    }

    while (true) {
        // only be able to input moves if not engaged in a battle
        if (not canMove) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            continue;
        }

        // checks if the player leaves this map
        const std::pair<std::pair<int, int>, int> mapData = (*currentMap).isExitPointHere(Trainer_1.getX(), Trainer_1.getY());
        if (mapData.second != -1) {
            keepMoving = false;

            // detach all threads of the NPCs
            for (std::thread &thread : threads) {
                thread.join();
            }

            // set the player's new coordinates
            Trainer_1.setCoordinates(mapData.first.first, mapData.first.second);

            currentMap = maps[mapData.second];
            goto recreate;
        }

        // checks if the player is in line of sight of any NPC
        for (int i = 0; i < numNPCs; ++i) {
            if ((*currentMap)[i].hasVisionOf(&Trainer_1) and not (*currentMap)[i].isDefeated()) {
                keepMoving = false;

                (*currentMap)[i].moveToPlayer(*currentMap, Trainer_1);
                Trainer_1.face(&(*currentMap)[i]);
                (*currentMap).print(Trainer_1);

                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                engageBattle(Trainer_1, &(*currentMap)[i], false);
                (*currentMap).print(Trainer_1);
            }
        }

        retry:
        const char decision = static_cast<char>(getch());

        // ultimately, pauses execution of the main thread if the trainer is spotted
        if (not canMove) {
            continue;
        }

        switch (decision) {
            case 'w':
                if (not Trainer_1.isFacingNorth()) {
                    Trainer_1.faceNorth();
                    (*currentMap).print(Trainer_1);
                }
                else if (not (*currentMap).isObstructionHere(Trainer_1.getX(), Trainer_1.getY() - 1)) {
                    Trainer_1.moveNorth();
                    (*currentMap).print(Trainer_1);
                }
                break;

            case 'a':
                if (not Trainer_1.isFacingWest()) {
                    Trainer_1.faceWest();
                    (*currentMap).print(Trainer_1);
                }
                else if (not (*currentMap).isObstructionHere(Trainer_1.getX() - 1, Trainer_1.getY())) {
                    Trainer_1.moveWest();
                    (*currentMap).print(Trainer_1);
                }
                break;

            case 's':
                if (not Trainer_1.isFacingSouth()) {
                    Trainer_1.faceSouth();
                    (*currentMap).print(Trainer_1);
                }
                else if (not (*currentMap).isObstructionHere(Trainer_1.getX(), Trainer_1.getY() + 1)) {
                    Trainer_1.moveSouth();
                    (*currentMap).print(Trainer_1);
                }
                break;

            case 'd':
                if (not Trainer_1.isFacingEast()) {
                    Trainer_1.faceEast();
                    (*currentMap).print(Trainer_1);
                }
                else if (not (*currentMap).isObstructionHere(Trainer_1.getX() + 1, Trainer_1.getY())) {
                    Trainer_1.moveEast();
                    (*currentMap).print(Trainer_1);
                }
                break;

            // interact
            case keys::ENTER:
                for (int i = 0; i < numNPCs; ++i) {
                    if (Trainer_1.hasVisionOf(&(*currentMap)[i]) and not (*currentMap)[i].hasVisionOf(&Trainer_1)) {
                        (*currentMap)[i].face(&Trainer_1);
                        (*currentMap).print(Trainer_1);

                        if (not (*currentMap)[i].isDefeated()) {
                            keepMoving = false;

                            (*currentMap)[i].moveToPlayer(*currentMap, Trainer_1);
                            Trainer_1.face(&(*currentMap)[i]);
                            (*currentMap).print(Trainer_1);

                            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                            engageBattle(Trainer_1, &(*currentMap)[i], false);
                            (*currentMap).print(Trainer_1);
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
    }
}
