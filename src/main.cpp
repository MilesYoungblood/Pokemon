#include "Functions/CoreFunctions.h"
#include "Classes/Map/Map.h"

const int mapLengthX = 10;
const int mapLengthY = 10;

enum keys { ESC = 27, UP_ARROW __attribute__((unused)) = 72, LEFT_ARROW __attribute__((unused)) = 75, DOWN_ARROW __attribute__((unused)) = 80, RIGHT_ARROW __attribute__((unused)) = 77 };

void engageBattle(Trainer &player, Trainer * npc, bool isTrainer) {
    displayHPBar(turn);

    introMessage(player[0], (*npc)[0]);

    bool keepPlaying = true;

    while (keepPlaying) { // enters the battle
        displayHPBar(player[0], (*npc)[0], turn);
        displayChoices(player[0]);

        int userMove = 0;       // passed into fight to determine move used
        bool cancel = false;    // passed into core four functions to know if to return to main screen

        switch (getChar({ 'f', 'b', 'r', 'p' })) {
            case 'f':
                selectionPhase::chooseMove(userMove, cancel);
                break;
            case 'b':
                selectionPhase::chooseItem(cancel);
                break;
            case 'r':
                if (selectionPhase::runAway(isTrainer)) {
                    npc->defeat();
                    return;
                }
                break;
            default:
                selectionPhase::choosePokemon(cancel);
        }

        if (not cancel)
            battlePhase::fight(player, *npc, userMove, turn, keepPlaying);
    }
}

int main() {
    Trainer_1[0].setMoves({ &waterShuriken, &DarkPulse, &iceBeam, &Extrasensory });
    Trainer_1[1].setMoves({ &flamethrower, &AirSlash, &DragonPulse, &SolarBeam });
    Trainer_1[2].setMoves({ &DarkPulse, &DragonPulse, &flamethrower, &focusBlast });

    Trainer_2[0].setMoves({ &thunder, &QuickAttack, &ironTail, &voltTackle });
    Trainer_2[1].setMoves({ &auraSphere, &flashCannon, &DragonPulse, &DarkPulse });

    Map Route_1(10, 10);

    Route_1.setObstruction(1, 2);
    Route_1.setObstruction(1, 3);
    Route_1.setObstruction(5, 5);
    Route_1.setObstruction(4, 5);

    std::vector<NPC> npcArr = { Trainer_2 };

    Route_1.print(Trainer_1, npcArr);

    while (true) {
        bool battle = npcArr[0].check(Route_1, Trainer_1, npcArr);
        if (battle) {
            Sleep(2000);
            system("cls");
            engageBattle(Trainer_1, &npcArr[0], true);
            Route_1.print(Trainer_1, npcArr);
        }

        switch (static_cast<char>(getch())) {
            case 'w':
                if (not Trainer_1.isFacingNorth()) {
                    Trainer_1.changeDirection(directions::NORTH);
                    Route_1.print(Trainer_1, npcArr);
                }
                else if (Trainer_1.getY() - 1 >= 0 and not Route_1[Trainer_1.getX()][Trainer_1.getY() - 1]) {
                    Trainer_1.move(directions::NORTH);
                    Route_1.print(Trainer_1, npcArr);
                }
                break;

            case 'a':
                if (not Trainer_1.isFacingWest()) {
                    Trainer_1.changeDirection(directions::WEST);
                    Route_1.print(Trainer_1, npcArr);
                }
                else if (Trainer_1.getX() - 1 >= 0 and not Route_1[Trainer_1.getX() - 1][Trainer_1.getY()]) {
                    Trainer_1.move(directions::WEST);
                    Route_1.print(Trainer_1, npcArr);
                }
                break;

            case 's':
                if (not Trainer_1.isFacingSouth()) {
                    Trainer_1.changeDirection(directions::SOUTH);
                    Route_1.print(Trainer_1, npcArr);
                }
                else if (Trainer_1.getY() + 1 <= mapLengthY - 1 and not Route_1[Trainer_1.getX()][Trainer_1.getY() + 1]) {
                    Trainer_1.move(directions::SOUTH);
                    Route_1.print(Trainer_1, npcArr);
                }
                break;

            case 'd':
                if (not Trainer_1.isFacingEast()) {
                    Trainer_1.changeDirection(directions::EAST);
                    Route_1.print(Trainer_1, npcArr);
                }
                else if (Trainer_1.getX() + 1 <= mapLengthX - 1 and not Route_1[Trainer_1.getX() + 1][Trainer_1.getY()]) {
                    Trainer_1.move(directions::EAST);
                    Route_1.print(Trainer_1, npcArr);
                }
                break;

            case 'e':


            case keys::ESC:
                system("cls");
                std::cout << "Thanks for playing!";
                Sleep(2000);
                return 0;

            default:
                continue;
        }
    }
}