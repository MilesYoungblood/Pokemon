#include "Functions/CoreFunctions.h"

bool isTrainerHere(const std::vector<NPC> &npcArray, int x, int y) {
    return std::any_of(npcArray.begin(), npcArray.end(), [&x, &y](const NPC &npc){ return npc.getX() == x and npc.getY() == y; });
}

#include "Classes/Map/Map.h"
#include <thread>

bool canMove = true;
bool keepTurning = true;

void turn(Map &m, Trainer &t, std::vector<NPC> &npc, int index) {
    while (keepTurning) {
        if (generateInteger(1, 2) == 1) {
            npc[index].face(&npc[index]);
            m.print(t, npc);

            if (npc[index].hasVisionOf(&Trainer_1) and not npc[index].isDefeated()) {
                keepTurning = false;
                canMove = false;

                npc[index].moveToPlayer(m, Trainer_1, npc);
                Trainer_1.face(&npc[index]);
                m.print(Trainer_1, npc);

                Sleep(2000);
                system("cls");
                engageBattle(Trainer_1, &npc[index], false);
                m.print(Trainer_1, npc);
                canMove = true;
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

    std::vector<NPC> npcArr = { NPC({ Pikachu, Lucario }, 6, 6, 3) };

    npcArr[0][0].setMoves({ new Thunder, new QuickAttack, new IronTail, new VoltTackle });
    npcArr[0][1].setMoves({ new AuraSphere, new FlashCannon, new DragonPulse, new DarkPulse });

    Map Route_1(12, 10);

    Route_1.setObstruction(1, 2);
    Route_1.setObstruction(1, 3);
    Route_1.setObstruction(5, 5);
    Route_1.setObstruction(4, 5);
    Route_1.setObstruction(3, 5);

    Route_1.print(Trainer_1, npcArr);

    // initial check of the player
    for (NPC &npc : npcArr) {
        if (npc.hasVisionOf(&Trainer_1) and not npc.isDefeated()) {
            npc.moveToPlayer(Route_1, Trainer_1, npcArr);
            Trainer_1.face(&npc);
            Route_1.print(Trainer_1, npcArr);

            Sleep(2000);
            system("cls");
            engageBattle(Trainer_1, &npc, false);
            Route_1.print(Trainer_1, npcArr);
        }
    }

    // create threads for each NPC to check if the player is in sight/ turn the NPC
    std::thread threads[npcArr.size()];
    for (int i = 0; i < sizeof(threads) / sizeof(threads[0]); ++i) {
        threads[i] = std::thread(turn, std::ref(Route_1), std::ref(Trainer_1), std::ref(npcArr), i);
    }

    while (true) {
        // only able to input moves if not engaged in a battle
        if (not canMove) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            continue;
        }
        switch (static_cast<char>(getch())) {
            case 'w':
                if (not Trainer_1.isFacingNorth()) {
                    Trainer_1.faceNorth();
                    Route_1.print(Trainer_1, npcArr);
                }
                else if (not Route_1.getTile(Trainer_1.getX(), Trainer_1.getY() - 1) and not isTrainerHere(npcArr, Trainer_1.getX(), Trainer_1.getY() - 1)) {
                    Trainer_1.moveNorth();
                    Route_1.print(Trainer_1, npcArr);
                }
                break;

            case 'a':
                if (not Trainer_1.isFacingWest()) {
                    Trainer_1.faceWest();
                    Route_1.print(Trainer_1, npcArr);
                }
                else if (not Route_1.getTile(Trainer_1.getX() - 1, Trainer_1.getY()) and not isTrainerHere(npcArr, Trainer_1.getX() - 1, Trainer_1.getY())) {
                    Trainer_1.moveWest();
                    Route_1.print(Trainer_1, npcArr);
                }
                break;

            case 's':
                if (not Trainer_1.isFacingSouth()) {
                    Trainer_1.faceSouth();
                    Route_1.print(Trainer_1, npcArr);
                }
                else if (not Route_1.getTile(Trainer_1.getX(), Trainer_1.getY() + 1) and not isTrainerHere(npcArr, Trainer_1.getX(), Trainer_1.getY() + 1)) {
                    Trainer_1.moveSouth();
                    Route_1.print(Trainer_1, npcArr);
                }
                break;

            case 'd':
                if (not Trainer_1.isFacingEast()) {
                    Trainer_1.faceEast();
                    Route_1.print(Trainer_1, npcArr);
                }
                else if (not Route_1.getTile(Trainer_1.getX() + 1, Trainer_1.getY()) and not isTrainerHere(npcArr, Trainer_1.getX() + 1, Trainer_1.getY())) {
                    Trainer_1.moveEast();
                    Route_1.print(Trainer_1, npcArr);
                }
                break;

            // interact
            case keys::ENTER:
                for (NPC &npc: npcArr) {
                    if (Trainer_1.hasVisionOf(&npc) and not npc.hasVisionOf(&Trainer_1)) {
                        npc.face(&Trainer_1);
                        Route_1.print(Trainer_1, npcArr);

                        if (npc.hasVisionOf(&Trainer_1) and not npc.isDefeated()) {
                            keepTurning = false;

                            npc.moveToPlayer(Route_1, Trainer_1, npcArr);
                            Trainer_1.face(&npc);
                            Route_1.print(Trainer_1, npcArr);

                            Sleep(2000);
                            system("cls");
                            engageBattle(Trainer_1, &npc, false);
                            Route_1.print(Trainer_1, npcArr);
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
