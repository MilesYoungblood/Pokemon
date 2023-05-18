#include "main.h"
#include "Data.h"

void FIGHT(int &move, bool &skip) {
    system("cls");
    displayHP(Trainer_1[0], Trainer_2[0], turn);
    displayMoves(Trainer_1[0]);
    move = getInt(0, Trainer_1[0].numMoves());

    if (move == 0) {
        skip = true;
        return;
    }
        // if move chosen is out of PP...
    else if (not Trainer_1[0][move - 1].canUse()) {
        attackErrorMessage();
        skip = true;
        return;
    }
}

void BAG(bool &skip) {
    system("cls");
    displayHP(Trainer_1[0], Trainer_2[0], turn);
    displayBag();
    int userItem = getInt(0, 4);

    // trainer chose HP/PP items
    switch (userItem) {
        case 1:
            displayItems(userRestoreItems);
            userItem = getInt(0, static_cast<int>(userRestoreItems.size()));

            if (userItem == 0) {
                skip = true;
                return;
            }
            // if trainer has at least 1 of the item selected...
            else if (userRestoreItems[userItem - 1].getQuantity() > 0) {
                displayPokemon(Trainer_1);
                int pokemon = getInt(0, Trainer_1.partySize());

                if (pokemon == 0) {
                    skip = true;
                    return;
                }
                // if Pokémon selected doesn't have full HP, but also isn't fainted...
                else if (not Trainer_1[pokemon - 1].isFainted() and not Trainer_1[pokemon - 1].isFullHP()) {
                    // if item selected restores HP...
                    if (userRestoreItems[userItem - 1].getRestoreType() == "HP") {
                        useItem(userRestoreItems[userItem - 1]);
                        useItemMessage(userRestoreItems[userItem - 1].getName());
                        HP::restore(Trainer_1[pokemon - 1], userRestoreItems[userItem - 1].getAmount());
                        HP::restoreMessage(Trainer_1[pokemon - 1], userRestoreItems[userItem - 1].getAmount());
                    }
                    // if item selected restores PP...
                    else if (userRestoreItems[userItem - 1].getRestoreType() == "PP") {
                        displayMoves(Trainer_1[pokemon - 1]);
                        int move = getInt(0, Trainer_1[0].numMoves());

                        if (move == 0) {
                            skip = true;
                            return;
                        }
                        else {
                            useItem(userRestoreItems[userItem - 1]);
                            useItemMessage(userRestoreItems[userItem - 1].getName());
                            PP::restore(Trainer_1[pokemon - 1][move - 1], userRestoreItems[userItem - 1].getAmount());
                            PP::restoreMessage(Trainer_1[pokemon - 1][move - 1], userRestoreItems[userItem - 1].getAmount());
                        }
                    }
                }
                // Pokémon's HP is already full
                else if (Trainer_1[pokemon - 1].isFullHP()) {
                    hpFullMessage(Trainer_1[pokemon - 1]);
                    skip = true;
                    return;
                }
                // Pokémon is fainted
                else if (Trainer_1[pokemon - 1].isFainted()) {
                    hpEmptyMessage(Trainer_1[pokemon - 1]);
                    skip = true;
                    return;
                }
            }
            // trainer is out of selected item
            else {
                itemErrorMessage(userRestoreItems[userItem - 1]);
                skip = true;
                return;
            }
            break;

        case 2:
            displayItems(userStatusItems);
            userItem = getInt(0, static_cast<int>(userStatusItems.size()));

            if (userItem == 0) {
                skip = true;
                return;
            }
            // if trainer has at least 1 of the item selected...
            else if (userStatusItems[userItem - 1].getQuantity() > 0) {
                displayPokemon(Trainer_1);
                int pokemon = getInt(0, Trainer_1.partySize());

                if (pokemon == 0) {
                    skip = true;
                    return;
                }
                // if Pokémon is not fainted...
                else if (Trainer_1[pokemon - 1].getHP() > 0) {
                    // if Pokémon has status condition...
                    if (Trainer_1[pokemon - 1].getStatus() != "No status") {
                        useItem(userStatusItems[userItem - 1]);
                        useItemMessage(userStatusItems[userItem - 1].getName());
                        cure(Trainer_1[pokemon - 1], userStatusItems[userItem - 1]);
                        cureMessage(Trainer_1[pokemon - 1], userStatusItems[userItem - 1].getRestoreType());
                    }
                    // Pokémon did not have a status condition
                    else {
                        useItem(userStatusItems[userItem - 1]);
                        noEffectMessage(userStatusItems[userItem - 1], Trainer_1[pokemon - 1]);
                    }
                }
                // Pokémon is fainted
                else {
                    hpEmptyMessage(Trainer_1[pokemon - 1]);
                    skip = true;
                    return;
                }
            }
            // trainer is out of selected item
            else {
                itemErrorMessage(userStatusItems[userItem - 1]);
                skip = true;
                return;
            }
            break;

        case 3:
            displayItems(userPokeBalls);
            userItem = getInt(0, static_cast<int>(userPokeBalls.size()));

            if (userItem == 0) {
                skip = true;
                return;
            }
                // if trainer has at least one of item selected...
            else if (userPokeBalls[userItem - 1].getQuantity() > 0) {
                bool shakes[4];
                useItem(userPokeBalls[userItem - 1]);
                useItemMessage(userPokeBalls[userItem - 1].getName());
                bool caught = catchPokemon(shakes);
                catchPokemonMessage(Trainer_2[0], shakes);
                if (caught) {
                    exit(0);
                }
            }
                // trainer is out of selected item
            else {
                itemErrorMessage(userPokeBalls[userItem - 1]);
                skip = true;
                return;
            }
            break;

        case 4:
            displayItems(userBattleItems);
            userItem = getInt(0, static_cast<int>(userBattleItems.size()));

            if (userItem == 0) {
                skip = true;
                return;
            }
                // if trainer has at least 1 of the item selected...
            else if (userBattleItems[userItem - 1].getQuantity() > 0) {
                bool limitReached = false;
                useItem(userBattleItems[userItem - 1]);
                useItemMessage(userBattleItems[userItem - 1].getName());
                boostStat(userBattleItems[userItem - 1], Trainer_1[0], 1, limitReached);
                boostMessage(Trainer_1[0], userBattleItems[userItem - 1].getStat(), 1, limitReached);
            }
                // trainer is out of selected item
            else {
                itemErrorMessage(userBattleItems[userItem - 1]);
                skip = true;
                return;
            }
            break;

        default:
            skip = true;
            return;
    }
}

