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
        int userMove{};
        std::cout << "\nTurn " << turn;
        displayHP(Trainer_1[0], Trainer_2[0]);
        displayChoices(Trainer_1[0]);
        char userChoice = getChar({"f", "b", "r", "p"});

        // trainer chose fight
        if (userChoice == 'f') {
            displayMoves(Trainer_1[0]);
            userMove = getInt(0, Trainer_1[0].numMoves());

            if (userMove == 0) {
                continue;
            }
            // if move chosen is out of PP...
            else if (Trainer_1[0][userMove - 1].getPP() <= 0) {
                attackErrorMessage();
                continue;
            }
        }
        // trainer chose bag
        else if (userChoice == 'b') {
            displayBag();
            int userItem = getInt(0, 4);

            // trainer chose HP/PP items
            if (userItem == 1) {
                displayItems(userRestoreItems);
                userItem = getInt(0, static_cast<int>(userRestoreItems.size()));

                if (userItem == 0) {
                    continue;
                }
                // if trainer has at least 1 of the item selected...
                else if (userRestoreItems[userItem - 1].getQuantity() > 0) {
                    displayPokemon(Trainer_1);
                    int pokemon = getInt(0, Trainer_1.partySize());

                    if (pokemon == 0) {
                        continue;
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
                    // Pokémon's HP is already full
                    else if (Trainer_1[pokemon - 1].isFullHP()) {
                        hpFullMessage(Trainer_1[pokemon - 1]);
                        continue;
                    }
                    // Pokémon is fainted
                    else if (Trainer_1[pokemon - 1].isFainted()) {
                        hpEmptyMessage(Trainer_1[pokemon - 1]);
                        continue;
                    }
                }
                // trainer is out of selected item
                else {
                    itemErrorMessage(userRestoreItems[userItem - 1]);
                    continue;
                }
            }
            // trainer chose status items
            else if (userItem == 2) {
                displayItems(userStatusItems);
                userItem = getInt(0, static_cast<int>(userStatusItems.size()));

                if (userItem == 0) {
                    continue;
                }
                // if trainer has at least 1 of the item selected...
                else if (userStatusItems[userItem - 1].getQuantity() > 0) {
                    displayPokemon(Trainer_1);
                    int pokemon = getInt(0, Trainer_1.partySize());

                    if (pokemon == 0) {
                        continue;
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
                        continue;
                    }
                }
                // trainer is out of selected item
                else {
                    itemErrorMessage(userStatusItems[userItem - 1]);
                    continue;
                }
            }
            // trainer chose Poké Balls
            else if (userItem == 3) {
                displayItems(userPokeBalls);
                userItem = getInt(0, static_cast<int>(userPokeBalls.size()));

                if (userItem == 0) {
                    continue;
                }
                // if trainer has at least one of item selected...
                else if (userPokeBalls[userItem - 1].getQuantity() > 0) {
                    bool shakes[4];
                    useItem(userPokeBalls[userItem - 1]);
                    useItemMessage(userPokeBalls[userItem - 1].getName());
                    bool caught = catchPokemon(shakes);
                    catchPokemonMessage(Trainer_2[0], shakes);
                    if (caught) {
                        break;
                    }
                }
                // trainer is out of selected item
                else {
                    itemErrorMessage(userPokeBalls[userItem - 1]);
                    continue;
                }
            }

            // trainer chose battle items
            else if (userItem == 4) {
                displayItems(userBattleItems);
                userItem = getInt(0, static_cast<int>(userBattleItems.size()));

                if (userItem == 0) {
                    continue;
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
                __attribute__((unused)) int temp = getInt(0, 0);

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
        battlePhase::fight(Trainer_1, Trainer_2, userMove);
        ++turn;
    }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// END OF BATTLE
    return 0;
}