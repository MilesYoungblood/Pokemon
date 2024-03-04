//
// Created by Miles on 10/1/2023.
//

#include "Battle.h"

void Battle::forcedSwitchPrompt(const int arrow, bool &print) {
    std::cout << "Choose an option:\n";

    arrow == 0 ? std::cout << "   ->   Fight\n" : std::cout << "\tFight\n";
    arrow == 1 ? std::cout << "   ->   Run" : std::cout << "\tRun";

    print = false;
    std::cout.flush();
}

void Battle::pokemonPrompt(const int arrow, bool &print) {
    std::cout << "Choose an option:\n";

    arrow == 0 ? std::cout << "   ->   Check Moves\n" : std::cout << "\tCheck Moves\n";
    arrow == 1 ? std::cout << "   ->   Switch\n" : std::cout << "\tSwitch\n";
    arrow == 2 ? std::cout << "\n   ->   Cancel\n" : std::cout << "\n\tCancel\n";
    std::cout.flush();

    print = false;
}

void Battle::switchOutMessage(const Trainer *trainer, const int pokemonSwitched) {
    std::cout << (*trainer)[pokemonSwitched].getName() + ", return! ";
    //pressEnter();
    std::cout << "Go " + (*trainer)[pokemonSwitched].getName() + "!\n";
    //pressEnter();
}

void Battle::switchOut(Trainer *trainer, const bool isUser) {
    //this->displayHpBar();
    int toSwitch = 0;

    if (isUser) {
        bool print = true;

        while (true) {
            Battle::forcedSwitchPrompt(toSwitch, print);
            if (chooseOption(toSwitch, 2)) {
                break;
            }
        }

        // player attempts to run
        //FIXME does not take into account trainer battle
        if (toSwitch == 1) {
            /*
            const bool run_success = run();
            Battle::runMessage(run_success);
            if (run_success) {
                this->isRunning = false;
                return;
            }
             */
        }

        print = true;

        while (true) {
            //this->displayPokemon(toSwitch, print);

            if (not chooseOption(toSwitch, this->player->partySize())) {
                continue;
            }

            if ((*trainer)[toSwitch].isFainted()) {
                (*trainer)[toSwitch - 1].hpEmptyMessage();
                //pressEnter();
                continue;
            }

            break;
        }
    }

    else {
        toSwitch = generateInteger(0, trainer->partySize() - 1);
        while ((*trainer)[toSwitch].isFainted()) {
            toSwitch = generateInteger(0, trainer->partySize() - 1);
        }
    }

    trainer->swapPokemon(0, toSwitch);
}