bool RUN() {
    system("cls");
    displayHP(Trainer_1[0], Trainer_2[0], turn);

    bool runAway = generateInteger(0, 1) == 1;
    runMessage(runAway);

    return runAway;
}

void POKEMON(bool &skip) {
    system("cls");
    displayHP(Trainer_1[0], Trainer_2[0], turn);
    displayPokemon(Trainer_1);
    int pokemon = getInt(0, Trainer_1.partySize());
    int userMove;

    if (pokemon == 0) {
        skip = true;
        return;
    }

    system("cls");
    displayHP(Trainer_1[0], Trainer_2[0], turn);
    pokemonPrompt();

    switch (getChar({'c', 's', '0'})) {
        case 'c':
            system("cls");
            displayHP(Trainer_1[0], Trainer_2[0], turn);
            displayMoves(Trainer_1[pokemon - 1]);
            userMove = getInt(0, Trainer_1[0].numMoves());

            if (userMove == 0) {
                skip = true;
                return;
            }

            system("cls");
            displayHP(Trainer_1[0], Trainer_2[0], turn);
            displayMoveSummary(Trainer_1[pokemon - 1][userMove - 1]);
            getInt(0, 0);

            skip = true;
            return;

        case 's':
            if (pokemon == 1) { // trainer chose Pokémon currently in battle
                system("cls");
                displayHP(Trainer_1[0], Trainer_2[0], turn);
                inBattleMessage(Trainer_1[0]);
                skip = true;
                return;
            }
            else {
                if (not Trainer_1[pokemon - 1].isFainted()) { // Pokémon chosen is not fainted
                    system("cls");
                    displayHP(Trainer_1[0], Trainer_2[0], turn);
                    switchOut(Trainer_1, pokemon - 1);
                    switchOutMessage(Trainer_1, pokemon - 1);
                }
                else { // Pokémon chosen is fainted
                    system("cls");
                    displayHP(Trainer_1[0], Trainer_2[0], turn);
                    hpEmptyMessage(Trainer_1[pokemon - 1]);
                    skip = true;
                    return;
                }
            }
            break;

        default:
            skip = true;
            return;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// MAIN

int main() {
    Trainer_1[0].setMoves({WShuriken, DarkPulse, IceBeam, Extrasensory});
    Trainer_1[1].setMoves({Flamethrower, AirSlash, DragonPulse, SolarBeam});
    Trainer_1[2].setMoves({DarkPulse, DragonPulse, Flamethrower, FocusBlast});

    Trainer_2[0].setMoves({Thunder, QuickAttack, IronTail, VoltTackle});
    Trainer_2[1].setMoves({AuraSphere, FlashCannon, DragonPulse, DarkPulse});

    displayEmptyHP(turn);

    introMessage(Trainer_1[0], Trainer_2[0]);

    while (true) { // enters the battle
        system("cls");
        displayHP(Trainer_1[0], Trainer_2[0], turn);
        displayChoices(Trainer_1[0]);

        int userMove = 0;       // passed into fight to determine move used
        bool cancel = false;    // passed into core four functions to know if to return to main screen

        switch (getChar({'f', 'b', 'r', 'p'})) {
            case 'f':
                FIGHT(userMove, cancel);
                break;

            case 'b':
                BAG(cancel);
                break;

            case 'r':
                if (RUN())
                    return 0;
                break;

            default:
                POKEMON(cancel);
        }

        if (not cancel) {
            system("cls");
            displayHP(Trainer_1[0], Trainer_2[0], turn);
            battlePhase::fight(Trainer_1, Trainer_2, userMove, turn);
            ++turn;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////