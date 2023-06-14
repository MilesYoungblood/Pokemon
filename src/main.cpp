#include "Functions/CoreFunctions.h"

int main() {
    Trainer_1[0].setMoves({ &WShuriken, &DarkPulse, &IceBeam, &Extrasensory });
    Trainer_1[1].setMoves({ &Flamethrower, &AirSlash, &DragonPulse, &SolarBeam });
    Trainer_1[2].setMoves({ &DarkPulse, &DragonPulse, &Flamethrower, &FocusBlast });

    Trainer_2[0].setMoves({ &Thunder, &QuickAttack, &IronTail, &VoltTackle });
    Trainer_2[1].setMoves({ &AuraSphere, &FlashCannon, &DragonPulse, &DarkPulse });

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