void Battle::chooseItem(bool &skip, const bool isTrainerBattle) {
    int userType = 0;
    int userItem = 0;
    bool print = true;

    const auto reset_variables = [&userType, &userItem, &print] -> void {
        userType = 0;
        userItem = 0;
        print = true;
    };

    chooseItemType:
    //this->displayHpBar();
    displayBag(userType, print);

    if (not chooseOption(userType, 4)) {
        goto chooseItemType;
    }

    // trainer chose HP/PP items
    switch (userType) {
        case 0:
            print = true;

        chooseRestoreItem:
            //this->displayHpBar();
            displayItems<RestoreItem>(this->player, userItem, print);

            if (not chooseOption(userItem, this->player->getNumItems<RestoreItem>())) {
                goto chooseRestoreItem;
            }

            if (userItem == this->player->getNumItems<RestoreItem>()) {
                reset_variables();
                goto chooseItemType;
            }
            // if trainer has at least 1 of the item selected...
            else if (this->player->getItem<RestoreItem>(userItem)) {
                int pokemon = 0;
                print = true;

                chooseRestorePokemon:
                //this->displayHpBar();
                //this->displayPokemon(pokemon, print);

                if (not chooseOption(pokemon, this->player->partySize())) {
                    goto chooseRestorePokemon;
                }

                if (pokemon == this->player->partySize()) {
                    reset_variables();
                    goto chooseRestoreItem;
                }
                // Pokémon's HP is already full
                else if ((*this->player)[pokemon].isFullHp()) {
                    //this->displayHpBar();
                    (*this->player)[pokemon].hpFullMessage();
                    //pressEnter();
                    goto chooseRestorePokemon;
                }
                // Pokémon is fainted
                else if ((*this->player)[pokemon].isFainted()) {
                    //this->displayHpBar();
                    (*this->player)[pokemon].hpEmptyMessage();
                    //pressEnter();
                    goto chooseRestorePokemon;
                }
                // if Pokémon selected doesn't have full HP, but also isn't fainted...
                else {
                    // if item selected restores HP...
                    if (this->player->getItem<RestoreItem>(userItem).isHp()) {
                        //this->displayHpBar();

                        this->player->getItem<RestoreItem>(userItem).use();
                        this->player->getItem<RestoreItem>(userItem).useMessage();

                        this->player->getItem<RestoreItem>(userItem).restore((*this->player)[pokemon]);
                        this->player->getItem<RestoreItem>(userItem).restoreMessage((*this->player)[pokemon]);

                        // automatically removes the item if it's quantity is now 0
                        if (not this->player->getItem<RestoreItem>(userItem)) {
                            this->player->removeItem<RestoreItem>(userItem);
                        }
                    }
                    // if item selected restores PP...
                    else {
                        int move = 0;
                        print = true;

                        choosePokemon:
                        //this->displayHpBar();
                        //Battle::displayMoves((*this->player)[pokemon], move, print);

                        if (not chooseOption(move, (*this->player)[0].numMoves())) {
                            goto choosePokemon;
                        }

                        if (move == (*this->player)[0].numMoves()) {
                            goto chooseRestorePokemon;
                        }
                        else {
                            //this->displayHpBar();

                            this->player->getItem<RestoreItem>(userItem).use();
                            this->player->getItem<RestoreItem>(userItem).useMessage();

                            this->player->getItem<RestoreItem>(userItem).restore((*this->player)[pokemon][move]);
                            this->player->getItem<RestoreItem>(userItem).restoreMessage((*this->player)[pokemon][move]);

                            // automatically removes the item if it's quantity is now 0
                            if (not this->player->getItem<RestoreItem>(userItem)) {
                                this->player->removeItem<RestoreItem>(userItem);
                            }
                        }
                    }
                }
            }
            break;

        case 1:
            print = true;

        chooseStatusItem:
            //this->displayHpBar();
            displayItems<StatusItem>(this->player, userItem, print);

            if (not chooseOption(userItem, this->player->getNumItems<StatusItem>())) {
                goto chooseStatusItem;
            }

            if (userItem == this->player->getNumItems<StatusItem>()) {
                reset_variables();
                goto chooseItemType;
            }

            // if trainer has at least 1 of the item selected...
            else if (this->player->getItem<StatusItem>(userItem)) {
                int pokemon = 0;
                print = true;

                chooseStatusPokemon:
                //this->displayHpBar();
                //this->displayPokemon(pokemon, print);

                if (not chooseOption(pokemon, this->player->partySize())) {
                    goto chooseStatusPokemon;
                }

                if (pokemon == this->player->partySize()) {
                    reset_variables();
                    goto chooseStatusItem;
                }

                // if Pokémon is not fainted...
                else if (not(*this->player)[pokemon].isFainted()) {
                    // if Pokémon has status condition...
                    if ((*this->player)[pokemon].isAfflicted()) {
                        //this->displayHpBar();

                        this->player->getItem<StatusItem>(userItem).use();
                        this->player->getItem<StatusItem>(userItem).useMessage();
                        //pressEnter();

                        this->player->getItem<StatusItem>(userItem).restore((*this->player)[pokemon]);
                        this->player->getItem<StatusItem>(userItem).restoreMessage((*this->player)[pokemon]);
                        //pressEnter();

                        // automatically removes the item if it's quantity is now 0
                        if (not this->player->getItem<StatusItem>(userItem)) {
                            this->player->removeItem<StatusItem>(userItem);
                        }
                    }
                    // Pokémon did not have a status condition
                    else {
                        //this->displayHpBar();

                        this->player->getItem<StatusItem>(userItem).use();
                        this->player->getItem<StatusItem>(userItem).noEffectMessage((*this->player)[pokemon]);

                        // automatically removes the item if it's quantity is now 0
                        if (not this->player->getItem<StatusItem>(userItem)) {
                            this->player->removeItem<StatusItem>(userItem);
                        }
                    }
                }
                // Pokémon is fainted
                else {
                    //this->displayHpBar();
                    (*this->player)[pokemon - 1].hpEmptyMessage();
                    //pressEnter();
                    goto chooseStatusPokemon;
                }
            }
            break;

        case 2:
            print = true;

        choosePokeball:
            //this->displayHpBar();
            displayItems<PokeBall>(this->player, userItem, print);

            if (not chooseOption(userItem, this->player->getNumItems<PokeBall>())) {
                goto choosePokeball;
            }

            if (userItem == this->player->getNumItems<PokeBall>()) {
                reset_variables();
                goto chooseItemType;
            }

            // if a trainer has at least one of the items selected...
            else if (this->player->getItem<PokeBall>(userItem)) {
                if (isTrainerBattle) {
                    //this->displayHpBar();
                    std::cout << "You can't catch another trainer's Pokemon!";
                    //pressEnter();
                    goto chooseItemType;
                }
                //this->displayHpBar();

                this->player->getItem<PokeBall>(userItem).use();
                this->player->getItem<PokeBall>(userItem).useMessage();

                // automatically removes the item if it's quantity is now 0
                if (not this->player->getItem<PokeBall>(userItem)) {
                    this->player->removeItem<PokeBall>(userItem);
                }

                std::array<bool, 4> shakes{};
                const bool caught = this->player->getItem<PokeBall>(userItem).catchPokemon((*this->opponent)[0], shakes);
                catchPokemonMessage((*this->opponent)[0], shakes);
                if (caught) {
                    this->isRunning = false;
                    return;
                }
            }
            break;

        case 3:
            print = true;

        chooseBattleItem:
            //this->displayHpBar();
            displayItems<BattleItem>(this->player, userItem, print);

            if (not chooseOption(userItem, this->player->getNumItems<BattleItem>())) {
                goto chooseBattleItem;
            }

            if (userItem == this->player->getNumItems<BattleItem>()) {
                reset_variables();
                goto chooseItemType;
            }

            // if trainer has at least 1 of the item selected...
            else if (this->player->getItem<BattleItem>(userItem)) {
                //this->displayHpBar();

                this->player->getItem<BattleItem>(userItem).use();
                this->player->getItem<BattleItem>(userItem).useMessage();

                bool limitReached = false;
                this->player->getItem<BattleItem>(userItem).boost((*this->player)[0], 2, limitReached);
                this->player->getItem<BattleItem>(userItem).boostMessage((*this->player)[0], 2, limitReached);

                // automatically removes the item if it's quantity is now 0
                if (not this->player->getItem<BattleItem>(userItem)) {
                    this->player->removeItem<BattleItem>(userItem);
                }
            }
            break;

        default:
            skip = true;
            return;
    }
}

