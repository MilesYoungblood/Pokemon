#include "main.h"
#include "Data.h"

int main() {
    Trainer_1[0].setMoves({WShuriken, DarkPulse, IceBeam, Extrasensory});
    Trainer_1[1].setMoves({Flamethrower, AirSlash, DragonPulse, SolarBeam});
    Trainer_1[2].setMoves({DarkPulse, DragonPulse, Flamethrower, FocusBlast});

    Trainer_2[0].setMoves({Thunder, QuickAttack, IronTail, VoltTackle});
    Trainer_2[1].setMoves({AuraSphere, FlashCannon, DragonPulse, DarkPulse});

    int turn = 1;

    introMessage(Trainer_1[0], Trainer_2[0]);

    while (true) { // enters the battle
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// USER SELECTIONS
        int userMove;
        std::cout << "\nTurn " << turn;
        displayHP(Trainer_1[0], Trainer_2[0]);
        displayChoices(Trainer_1[0]);
        char userChoice = getChar({"f", "b", "r", "p"});

        if (userChoice == 'f') { // trainer chose fight
            displayMoves(Trainer_1[0]);
            userMove = getInt(0, Trainer_1[0].numMoves());

            if (userMove == 0) {
                continue;
            }
            else if (Trainer_1[0][userMove - 1].getPP() <= 0) { // if move chosen is out of PP...
                attackErrorMessage();
                continue;
            }
        }

        else if (userChoice == 'b') { // trainer chose bag
            displayBag();
            int userItem = getInt(0, 4);

            if (userItem == 1) { // trainer chose HP/PP items
                displayItems(userRestoreItems);
                userItem = getInt(0, static_cast<int>(userRestoreItems.size()));

                if (userItem == 0) {
                    continue;
                }
                else if (userRestoreItems[userItem - 1].getQuantity() > 0) { // if trainer has at least 1 of the item selected...
                    displayPokemon(Trainer_1);
                    int pokemon = getInt(0, Trainer_1.partySize());

                    if (pokemon == 0) {
                        continue;
                    }
                    // if Pokémon selected doesn't have full HP, but also isn't fainted...
                    else if (0 < Trainer_1[pokemon - 1].getHP() and Trainer_1[pokemon - 1].getHP() < Trainer_1[pokemon - 1].getMaxHp()) {
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
                            userMove = getInt(0, Trainer_1[0].numMoves());

                            if (userMove == 0) {
                                continue;
                            }
                            else {
                                useItem(userRestoreItems[userItem - 1]);
                                useItemMessage(userRestoreItems[userItem - 1].getName());
                                PP::restore(Trainer_1[pokemon - 1][userMove - 1],userRestoreItems[userItem - 1].getAmount());
                                PP::restoreMessage(Trainer_1[pokemon - 1][userMove - 1],userRestoreItems[userItem - 1].getAmount());
                            }
                        }
                    }
                    else { // Pokémon's HP is already full
                        hpFullMessage(Trainer_1[pokemon - 1].getName());
                        continue;
                    }
                }
                else { // trainer is out of selected item
                    itemErrorMessage(userRestoreItems[userItem - 1]);
                    continue;
                }
            }

            else if (userItem == 2) { // trainer chose status items
                displayItems(userStatusItems);
                userItem = getInt(0, static_cast<int>(userStatusItems.size()));

                if (userItem == 0) {
                    continue;
                }
                else if (userStatusItems[userItem - 1].getQuantity() > 0) { // if trainer has at least 1 of the item selected...
                    displayPokemon(Trainer_1);
                    int pokemon = getInt(0, Trainer_1.partySize());

                    if (pokemon == 0) {
                        continue;
                    }
                    else if (Trainer_1[pokemon - 1].getHP() > 0) { // if Pokémon is not fainted...
                        if (Trainer_1[pokemon - 1].getStatus() != "No status") { // if Pokémon has status condition...
                            useItem(userStatusItems[userItem - 1]);
                            useItemMessage(userStatusItems[userItem - 1].getName());
                            cure(Trainer_1[pokemon - 1], userStatusItems[userItem - 1]);
                            cureMessage(Trainer_1[pokemon - 1], userStatusItems[userItem - 1].getRestoreType());
                        }
                        else { // Pokémon did not have a status condition
                            useItem(userStatusItems[userItem - 1]);
                            noEffectMessage(userStatusItems[userItem - 1], Trainer_1[pokemon - 1]);
                        }
                    }
                    else { // Pokémon is fainted
                        hpEmptyMessage(Trainer_1[pokemon - 1]);
                        continue;
                    }
                }
                else { // trainer is out of selected item
                    itemErrorMessage(userStatusItems[userItem - 1]);
                    continue;
                }
            }

            else if (userItem == 3) { // trainer chose Poké Balls
                displayItems(userPokeBalls);
                userItem = getInt(0, static_cast<int>(userPokeBalls.size()));

                if (userItem == 0) {
                    continue;
                }
                else if (userPokeBalls[userItem - 1].getQuantity() > 0) { // if trainer has at least one of item selected...
                    bool shakes[4];
                    useItem(userPokeBalls[userItem - 1]);
                    useItemMessage(userPokeBalls[userItem - 1].getName());
                    bool caught = catchPokemon(shakes);
                    catchPokemonMessage(Trainer_2[0], shakes);
                    if (caught) {
                        break;
                    }
                }
                else { // trainer is out of selected item
                    itemErrorMessage(userPokeBalls[userItem - 1]);
                    continue;
                }
            }

            else if (userItem == 4) { // trainer chose battle items
                displayItems(userBattleItems);
                userItem = getInt(0, static_cast<int>(userBattleItems.size()));

                if (userItem == 0) {
                    continue;
                }
                else if (userBattleItems[userItem - 1].getQuantity() > 0) { // if trainer has at least 1 of the item selected...
                    bool limitReached = false;
                    useItem(userBattleItems[userItem - 1]);
                    useItemMessage(userBattleItems[userItem - 1].getName());
                    boostStat(userBattleItems[userItem - 1], Trainer_1[0], 1, limitReached);
                    boostMessage(Trainer_1[0], userBattleItems[userItem - 1].getStat(), 1, limitReached);
                }
                else {
                    itemErrorMessage(userBattleItems[userItem - 1]);
                    continue;
                }
            }

            else if (userItem == 0) {
                continue;
            }
        }

        else if (userChoice == 'r') { // trainer chose run
            bool runAway = run();
            runMessage(runAway);
            if (runAway) {
                break;
            }
        }

        else if (userChoice == 'p') { // trainer chose Pokémon
            displayPokemon(Trainer_1);
            int pokemon = getInt(0, Trainer_1.partySize());

            if (pokemon == 0) {
                continue;
            }

            pokemonPrompt();
            userChoice = getChar({"c", "s", "0"});

            if (userChoice == 'c') {
                displayMoves(Trainer_1[pokemon - 1]);
                userMove = getInt(0, Trainer_1[0].numMoves());

                if (userMove == 0) {
                    continue;
                }

                displayMoveSummary(Trainer_1[pokemon - 1][userMove - 1]);
                userMove = getInt(0, 0);

                continue;
            }
            else if (userChoice == 's') {
                if (pokemon == 1) { // trainer chose Pokémon currently in battle
                    inBattleMessage(Trainer_1[0]);
                    continue;
                }
                else {
                    if (not Trainer_1[pokemon - 1].isFainted()) { // Pokémon chosen is not fainted
                        switchOut(Trainer_1, pokemon - 1);
                        switchOutMessage(Trainer_1, pokemon - 1);
                    }
                    else { // Pokémon chosen is fainted
                        hpEmptyMessage(Trainer_1[pokemon - 1]);
                        continue;
                    }
                }
            }
            else if (userChoice == '0') {
                continue;
            }
        }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// BATTLE PHASE
        int opponentMove = generateInteger(0, 3);
        while (Trainer_2[0][opponentMove].getPP() <= 0) { // re-selects opponent move if it's out of PP
            opponentMove = generateInteger(0, 3);
        }
        battlePhase::fight(Trainer_1, Trainer_2, userMove, opponentMove, userChoice);

        ++turn;
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// END OF BATTLE
    return 0;
}