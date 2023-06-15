#include "Functions/CoreFunctions.h"

int main() {
    Trainer_1[0].setMoves({&waterShuriken, &DarkPulse, &iceBeam, &Extrasensory });
    Trainer_1[1].setMoves({&flamethrower, &AirSlash, &DragonPulse, &SolarBeam });
    Trainer_1[2].setMoves({&DarkPulse, &DragonPulse, &flamethrower, &focusBlast });

    Trainer_2[0].setMoves({ &thunder, &QuickAttack, &ironTail, &voltTackle });
    Trainer_2[1].setMoves({&auraSphere, &flashCannon, &DragonPulse, &DarkPulse });

    displayHPBar(turn);

    introMessage(Trainer_1[0], Trainer_2[0]);

    while (true) { // enters the battle
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
                if (selectionPhase::runAway()) return 0;
                break;
            default:
                selectionPhase::choosePokemon(cancel);
        }
 
        if (not cancel)
            battlePhase::fight(Trainer_1, Trainer_2, userMove, turn);
    }
}