void Battle::choosePokemon(bool &skip) {
    int pokemon = 0;
    bool print = true;

    choosePokemon:
    //this->displayHpBar();
    //this->displayPokemon(pokemon, print);

    if (not chooseOption(pokemon, this->player->partySize())) {
        goto choosePokemon;
    }

    if (pokemon == this->player->partySize()) {
        skip = true;
        return;
    }

    int option = 0;
    print = true;

    chooseOption:
    //this->displayHpBar();
    Battle::pokemonPrompt(option, print);

    if (not chooseOption(option, 2)) {
        goto chooseOption;
    }

    int userMove = 0;

    switch (option) {
        case 0:
            userMove = 0;
            print = true;

        chooseMove:
            //this->displayHpBar();
            //Battle::displayMoves((*this->player)[pokemon], userMove, print);

            if (not chooseOption(userMove, (*this->player)[pokemon].numMoves())) {
                goto chooseMove;
            }

            if (userMove == (*this->player)[pokemon].numMoves()) {
                option = 0;
                print = true;
                goto chooseOption;
            }

            //this->displayHpBar();
            //Battle::displayMoveSummary((*this->player)[pokemon][userMove]);
            //pressEnter();

            userMove = 0;
            print = true;
            goto chooseMove;

        case 1:
            // trainer chose Pokémon currently in battle
            if (pokemon == 0) {
                //this->displayHpBar();
                //this->inBattleMessage();
                goto chooseOption;
            }
            else {
                // Pokémon chosen is not fainted
                if (not (*this->player)[pokemon].isFainted()) {
                    //this->displayHpBar();
                    this->player->swapPokemon(0, pokemon);
                    Battle::switchOutMessage(this->player, pokemon);
                }
                // Pokémon chosen is fainted
                else {
                    //this->displayHpBar();
                    (*this->player)[pokemon].hpEmptyMessage();
                    //pressEnter();
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
