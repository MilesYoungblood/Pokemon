#include "Functions/CoreFunctions.h"

const int mapLengthX = 10;
const int mapLengthY = 10;

enum keys { ESC = 27, UP_ARROW __attribute__((unused)) = 72, LEFT_ARROW __attribute__((unused)) = 75, DOWN_ARROW __attribute__((unused)) = 80, RIGHT_ARROW __attribute__((unused)) = 77 };

void engageBattle() {
    displayHPBar(turn);

    introMessage(Trainer_1[0], Trainer_2[0]);

    bool keepPlaying = true;

    while (keepPlaying) { // enters the battle
        displayHPBar(Trainer_1[0], Trainer_2[0], turn);
        displayChoices(Trainer_1[0]);

        int userMove = 0;       // passed into fight to determine move used
        bool cancel = false;    // passed into core four functions to know if to return to main screen

        switch (getChar({'f', 'b', 'r', 'p'})) {
            case 'f':
                selectionPhase::chooseMove(userMove, cancel);
                break;
            case 'b':
                selectionPhase::chooseItem(cancel);
                break;
            case 'r':
                if (selectionPhase::runAway()) {
                    Trainer_2.defeat();
                    return;
                }
                break;
            default:
                selectionPhase::choosePokemon(cancel);
        }

        if (not cancel)
            battlePhase::fight(Trainer_1, Trainer_2, userMove, turn, keepPlaying);
    }
}

void printMap(bool m[][mapLengthY], const Trainer &trainer, const NPC &npc) {
    system("cls");

    std::cout << "Press ESC to quit\n";

    // top border
    std::cout << '+';
    std::cout << std::string(mapLengthX, '-');
    std::cout << "+\n";

    for (int y = 0; y < mapLengthY; ++y) {
        std::cout << '|';
        for (int x = 0; x < mapLengthX; ++x) {
            // if an obstruction is in this spot
            if (m[x][y]) {
                std::cout << 'X';
            }
            // if the player is currently at these coordinates
            else if (x == trainer.getX() and y == trainer.getY()) {
                std::cout << trainer.getModel();
            }

            else if (x == npc.getX() and y == npc.getY()) {
                std::cout << npc.getModel();
            }
                // empty space
            else {
                std::cout << ' ';
            }
        }
        std::cout << "|\n";
    }

    // bottom border
    std::cout << '+';
    std::cout << std::string(mapLengthX, '-');
    std::cout << '+' << std::flush;
}

void check(bool map[][mapLengthY], Trainer &trainer, NPC &npc) {
    if (npc.isInRange(trainer) and not npc.isDefeated()) {
        if (npc.isFacingNorth()) {
            while (npc.getY() != trainer.getY() + 1) {
                npc.move(directions::NORTH);
                Sleep(250);
                printMap(map, trainer, npc);
            }
            trainer.changeDirection(directions::SOUTH);
            printMap(map, trainer, npc);
        }
        else if (npc.isFacingEast()) {
            while (npc.getX() != trainer.getX() - 1) {
                npc.move(directions::EAST);
                Sleep(250);
                printMap(map, trainer, npc);
            }
            trainer.changeDirection(directions::WEST);
            printMap(map, trainer, npc);
        }
        else if (npc.isFacingSouth()) {
            while (npc.getY() != trainer.getY() - 1) {
                npc.move(directions::SOUTH);
                Sleep(250);
                printMap(map, trainer, npc);
            }
            trainer.changeDirection(directions::NORTH);
            printMap(map, trainer, npc);
        }
        else if (npc.isFacingWest()) {
            while (npc.getX() != trainer.getX() + 1) {
                npc.move(directions::WEST);
                Sleep(250);
                printMap(map, trainer, npc);
            }
            trainer.changeDirection(directions::EAST);
            printMap(map, trainer, npc);
        }

        Sleep(2000);
        system("cls");

        engageBattle();
        printMap(map, trainer, npc);
    }
}

int main() {
    Trainer_1[0].setMoves({ &waterShuriken, &DarkPulse, &iceBeam, &Extrasensory });
    Trainer_1[1].setMoves({ &flamethrower, &AirSlash, &DragonPulse, &SolarBeam });
    Trainer_1[2].setMoves({ &DarkPulse, &DragonPulse, &flamethrower, &focusBlast });

    Trainer_2[0].setMoves({ &thunder, &QuickAttack, &ironTail, &voltTackle });
    Trainer_2[1].setMoves({ &auraSphere, &flashCannon, &DragonPulse, &DarkPulse });

    //std::vector<Trainer*> trainers = { &Trainer_1, &Trainer_2 };
    /*
     * Our map is represented by boolean values.
     * A true denotes that there is an obstruction,
     * A false denotes a walkable pathway.
     */
    bool map[mapLengthX][mapLengthY];

    // map initialization
    for (auto &i : map) {
        for (bool &j : i) {
            j = false;
        }
    }
    /*
    for (int i = 0; i < mapLengthY; ++i) {
        for (int j = 0; j < mapLengthY; ++j) {
            map[i][j] = false;
            for (auto &trainer : trainers) {
                if (trainer->getX() == i and trainer->getY() == j) {
                    map[i][j] = true;
                }
            }
        }
    }
    */

    map[1][2] = true;
    map[1][3] = true;
    map[5][5] = true;
    map[4][5] = true;

    printMap(map, Trainer_1, Trainer_2);

    while (true) {
        check(map, Trainer_1, Trainer_2);

        switch (static_cast<char>(getch())) {
            //case keys::UP_ARROW:
            case 'w':
                if (not Trainer_1.isFacingNorth()) {
                    Trainer_1.changeDirection(directions::NORTH);
                    printMap(map, Trainer_1, Trainer_2);
                }
                else if (Trainer_1.getY() - 1 >= 0 and not map[Trainer_1.getX()][Trainer_1.getY() - 1]) {
                    Trainer_1.move(directions::NORTH);
                    printMap(map, Trainer_1, Trainer_2);
                }
                break;

            //case keys::LEFT_ARROW:
            case 'a':
                if (not Trainer_1.isFacingWest()) {
                    Trainer_1.changeDirection(directions::WEST);
                    printMap(map, Trainer_1, Trainer_2);
                }
                else if (Trainer_1.getX() - 1 >= 0 and not map[Trainer_1.getX() - 1][Trainer_1.getY()]) {
                    Trainer_1.move(directions::WEST);
                    printMap(map, Trainer_1, Trainer_2);
                }
                break;

            //case keys::DOWN_ARROW:
            case 's':
                if (not Trainer_1.isFacingSouth()) {
                    Trainer_1.changeDirection(directions::SOUTH);
                    printMap(map, Trainer_1, Trainer_2);
                }
                else if (Trainer_1.getY() + 1 <= mapLengthY - 1 and not map[Trainer_1.getX()][Trainer_1.getY() + 1]) {
                    Trainer_1.move(directions::SOUTH);
                    printMap(map, Trainer_1, Trainer_2);
                }
                break;

            //case keys::RIGHT_ARROW:
            case 'd':
                if (not Trainer_1.isFacingEast()) {
                    Trainer_1.changeDirection(directions::EAST);
                    printMap(map, Trainer_1, Trainer_2);
                }
                else if (Trainer_1.getX() + 1 <= mapLengthX - 1 and not map[Trainer_1.getX() + 1][Trainer_1.getY()]) {
                    Trainer_1.move(directions::EAST);
                    printMap(map, Trainer_1, Trainer_2);
                }
                break;

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