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

                Sleep(2000);
                engageBattle(t, &map[index], false);
                map.print(t);

                keepTurning = true;
                canMove = true;
                return;
            }
        }
        else {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
}

#include "Data/Data.h"

int main() {
    ShowConsoleCursor(false);

    Trainer_1[0].setMoves({ new WaterShuriken, new DarkPulse, new IceBeam, new Extrasensory });
    Trainer_1[1].setMoves({ new Flamethrower, new AirSlash, new DragonPulse, new SolarBeam });
    Trainer_1[2].setMoves({ new DarkPulse, new DragonPulse, new Flamethrower, new FocusBlast });

    Trainer_1.setItems({{ new Potion(5), new Ether(5) }, { new ParalyzeHeal(2) }, {}, {}});

    Map Route_1(12, 10, { NPC({ Pikachu, Lucario }, 6, 6, 3) });
    Route_1[0][0].setMoves({ new Thunder, new QuickAttack, new IronTail, new VoltTackle });
    Route_1[0][1].setMoves({ new AuraSphere, new FlashCannon, new DragonPulse, new DarkPulse });

    Route_1.setObstruction(1, 2);
    Route_1.setObstruction(1, 3);
    Route_1.setObstruction(5, 5);
    Route_1.setObstruction(4, 5);
    Route_1.setObstruction(3, 5);

    Route_1.print(Trainer_1);

    // create threads for each NPC to check if the player is in sight/ turn the NPC
    std::thread threads[Route_1.numNPCs()];
    for (int i = 0; i < sizeof threads / sizeof threads[0]; ++i) {
        threads[i] = std::thread(turn, std::ref(Route_1), std::ref(Trainer_1), i);
    }

    while (true) {
        // only be able to input moves if not engaged in a battle
        if (not canMove) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            continue;
        }

        // checks if the player is in line of sight of any NPC
        for (int i = 0; i < Route_1.numNPCs(); ++i) {
            if (Route_1[i].hasVisionOf(&Trainer_1) and not Route_1[i].isDefeated()) {
                keepTurning = false;

                Route_1[i].moveToPlayer(Route_1, Trainer_1);
                Trainer_1.face(&Route_1[i]);
                Route_1.print(Trainer_1);

                std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                engageBattle(Trainer_1, &Route_1[i], false);
                Route_1.print(Trainer_1);
            }
        }

        switch (static_cast<char>(getch())) {
            case 'w':
                if (not Trainer_1.isFacingNorth()) {
                    Trainer_1.faceNorth();
                    Route_1.print(Trainer_1);
                }
                else if (not Route_1.getTile(Trainer_1.getX(), Trainer_1.getY() - 1)) {
                    Trainer_1.moveNorth();
                    Route_1.print(Trainer_1);
                }
                break;

            case 'a':
                if (not Trainer_1.isFacingWest()) {
                    Trainer_1.faceWest();
                    Route_1.print(Trainer_1);
                }
                else if (not Route_1.getTile(Trainer_1.getX() - 1, Trainer_1.getY())) {
                    Trainer_1.moveWest();
                    Route_1.print(Trainer_1);
                }
                break;

            case 's':
                if (not Trainer_1.isFacingSouth()) {
                    Trainer_1.faceSouth();
                    Route_1.print(Trainer_1);
                }
                else if (not Route_1.getTile(Trainer_1.getX(), Trainer_1.getY() + 1)) {
                    Trainer_1.moveSouth();
                    Route_1.print(Trainer_1);
                }
                break;

            case 'd':
                if (not Trainer_1.isFacingEast()) {
                    Trainer_1.faceEast();
                    Route_1.print(Trainer_1);
                }
                else if (not Route_1.getTile(Trainer_1.getX() + 1, Trainer_1.getY())) {
                    Trainer_1.moveEast();
                    Route_1.print(Trainer_1);
                }
                break;

            // interact
            case keys::ENTER:
                for (int i = 0 ; i < Route_1.numNPCs(); ++i) {
                    if (Trainer_1.hasVisionOf(&Route_1[i]) and not Route_1[i].hasVisionOf(&Trainer_1)) {
                        Route_1[i].face(&Trainer_1);
                        Route_1.print(Trainer_1);

                        if (not Route_1[i].isDefeated()) {
                            keepTurning = false;

                            Route_1[i].moveToPlayer(Route_1, Trainer_1);
                            Trainer_1.face(&Route_1[i]);
                            Route_1.print(Trainer_1);

                            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
                            engageBattle(Trainer_1, &Route_1[i], false);
                            Route_1.print(Trainer_1);
                        }
                        break;
                    }
                }
                break;

            case keys::ESC:
                // detach all threads of the NPCs
                for (std::thread &thread: threads) {
                    thread.detach();
                }
                return 0;
        }
    }
}
