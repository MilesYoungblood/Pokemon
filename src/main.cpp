#include "Functions/CoreFunctions.h"
#include "Classes/Map/Map.h"

enum keys {
    ESC = 27,
    UP_ARROW __attribute__((unused)) = 72,
    LEFT_ARROW __attribute__((unused)) = 75,
    DOWN_ARROW __attribute__((unused)) = 80,
    RIGHT_ARROW __attribute__((unused)) = 77,
    ENTER = 13
};

void engageBattle(Trainer &player, Trainer * npc, bool isTrainer) {
    size_t turn = 1;

    displayHPBar(turn);
    introMessage(player[0], (*npc)[0]);

    bool keepPlaying = true;

    while (keepPlaying) { // enters the battle
        int option = 0;
        bool print = true;

        reprint:
        displayHPBar(player[0], (*npc)[0], turn);
        displayChoices(player[0], option, print);

        if (not chooseOption(option, 3))
            goto reprint;

        int userMove = player.partySize();      // passed into fight to determine move used
        bool cancel = false;                    // passed into core four functions to know if to return to main screen

        chooseOption:
        switch (option) {
            case 0:
                userMove = selectionPhase::chooseMove(player, npc, turn, cancel);
                break;
            case 1:
                selectionPhase::chooseItem(player, npc, turn, cancel, isTrainer, keepPlaying);
                break;
            case 2:
                if (selectionPhase::runAway(player, npc, turn, cancel, not isTrainer)) {
                    npc->defeat();
                    return;
                }
                break;
            case 3:
                selectionPhase::choosePokemon(player, npc, turn, cancel);
                break;
            default:
                goto chooseOption;
        }

        if (not cancel)
            battlePhase::fight(player, *npc, userMove, turn, keepPlaying);
    }
}

bool isTrainerHere(const std::vector<NPC> &npcArray, int x, int y) {
    return std::any_of(npcArray.begin(), npcArray.end(), [&x, &y](const NPC &npc){ return npc.getX() == x and npc.getY() == y; });
}

#include "Data/Data.h"

int main() {
    ShowConsoleCursor(false);

    Trainer_1[0].setMoves({ new WaterShuriken, new DarkPulse, new IceBeam, new Extrasensory });
    Trainer_1[1].setMoves({ new Flamethrower, new AirSlash, new DragonPulse, new SolarBeam });
    Trainer_1[2].setMoves({ new DarkPulse, new DragonPulse, new Flamethrower, new FocusBlast });

    Trainer_1.setItems({{ new Potion(2), new Ether(2) }, {}, {}, {}});

    std::vector<NPC> npcArr = { Trainer_2 };

    npcArr[0][0].setMoves({ new Thunder, new QuickAttack, new IronTail, new VoltTackle });
    npcArr[0][1].setMoves({ new AuraSphere, new FlashCannon, new DragonPulse, new DarkPulse });

    Map Route_1(12, 10);

    Route_1.setObstruction(1, 2);
    Route_1.setObstruction(1, 3);
    Route_1.setObstruction(5, 5);
    Route_1.setObstruction(4, 5);
    Route_1.setObstruction(3, 5);

    Route_1.print(Trainer_1, npcArr);

    while (true) {
        // checks if the player is in the line of sight of any trainers
        for (int i = 0; i < npcArr.size(); ++i) {
            if (npcArr[i].hasVisionOf(&Trainer_1) and not npcArr[i].isDefeated()) {
                npcArr[i].moveToPlayer(Route_1, Trainer_1, npcArr);
                Trainer_1.face(&npcArr[i]);
                Route_1.print(Trainer_1, npcArr);

                Sleep(2000);
                system("cls");
                engageBattle(Trainer_1, &npcArr[i], true);
                Route_1.print(Trainer_1, npcArr);
            }
        }

        chooseInput:
        switch (static_cast<char>(getch())) {
            case 'w':
                if (not Trainer_1.isFacingNorth()) {
                    Trainer_1.faceNorth();
                    Route_1.print(Trainer_1, npcArr);
                }
                else if (Trainer_1.getY() - 1 >= 0 and not Route_1[Trainer_1.getX()][Trainer_1.getY() - 1] and not isTrainerHere(npcArr, Trainer_1.getX(), Trainer_1.getY() - 1)) {
                    Trainer_1.moveNorth();
                    Route_1.print(Trainer_1, npcArr);
                }
                break;

            case 'a':
                if (not Trainer_1.isFacingWest()) {
                    Trainer_1.faceWest();
                    Route_1.print(Trainer_1, npcArr);
                }
                else if (Trainer_1.getX() - 1 >= 0 and not Route_1[Trainer_1.getX() - 1][Trainer_1.getY()] and not isTrainerHere(npcArr, Trainer_1.getX() - 1, Trainer_1.getY())) {
                    Trainer_1.moveWest();
                    Route_1.print(Trainer_1, npcArr);
                }
                break;

            case 's':
                if (not Trainer_1.isFacingSouth()) {
                    Trainer_1.faceSouth();
                    Route_1.print(Trainer_1, npcArr);
                }
                else if (Trainer_1.getY() + 1 <= Route_1.getYBounds() - 1 and not Route_1[Trainer_1.getX()][Trainer_1.getY() + 1] and not isTrainerHere(npcArr, Trainer_1.getX(), Trainer_1.getY() + 1)) {
                    Trainer_1.moveSouth();
                    Route_1.print(Trainer_1, npcArr);
                }
                break;

            case 'd':
                if (not Trainer_1.isFacingEast()) {
                    Trainer_1.faceEast();
                    Route_1.print(Trainer_1, npcArr);
                }
                else if (Trainer_1.getX() + 1 <= Route_1.getXBounds() - 1 and not Route_1[Trainer_1.getX() + 1][Trainer_1.getY()] and not isTrainerHere(npcArr, Trainer_1.getX() + 1, Trainer_1.getY())) {
                    Trainer_1.moveEast();
                    Route_1.print(Trainer_1, npcArr);
                }
                break;

            case keys::ENTER:
                for (int i = 0; i < npcArr.size(); ++i) {
                    if (Trainer_1.hasVisionOf(&npcArr[i]) and not npcArr[i].hasVisionOf(&Trainer_1)) {
                        npcArr[i].face(&Trainer_1);
                        Route_1.print(Trainer_1, npcArr);
                        break;
                    }
                }
                break;

            case keys::ESC:
                return 0;

            default:
                goto chooseInput;
        }
    }
}
