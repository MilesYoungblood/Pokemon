#include "Functions/CoreFunctions.h"
#include "Classes/Map/Map.h"
#include <thread>

bool canMove = true;
bool keepTurning = true;

void turn(Map &map, Trainer &t, int index) {
    while (keepTurning) {
        if (generateInteger(1, 3) == 1) {
            map[index].face(&map[index]);
            map.print(t);

            if (map[index].hasVisionOf(&t) and not map[index].isDefeated()) {
                keepTurning = false;
                canMove = false;

                map[index].moveToPlayer(map, t);
                t.face(&map[index]);

                map.print(t);

                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                engageBattle(t, &map[index], false);
                map.print(t);

                keepTurning = true;
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

#include <conio.h>

enum Maps { ROUTE_1 = 0, ROUTE_2 = 1 };

int main() {

    int * o = nullptr;
    delete o;

    ShowConsoleCursor(false);

    Trainer_1[0].setMoves({ new WaterShuriken, new DarkPulse, new IceBeam, new Extrasensory });
    Trainer_1[1].setMoves({ new Flamethrower, new AirSlash, new DragonPulse, new SolarBeam });
    Trainer_1[2].setMoves({ new DarkPulse, new DragonPulse, new Flamethrower, new FocusBlast });

    Trainer_1.setItems({{ new Potion(5), new Ether(5) }, { new ParalyzeHeal(2) }, {}, {}});

    Map Route_2(21, 20, {}, { std::make_pair(std::make_pair(1, 0), Maps::ROUTE_1) });

    Map Route_1(12, 10, { NPC({ Pikachu, Lucario }, 6, 6, 3) }, { std::make_pair(std::make_pair(5, 0), Maps::ROUTE_2) });
    Route_1[0][0].setMoves({ new Thunder, new QuickAttack, new IronTail, new VoltTackle });
    Route_1[0][1].setMoves({ new AuraSphere, new FlashCannon, new DragonPulse, new DarkPulse });

    Route_1.setObstruction(1, 2);
    Route_1.setObstruction(1, 3);
    Route_1.setObstruction(5, 5);
    Route_1.setObstruction(4, 5);
    Route_1.setObstruction(3, 5);

    Map currentMap(Route_2);
    std::vector<Map*> maps = { &Route_1, &Route_2 };

    recreate:

    currentMap.print(Trainer_1);

    // create threads for each NPC to check if the player is in sight/ turn the NPC
    keepTurning = true;
    std::thread threads[currentMap.numNPCs()];
    for (int i = 0; i < currentMap.numNPCs(); ++i) {
        threads[i] = std::thread(turn, std::ref(currentMap), std::ref(Trainer_1), i);
    }

    while (true) {
        // only be able to input moves if not engaged in a battle
        if (not canMove) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            continue;
        }

        // checks if the player is in line of sight of any NPC
        for (int i = 0; i < currentMap.numNPCs(); ++i) {
            if (currentMap[i].hasVisionOf(&Trainer_1) and not currentMap[i].isDefeated()) {
                keepTurning = false;

                currentMap[i].moveToPlayer(currentMap, Trainer_1);
                Trainer_1.face(&currentMap[i]);
                currentMap.print(Trainer_1);

                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                engageBattle(Trainer_1, &currentMap[i], false);
                currentMap.print(Trainer_1);
            }
        }

        int mapIndex = currentMap.isExitPointHere(Trainer_1.getX(), Trainer_1.getY());
        if (mapIndex != -1) {
            //TODO will eventually change the map, reset the player's coordinates

            keepTurning = false;

            // detach all threads of the NPCs
            for (std::thread &thread : threads) {
                thread.detach();
            }
            Trainer_1.setCoordinates(1, 1);

            std::cout << maps[0] << '\n' << maps[1] << std::endl;

            std::cin.ignore();
            currentMap = *maps[mapIndex];
            goto recreate;
        }

        retry:
        char decision = static_cast<char>(getch());

        // ultimately, pauses execution of the main thread if the trainer is spotted
        if (not canMove) {
            continue;
        }

        switch (decision) {
            case 'w':
                if (not Trainer_1.isFacingNorth()) {
                    Trainer_1.faceNorth();
                    currentMap.print(Trainer_1);
                }
                else if (not currentMap.getTile(Trainer_1.getX(), Trainer_1.getY() - 1)) {
                    Trainer_1.moveNorth();
                    currentMap.print(Trainer_1);
                }
                break;

            case 'a':
                if (not Trainer_1.isFacingWest()) {
                    Trainer_1.faceWest();
                    currentMap.print(Trainer_1);
                }
                else if (not currentMap.getTile(Trainer_1.getX() - 1, Trainer_1.getY())) {
                    Trainer_1.moveWest();
                    currentMap.print(Trainer_1);
                }
                break;

            case 's':
                if (not Trainer_1.isFacingSouth()) {
                    Trainer_1.faceSouth();
                    currentMap.print(Trainer_1);
                }
                else if (not currentMap.getTile(Trainer_1.getX(), Trainer_1.getY() + 1)) {
                    Trainer_1.moveSouth();
                    currentMap.print(Trainer_1);
                }
                break;

            case 'd':
                if (not Trainer_1.isFacingEast()) {
                    Trainer_1.faceEast();
                    currentMap.print(Trainer_1);
                }
                else if (not currentMap.getTile(Trainer_1.getX() + 1, Trainer_1.getY())) {
                    Trainer_1.moveEast();
                    currentMap.print(Trainer_1);
                }
                break;

            // interact
            case keys::ENTER:
                for (int i = 0; i < currentMap.numNPCs(); ++i) {
                    if (Trainer_1.hasVisionOf(&currentMap[i]) and not currentMap[i].hasVisionOf(&Trainer_1)) {
                        currentMap[i].face(&Trainer_1);
                        currentMap.print(Trainer_1);

                        if (not currentMap[i].isDefeated()) {
                            keepTurning = false;

                            currentMap[i].moveToPlayer(currentMap, Trainer_1);
                            Trainer_1.face(&currentMap[i]);
                            currentMap.print(Trainer_1);

                            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                            engageBattle(Trainer_1, &currentMap[i], false);
                            currentMap.print(Trainer_1);
                        }
                        break;
                    }
                }
                break;

            case keys::ESC:
                // detach all threads of the NPCs
                for (std::thread &thread : threads) {
                    thread.detach();
                }
                return 0;

            default:
                goto retry;
        }
    }
}
