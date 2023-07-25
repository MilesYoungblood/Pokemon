//
// Created by Miles on 18/05/2023.
//

#pragma once

#include "AttackFunctions.h"
#include "../Data/Data.h"

// returns true once the user has pressed enter and false if the user chooses up (w) or down (s)
bool chooseOption(int &option, int upper) {
    retry:
    switch (static_cast<char>(getch())) {
        case 'w':
            if (option - 1 >= 0) {
                --option;
                return false;
            }
            else {
                goto retry;
            }

        case 's':
            if (option + 1 <= upper) {
                ++option;
                return false;
            }
            else {
                goto retry;
            }

        case 13:
            return true;

        default:
            goto retry;
    }
}

namespace selectionPhase {
    int chooseMove(Trainer &trainer_1, Trainer * trainer_2, size_t t, bool &skip) {
        int move = 0;
        bool print = true;

    chooseMove:
        displayHPBar(trainer_1[0], (*trainer_2)[0], t);
        displayMoves(trainer_1[0], move, print);

        if (not chooseOption(move, trainer_1[0].numMoves())) {
            goto chooseMove;
        }

        // user chose to go back
        if (move == trainer_1[0].numMoves()) {
            skip = true;
            return 0;
        }
        // if move chosen is out of PP...
        else if (not trainer_1[0][move].canUse()) {
            attackErrorMessage();
            goto chooseMove;
        }
        else {
            return move;
        }
    }

    void chooseItem(Trainer &trainer_1, Trainer * trainer_2, size_t t, bool &skip, bool isTrainerBattle, bool &keepPlaying) {
        int userItem = 0;
        bool print = true;

    chooseItemType:
        displayHPBar(trainer_1[0], (*trainer_2)[0], t);
        displayBag(userItem, print);

        if (not chooseOption(userItem, 4))
            goto chooseItemType;

        // trainer chose HP/PP items
        switch (userItem) {
            case 0:
                print = true;

            chooseRestoreItem:
                displayHPBar(trainer_1[0], (*trainer_2)[0], t);
                displayItems(userRestoreItems, userItem, print);

                if (not chooseOption(userItem, static_cast<int>(userRestoreItems.size())))
                    goto chooseRestoreItem;

                if (userItem == static_cast<int>(userRestoreItems.size())) {
                    userItem = 0;
                    print = true;
                    goto chooseItemType;
                }

                // if trainer has at least 1 of the item selected...
                else if (userRestoreItems[userItem].getQuantity() > 0) {
                    int pokemon = 0;
                    print = true;

                chooseRestorePokemon:
                    displayHPBar(trainer_1[0], (*trainer_2)[0], t);
                    displayPokemon(trainer_1, pokemon, print);

                    if (not chooseOption(pokemon, trainer_1.partySize()))
                        goto chooseRestorePokemon;

                    if (pokemon == trainer_1.partySize()) {
                        userItem = 0;
                        print = true;
                        goto chooseRestoreItem;
                    }
                    // Pokémon's HP is already full
                    else if (trainer_1[pokemon].isFullHP()) {
                        displayHPBar(trainer_1[0], (*trainer_2)[0], t);
                        hpFullMessage(trainer_1[pokemon]);
                        goto chooseRestorePokemon;
                    }
                    // Pokémon is fainted
                    else if (trainer_1[pokemon].isFainted()) {
                        displayHPBar(trainer_1[0], (*trainer_2)[0], t);
                        hpEmptyMessage(trainer_1[pokemon]);
                        goto chooseRestorePokemon;
                    }
                    // if Pokémon selected doesn't have full HP, but also isn't fainted...
                    else {
                        // if item selected restores HP...
                        if (userRestoreItems[userItem].getRestoreType() == "HP") {
                            displayHPBar(trainer_1[0], (*trainer_2)[0], t);
                            useItem(userRestoreItems[userItem]);
                            useItemMessage(userRestoreItems[userItem].getName());
                            HP::restore(trainer_1[pokemon], userRestoreItems[userItem].getAmount());
                            HP::restoreMessage(trainer_1[pokemon], userRestoreItems[userItem].getAmount());
                        }
                        // if item selected restores PP...
                        else if (userRestoreItems[userItem].getRestoreType() == "PP") {
                            int move = 0;
                            print = true;

                        choosePokemon:
                            displayHPBar(trainer_1[0], (*trainer_2)[0], t);
                            displayMoves(trainer_1[pokemon], move, print);
                            //int move = getInt(0, trainer_1[0].numMoves());

                            if (not chooseOption(move, trainer_1[0].numMoves()))
                                goto choosePokemon;

                            if (move == trainer_1[0].numMoves())
                                goto chooseRestorePokemon;

                            else {
                                displayHPBar(trainer_1[0], (*trainer_2)[0], t);
                                useItem(userRestoreItems[userItem]);
                                useItemMessage(userRestoreItems[userItem].getName());
                                PP::restore(trainer_1[pokemon][move], userRestoreItems[userItem].getAmount());
                                PP::restoreMessage(trainer_1[pokemon][move], userRestoreItems[userItem].getAmount());
                            }
                        }
                    }
                }
                // trainer is out of selected item
                else {
                    displayHPBar(trainer_1[0], (*trainer_2)[0], t);
                    itemErrorMessage(&userRestoreItems[userItem]);
                    goto chooseRestoreItem;
                }
                break;

            case 1:
            chooseStatusItem:
                displayHPBar(trainer_1[0], (*trainer_2)[0], t);
                displayItems(userStatusItems);
                userItem = getInt(0, static_cast<int>(userStatusItems.size()));

                if (userItem == 0) {
                    goto chooseItemType;
                }
                // if trainer has at least 1 of the item selected...
                else if (userStatusItems[userItem - 1].getQuantity() > 0) {
                chooseStatusPokemon:
                    displayHPBar(trainer_1[0], (*trainer_2)[0], t);
                    displayPokemon(trainer_1);
                    int pokemon = getInt(0, trainer_1.partySize());

                    if (pokemon == 0) {
                        goto chooseStatusItem;
                    }
                    // if Pokémon is not fainted...
                    else if (not trainer_1[pokemon - 1].isFainted()) {
                        // if Pokémon has status condition...
                        if (trainer_1[pokemon - 1].isAfflicted()) {
                            displayHPBar(trainer_1[0], (*trainer_2)[0], t);
                            useItem(userStatusItems[userItem - 1]);
                            useItemMessage(userStatusItems[userItem - 1].getName());
                            cure(trainer_1[pokemon - 1], userStatusItems[userItem - 1]);
                            cureMessage(trainer_1[pokemon - 1], userStatusItems[userItem - 1].getRestoreType());
                        }
                        // Pokémon did not have a status condition
                        else {
                            displayHPBar(trainer_1[0], (*trainer_2)[0], t);
                            useItem(userStatusItems[userItem - 1]);
                            noEffectMessage(&userStatusItems[userItem - 1], trainer_1[pokemon - 1]);
                        }
                    }
                    // Pokémon is fainted
                    else {
                        displayHPBar(trainer_1[0], (*trainer_2)[0], t);
                        hpEmptyMessage(trainer_1[pokemon - 1]);
                        goto chooseStatusPokemon;
                    }
                }
                // trainer is out of selected item
                else {
                    displayHPBar(trainer_1[0], (*trainer_2)[0], t);
                    itemErrorMessage(&userStatusItems[userItem - 1]);
                    goto chooseStatusItem;
                }
                break;

            case 2:
            choosePokeball:
                displayHPBar(trainer_1[0], (*trainer_2)[0], t);
                displayItems(userPokeBalls);
                userItem = getInt(0, static_cast<int>(userPokeBalls.size()));

                if (userItem == 0) {
                    goto chooseItemType;
                }
                // if trainer has at least one of item selected...
                else if (userPokeBalls[userItem - 1].getQuantity() > 0) {
                    if (isTrainerBattle) {
                        displayHPBar(trainer_1[0], (*trainer_2)[0], t);
                        printMessage("You cannot catch another trainer's Pokemon!");
                        Sleep(1000);
                        goto chooseItemType;
                    }
                    displayHPBar(trainer_1[0], (*trainer_2)[0], t);
                    useItem(userPokeBalls[userItem - 1]);
                    useItemMessage(userPokeBalls[userItem - 1].getName());

                    bool shakes[4];
                    bool caught = catchPokemon(shakes);
                    catchPokemonMessage((*trainer_2)[0], shakes);
                    if (caught) {
                        keepPlaying = false;
                        return;
                    }
                }
                // trainer is out of selected item
                else {
                    displayHPBar(trainer_1[0], (*trainer_2)[0], t);
                    itemErrorMessage(&userPokeBalls[userItem - 1]);
                    goto choosePokeball;
                }
                break;

            case 3:
            chooseBattleItem:
                displayHPBar(trainer_1[0], (*trainer_2)[0], t);
                displayItems(userBattleItems);
                userItem = getInt(0, static_cast<int>(userBattleItems.size()));

                if (userItem == 0) {
                    goto chooseItemType;
                }
                // if trainer has at least 1 of the item selected...
                else if (userBattleItems[userItem - 1].getQuantity() > 0) {
                    displayHPBar(trainer_1[0], (*trainer_2)[0], t);
                    useItem(userBattleItems[userItem - 1]);
                    useItemMessage(userBattleItems[userItem - 1].getName());

                    bool limitReached = false;
                    boostStat(userBattleItems[userItem - 1], trainer_1[0], 1, limitReached);
                    boostMessage(trainer_1[0], userBattleItems[userItem - 1].getStat(), 1, limitReached);
                }
                // trainer is out of selected item
                else {
                    displayHPBar(trainer_1[0], (*trainer_2)[0], t);
                    itemErrorMessage(&userBattleItems[userItem - 1]);
                    goto chooseBattleItem;
                }
                break;

            default:
                skip = true;
                return;
        }
    }

    bool runAway(Trainer &trainer_1, Trainer * trainer_2, size_t t, bool &skip, bool canRun) {
        displayHPBar(trainer_1[0], (*trainer_2)[0], t);

        if (not canRun) {
            runErrorMessage();
            skip = true;
            return false;
        }
        else {
            bool runAway = generateInteger(0, 1) == 1;
            runMessage(runAway);

            return runAway;
        }
    }

    void choosePokemon(Trainer &trainer_1, Trainer * trainer_2, size_t t, bool &skip) {
        int pokemon = 0;
        bool print = true;

        choosePokemon:
        displayHPBar(trainer_1[0], (*trainer_2)[0], t);
        displayPokemon(trainer_1, pokemon, print);

        if (not chooseOption(pokemon, trainer_1.partySize()))
            goto choosePokemon;


        if (pokemon == trainer_1.partySize()) {
            skip = true;
            return;
        }

        int option = 0;
        print = true;

        chooseOption:
        displayHPBar(trainer_1[0], (*trainer_2)[0], t);
        pokemonPrompt(option, print);

        if (not chooseOption(option, 2))
            goto chooseOption;

        int userMove;

        switch (option) {
            case 0:
                userMove = 0;
                print = true;

            chooseMove:
                displayHPBar(trainer_1[0], (*trainer_2)[0], t);
                displayMoves(trainer_1[pokemon], userMove, print);

                if (not chooseOption(userMove, trainer_1[pokemon].numMoves()))
                    goto chooseMove;

                if (userMove == trainer_1[pokemon].numMoves()) {
                    option = 0;
                    print = true;
                    goto chooseOption;
                }

                displayHPBar(trainer_1[0], (*trainer_2)[0], t);
                displayMoveSummary(trainer_1[pokemon][userMove]);
                std::cin.ignore();

                userMove = 0;
                print = true;
                goto chooseMove;

            case 1:
                // trainer chose Pokémon currently in battle
                if (pokemon == 0) {
                    displayHPBar(trainer_1[0], (*trainer_2)[0], t);
                    inBattleMessage(trainer_1[0]);
                    goto chooseOption;
                }
                else {
                    // Pokémon chosen is not fainted
                    if (not trainer_1[pokemon].isFainted()) {
                        displayHPBar(trainer_1[0], (*trainer_2)[0], t);
                        switchOut(trainer_1, pokemon);
                        switchOutMessage(trainer_1, pokemon);
                    }
                    // Pokémon chosen is fainted
                    else {
                        displayHPBar(trainer_1[0], (*trainer_2)[0], t);
                        hpEmptyMessage(trainer_1[pokemon]);
                        goto chooseOption;
                    }
                }
                break;

            default:
                print = true;
                pokemon = 0;
                goto choosePokemon;
        }
    }
}

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

        // FIXME change 4 back to 3; only using 4 for testing purposes
        if (not chooseOption(option, 4))
            goto reprint;

        if (option == 4) {
            (*npc).defeat();
            return;
        }

        int userMove = player[0].numMoves();    // passed into fight to determine move used
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
