//
// Created by Miles on 10/1/2023.
//

#include "Battle.h"

Player *Battle::player = nullptr;
Trainer *Battle::opponent = nullptr;
size_t Battle::turn = 1ull;
/*
void Battle::wildPokemonMessage(const Pokemon &pokemon) {
    printMessage("Your opponent sent out " + pokemon.getName() + "! ");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}
 */

void Battle::sendOutMessage(const Pokemon &pokemon) {
    printMessage("Go " + pokemon.getName() + "!\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void Battle::returnMessage(const Pokemon &pokemon) {
    printMessage(pokemon.getName() + ", return! ");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void Battle::introMessage() {
    printMessage("Your opponent sent out " + (*Battle::opponent)[0].getName() + "!\n");
    pressEnter();
    //printMessage("Go " + (*Battle::user)[0].getName());
    Battle::sendOutMessage((*Battle::player)[0]);
}

void Battle::displayChoices(int arrow, bool &print) {
    print ? printMessage("What will " + (*Battle::player)[0].getName() + " do?\n") : printMessage("What will " + (*Battle::player)[0].getName() + " do?\n", 0);

    arrow == 0 ? std::cout << "   ->   Fight\n" : std::cout << "\tFight\n";
    arrow == 1 ? std::cout << "   ->   Bag\n" : std::cout << "\tBag\n";
    arrow == 2 ? std::cout << "   ->   Run\n" : std::cout << "\tRun\n";
    arrow == 3 ? std::cout << "   ->   Pokemon\n" : std::cout << "\tPokemon\n";

    std::cout.flush();

    print = false;
}

void Battle::displayPokemon(int arrow, bool &print) {
    if (print) {
        printMessage("Choose a Pokemon:\n");
    }
    else {
        std::cout << "Choose a Pokemon:\n";
    }
    for (int i = 0; i < Battle::player->partySize(); ++i) {
        if (arrow == i) {
            std::cout << "   ->   " << (*Battle::player)[i] << std::string(15 - (*Battle::player)[i].getName().length(), ' ')
                      << "(HP: " << (*Battle::player)[i].getHP() << std::string(3 - std::to_string((*Battle::player)[i].getHP()).length(), ' ')
                      << '/' << std::string(3 - std::to_string((*Battle::player)[i].getMaxHp()).length(), ' ') << (*Battle::player)[i].getMaxHp()
                      << ")\n";
        }
        else {
            std::cout << '\t' << (*Battle::player)[i] << std::string(15 - (*Battle::player)[i].getName().length(), ' ')
                      << "(HP: " << (*Battle::player)[i].getHP() << std::string(3 - std::to_string((*Battle::player)[i].getHP()).length(), ' ')
                      << '/' << std::string(3 - std::to_string((*Battle::player)[i].getMaxHp()).length(), ' ') << (*Battle::player)[i].getMaxHp()
                      << ")\n";
        }
    }
    arrow == Battle::player->partySize() ? std::cout << "\n   ->   Cancel\n" : std::cout << "\n\tCancel\n";
    std::cout.flush();

    print = false;
}

void Battle::displayHPBar(bool displayPokemon = true) {
    system("cls");
    std::cout << "Turn " << Battle::turn << '\n';

    if (displayPokemon) {
        std::cout << '+' << std::string(16, '-') << '+' << std::string(13, '-') << "+\n"; // top layer

        std::cout << "| " << (*Battle::player)[0] << std::string(15 - (*Battle::player)[0].getName().length(), ' ')
                  << "| HP: " << (*Battle::player)[0].getHP()
                  << std::string(3 - std::to_string((*Battle::player)[0].getHP()).length(), ' ')
                  << '/' << (*Battle::player)[0].getMaxHp()
                  << std::string(3 - std::to_string((*Battle::player)[0].getMaxHp()).length(), ' ')
                  << " |\n";

        std::cout << '+' << std::string(16, '-') << '+' << std::string(13, '-') << "+\n"; // middle layer

        std::cout << "| " << (*Battle::opponent)[0] << std::string(15 - (*Battle::opponent)[0].getName().length(), ' ')
                  << "| HP: " << (*Battle::opponent)[0].getHP()
                  << std::string(3 - std::to_string((*Battle::opponent)[0].getHP()).length(), ' ')
                  << '/' << (*Battle::opponent)[0].getMaxHp()
                  << std::string(3 - std::to_string((*Battle::player)[0].getMaxHp()).length(), ' ')
                  << " |\n";
    }
    else {
        for (int i = 0; i < 2; ++i) {
            std::cout << '+' << std::string(16, '-') << '+' << std::string(13, '-') << "+\n";
            std::cout << '|' << std::string(16, ' ') << "|" << std::string(13, ' ') << "|\n";
        }
    }

    std::cout << '+' << std::string(16, '-') << '+' << std::string(13, '-') << "+\n\n"; // bottom layer
    std::cout.flush();
}

void Battle::faintMessage(const Pokemon &pokemon) {
    printMessage(pokemon.getName() + " fainted!\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

void Battle::forcedSwitchPrompt(int arrow, bool &print) {
    if (print)
        printMessage("Choose an option:\n");
    else
        std::cout << "Choose an option:\n";

    arrow == 0 ? std::cout << "   ->   Fight\n" : std::cout << "\tFight\n";
    arrow == 1 ? std::cout << "   ->   Run" : std::cout << "\tRun";

    print = false;
    std::cout.flush();
}

bool Battle::run() {
    const int opponentSpeed = ((*Battle::opponent)[0].getBaseSpeed() / 4) % 256;
    const int odds = (((*Battle::player)[0].getBaseSpeed() * 32) / opponentSpeed) + 30;

    return opponentSpeed == 0 or odds > 255 or generateInteger(0, 255) < odds;
}

void Battle::runMessage(bool runStatus) {
    runStatus ? printMessage("Got away safely!\n") : printMessage("Couldn't get away!\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void Battle::runErrorMessage() {
    printMessage("You can't run away from a trainer battle!");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void Battle::pokemonPrompt(int arrow, bool &print) {
    if (print) {
        printMessage("Choose an option:\n");
    }
    else {
        std::cout << "Choose an option:\n";
    }
    arrow == 0 ? std::cout << "   ->   Check Moves\n" : std::cout << "\tCheck Moves\n";
    arrow == 1 ? std::cout << "   ->   Switch\n" : std::cout << "\tSwitch\n";
    arrow == 2 ? std::cout << "\n   ->   Cancel\n" : std::cout << "\n\tCancel\n";
    std::cout.flush();

    print = false;
}

void Battle::switchOutMessage(const Trainer *t, int pokemonSwitched) {
    Battle::returnMessage((*t)[pokemonSwitched]);
    Battle::sendOutMessage((*t)[0]);
}

void Battle::inBattleMessage() {
    printMessage((*Battle::player)[0].getName() + " is already in battle!\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

void Battle::winMessage() {
    printMessage("Your opponent ran out of usable Pokemon! ");
    pressEnter();
    printMessage("You won!\n");
    pressEnter();
}

void Battle::loseMessage() {
    printMessage("You've run out of usable Pokemon! ");
    pressEnter();
    printMessage("You blacked out!\n");
    pressEnter();
}

void Battle::inflictedMessage(const Pokemon &pokemon) {
    if (pokemon.getStatus() == Status::BURN)
        printMessage(pokemon.getName() + " took " + std::to_string(static_cast<int>(lround(pokemon.getMaxHp() * .065))) + " damage from it's burn!\n");

    else if (pokemon.getStatus() == Status::PARALYSIS)
        printMessage(pokemon.getName() + " is paralyzed! It can't move!\n");

    else if (pokemon.getStatus() == Status::FREEZE)
        printMessage(pokemon.getName() + " is frozen solid!\n");

    else if (pokemon.getStatus() == Status::POISON)
        printMessage(pokemon.getName() + " took " + std::to_string(static_cast<int>(lround(pokemon.getMaxHp() * .0625))) + " damage from it's poisoning!\n");

    else if (pokemon.getStatus() == Status::SLEEP)
        printMessage(pokemon.getName() + " is fast asleep!\n");

    pressEnter();
}

void Battle::displayMoves(const Pokemon &pokemon, int arrow, bool &print) {
    if (print) {
        printMessage("Choose a move:\n");
    }
    else {
        std::cout << "Choose a move:\n";
    }
    for (int i = 0; i < pokemon.numMoves(); ++i) {
        if (arrow == i) {
            std::cout << "   ->   " << pokemon[i] << std::string(15 - pokemon[i].getName().length(), ' ')
                      << " (PP: " << pokemon[i].getPP() << std::string(2 - std::to_string(pokemon[i].getPP()).length(), ' ')
                      << '/' << std::string(2 - std::to_string(pokemon[i].getMaxPP()).length(), ' ') << pokemon[i].getMaxPP()
                      << ")\n";
        }
        else {
            std::cout << '\t' << pokemon[i] << std::string(15 - pokemon[i].getName().length(), ' ')
                      << " (PP: " << pokemon[i].getPP() << std::string(2 - std::to_string(pokemon[i].getPP()).length(), ' ')
                      << '/' << std::string(2 - std::to_string(pokemon[i].getMaxPP()).length(), ' ') << pokemon[i].getMaxPP()
                      << ")\n";
        }
    }
    arrow == pokemon.numMoves() ? std::cout << "\n   ->   Cancel\n" : std::cout << "\n\tCancel\n";
    std::cout.flush();

    print = false;
}

void Battle::displayMoveSummary(const Move &move) {
    const char *type;

    switch (move.getType()) {
        case Type::NORMAL:
            type = "normal";
            break;

        case Type::FIRE:
            type = "fire";
            break;

        case Type::WATER:
            type = "water";
            break;

        case Type::ELECTRIC:
            type = "electric";
            break;

        case Type::GRASS:
            type = "grass";
            break;

        case Type::ICE:
            type = "ice";
            break;

        case Type::FIGHTING:
            type = "fighting";
            break;

        case Type::POISON:
            type = "poison";
            break;

        case Type::GROUND:
            type = "ground";
            break;

        case Type::FLYING:
            type = "flying";
            break;

        case Type::PSYCHIC:
            type = "psychic";
            break;

        case Type::BUG:
            type = "bug";
            break;

        case Type::ROCK:
            type = "rock";
            break;

        case Type::GHOST:
            type = "ghost";
            break;

        case Type::DRAGON:
            type = "dragon";
            break;

        case Type::DARK:
            type = "dark";
            break;

        case Type::STEEL:
            type = "steel";
            break;

        case Type::FAIRY:
            type = "fairy";
            break;

        default:
            throw std::runtime_error("Unexpected error: function displayMoveSummary");
    }

    const char *category;

    switch (move.getCategory()) {
        case Category::PHYSICAL:
            category = "physical";
            break;

        case Category::SPECIAL:
            category = "special";
            break;

        case Category::STATUS:
            category = "status";
            break;
    }

    std::cout << move << '\n';
    std::cout << "\tType:     " << type << '\n';
    std::cout << "\tCategory: " << category << '\n';
    std::cout << "\tPower:    " << move.getPower() << '\n';
    std::cout << "\tAccuracy: " << move.getAccuracy() << '\n';
    std::cout << "\tPP:       " << move.getPP() << '/' << move.getMaxPP() << '\n';
    std::cout << "\n\tCancel (ENTER)\n";
    std::cout.flush();
}

void Battle::attackErrorMessage() {
    printMessage("That move is out of PP. Please select another move.\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

void Battle::takeDamage(Trainer *t, int damage) {
    (*t)[0].setHP((*t)[0].getHP() - damage);

    if ((*t)[0].isFainted()) {
        (*t).incFaintCount();
        faintMessage((*t)[0]);
    }
}

int Battle::getPhysicalAttack(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, Move &move) {
    const int levelCalc = (2 * attackingPokemon.getLevel() / 5) + 2;
    return levelCalc * attackingPokemon.getBaseAttack() * move.getDamage() / defendingPokemon.getBaseDefense();
}

int Battle::getSpecialAttack(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, Move &move) {
    const int levelCalc = (2 * attackingPokemon.getLevel() / 5) + 2;
    return levelCalc * attackingPokemon.getBaseSpAttack() * move.getDamage() / defendingPokemon.getBaseSpDefense();
}

// generates a random number between 1 and 16
// returns true and 2.0 if that number is 1 and 1.0 and false otherwise
std::pair<double, bool> Battle::criticalHit() {
    return generateInteger(1, 16) == 1 ? std::make_pair(2.0, true) : std::make_pair(1.0, false);
}

// returns 1.5 if move is a STAB move, and 1.0 otherwise
double Battle::stabCheck(const Pokemon &pokemon, const Move &move) {
    return pokemon.getType(true) == move.getType() or pokemon.getType(false) == move.getType() ? 1.5 : 1.0;
}

int Battle::calculateDamage(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, Move &move, bool &crit) {
    int initialDamage = 0;
    if (move.getCategory() == Category::PHYSICAL)
        initialDamage = getPhysicalAttack(attackingPokemon, defendingPokemon, move);
    else if (move.getCategory() == Category::SPECIAL)
        initialDamage = getSpecialAttack(attackingPokemon, defendingPokemon, move);

    const int finalDamage = (initialDamage / 50) + 2;
    const std::pair<double, bool> c = criticalHit();
    crit = c.second;

    //FIXME recalculate damage
    return static_cast<int>(finalDamage * stabCheck(attackingPokemon, move) * getTypeEffective(move, defendingPokemon) * c.first);
}

void Battle::SwitchOut(Trainer *trainer, bool isUser, bool &keepPlaying) {
    Battle::displayHPBar();
    int toSwitch = 0;

    if (isUser) {
        bool print = true;

        reprint_1:
        forcedSwitchPrompt(toSwitch, print);

        if (not chooseOption(toSwitch, 2)) {
            goto reprint_1;
        }

        // player attempts to run
        //FIXME does not take into account trainer battle
        if (toSwitch == 1) {
            bool runSuccess = run();
            runMessage(runSuccess);
            if (runSuccess) {
                keepPlaying = false;
                return;
            }
        }

        while (true) {
            print = true;

            reprint_2:
            displayPokemon(toSwitch, print);

            if (not chooseOption(toSwitch, Battle::player->partySize())) {
                goto reprint_2;
            }

            if ((*trainer)[toSwitch].isFainted()) {
                (*trainer)[toSwitch - 1].hpEmptyMessage();
                pressEnter();
                goto reprint_2;
            }

            else
                break;
        }
    }

    else {
        do {
            toSwitch = generateInteger(0, trainer->partySize() - 1);
        } while ((*trainer)[toSwitch].isFainted());
    }

    trainer->swapPokemon(0, toSwitch);
}

void Battle::Action(Trainer *attacker, Trainer *defender, int move, bool &switched, bool isUserAttacking, bool &keepPlaying) {
    bool crit = false;
    const int damage = calculateDamage((*attacker)[0], (*defender)[0], (*attacker)[0][move], crit);

    (*attacker)[0][move].action((*attacker)[0], (*defender)[0], damage);
    (*attacker)[0][move].actionMessage((*attacker)[0], (*defender)[0], damage, crit, getTypeEffective((*attacker)[0][move], (*defender)[0]));

    if ((*defender)[0].isFainted()) {
        defender->incFaintCount();
        faintMessage((*defender)[0]);
        if (not *defender) {
            Battle::displayHPBar();
            if (isUserAttacking) {
                defender->clearParty();
                winMessage();
            }
            else {
                loseMessage();
            }
            keepPlaying = false;
        }
        else {
            if (isUserAttacking) {
                int toSwitch;
                do {
                    toSwitch = generateInteger(0, defender->partySize() - 1);
                } while ((*defender)[toSwitch].isFainted());

                int option = 0;
                bool print = true;

                reprint_1:
                Battle::displayHPBar();
                print ? printMessage("Your opponent is about to send out " + (*Battle::opponent)[toSwitch].getName() + ".\n") : printMessage("Your opponent is about to send out " + (*Battle::opponent)[0].getName() + ".\n", 0);
                if (print) pressEnter();
                print ? printMessage("Would you like to swap out?\n") : printMessage("Would you like to swap out?\n", 0);
                option == 0 ? std::cout << "   ->   Yes\n" : std::cout << "\tYes\n";
                option == 1 ? std::cout << "   ->   No" : std::cout << "\tNo";

                print = false;

                if (not chooseOption(option, 1)) {
                    goto reprint_1;
                }

                print = true;
                if (option == 0) {
                    reprint_2:
                    Battle::displayHPBar();
                    Battle::displayPokemon(option, print);

                    if (not chooseOption(option, Battle::player->partySize())) {
                        goto reprint_2;
                    }

                    if (option == 0) {
                        Battle::displayHPBar();
                        Battle::inBattleMessage();
                        goto reprint_2;
                    }
                    if ((*Battle::player)[0].isFainted()) {
                        Battle::displayHPBar();
                        (*Battle::player)[option].hpEmptyMessage();
                        pressEnter();
                        goto reprint_2;
                    }

                    if (option < Battle::player->partySize()) {
                        Battle::displayHPBar();
                        Battle::player->swapPokemon(0, option);
                        Battle::switchOutMessage(Battle::player, option);
                    }
                }
                Battle::opponent->swapPokemon(0, toSwitch);
            }
            else {
                SwitchOut(defender, true, keepPlaying);
            }
            switched = true;
        }
    }
}

// This function commences attacking of each Pokémon and takes into account who is faster.
// If a Pokémon is inflicted by a pre-attack status condition (paralysis, sleep, frozen), it cannot attack.
void Battle::PreStatus(int userMove, int opponentMove, bool isUserFaster, bool &keepPlaying) {
    auto hasStatusCondition = [](Status status) {
        return status == Status::PARALYSIS ? generateInteger(1, 4) == 1 : status == Status::FREEZE or status == Status::SLEEP;
    };

    bool skip = false;
    if (isUserFaster) {
        if (not hasStatusCondition((*Battle::player)[0].getStatus()))
            Action(Battle::player, Battle::opponent, userMove, skip, true, keepPlaying);
        else
            inflictedMessage((*Battle::player)[0]);

        if (not skip and keepPlaying) {
            if (not hasStatusCondition((*Battle::opponent)[0].getStatus()))
                Action(Battle::opponent, Battle::player, opponentMove, skip, false, keepPlaying);
            else
                inflictedMessage((*Battle::opponent)[0]);
        }
    }
    else {
        if (not hasStatusCondition((*Battle::opponent)[0].getStatus()))
            Action(opponent, Battle::player, opponentMove, skip, false, keepPlaying);
        else
            inflictedMessage((*Battle::opponent)[0]);

        if (not skip and keepPlaying) {
            if (not hasStatusCondition((*Battle::player)[0].getStatus()))
                Action(Battle::player, Battle::opponent, userMove, skip, true, keepPlaying);
            else
                inflictedMessage((*Battle::player)[0]);
        }
    }
}

// If a Pokémon is inflicted with a post-move status condition (burn, poison), it will take damage based on max HP.
void Battle::PostStatus(bool isUserFaster, bool &keepPlaying) {
    auto hasStatusCondition = [](Status status) {
        return status == Status::BURN or status == Status::POISON;
    };

    auto PostStatus = [&keepPlaying](Trainer *trainer, bool isUser) {
        takeDamage(trainer, static_cast<int>(lround((*trainer)[0].getMaxHp() * 0.0625)));
        inflictedMessage((*trainer)[0]);

        if (not *trainer) {
            if (isUser) {
                trainer->clearParty();
                winMessage();
            }
            else {
                loseMessage();
            }
            keepPlaying = false;
        }
        if ((*trainer)[0].isFainted())
            isUser ? SwitchOut(trainer, true, keepPlaying) : SwitchOut(trainer, false, keepPlaying);
    };

    if (isUserFaster) {
        // if Pokémon is inflicted with a post-move status condition...
        if (hasStatusCondition((*Battle::player)[0].getStatus()))
            PostStatus(Battle::player, true);

        // if Pokémon is inflicted with a post-move status condition...
        if (hasStatusCondition((*Battle::opponent)[0].getStatus()))
            PostStatus(Battle::opponent, false);
    }
    else {
        // if Pokémon is inflicted with a post-move status condition...
        if (hasStatusCondition((*Battle::opponent)[0].getStatus()))
            PostStatus(Battle::opponent, false);

        // if Pokémon is inflicted with a post-move status condition...
        if (hasStatusCondition((*Battle::player)[0].getStatus()))
            PostStatus(Battle::player, true);
    }
}

int Battle::chooseMove(bool &skip) {
    int move = 0;
    bool print = true;

    chooseMove:
    Battle::displayHPBar();
    Battle::displayMoves((*Battle::player)[0], move, print);

    if (not chooseOption(move, (*Battle::player)[0].numMoves())) {
        goto chooseMove;
    }

    // user chose to go back
    if (move == (*Battle::player)[0].numMoves()) {
        skip = true;
        return 0;
    }
    // if move chosen is out of PP...
    else if (not (*Battle::player)[0][move]) {
        attackErrorMessage();
        goto chooseMove;
    }
    else {
        return move;
    }
}

void Battle::chooseItem(bool &skip, bool isTrainerBattle, bool &keepPlaying) {
    int itemType = 0;
    int userItem = 0;
    bool print = true;

    auto resetVariables = [&itemType, &userItem, &print] {
        itemType = 0;
        userItem = 0;
        print = true;
    };

    chooseItemType:
    Battle::displayHPBar();
    displayBag(itemType, print);

    if (not chooseOption(itemType, 4))
        goto chooseItemType;

    // trainer chose HP/PP items
    switch (itemType) {
        case 0:
            print = true;

        chooseRestoreItem:
            Battle::displayHPBar();
            displayItems(Battle::player, itemType, userItem, print);

            if (not chooseOption(userItem, Battle::player->getNumItems(itemType)))
                goto chooseRestoreItem;

            if (userItem == Battle::player->getNumItems(itemType)) {
                resetVariables();
                goto chooseItemType;
            }

            // if trainer has at least 1 of the item selected...
            else if (Battle::player->getItem(itemType, userItem)) {
                int pokemon = 0;
                print = true;

                chooseRestorePokemon:
                Battle::displayHPBar();
                displayPokemon(pokemon, print);

                if (not chooseOption(pokemon, Battle::player->partySize()))
                    goto chooseRestorePokemon;

                if (pokemon == Battle::player->partySize()) {
                    resetVariables();
                    goto chooseRestoreItem;
                }
                // Pokémon's HP is already full
                else if ((*Battle::player)[pokemon].isFullHP()) {
                    Battle::displayHPBar();
                    (*Battle::player)[pokemon].hpFullMessage();
                    pressEnter();
                    goto chooseRestorePokemon;
                }
                // Pokémon is fainted
                else if ((*Battle::player)[pokemon].isFainted()) {
                    Battle::displayHPBar();
                    (*Battle::player)[pokemon].hpEmptyMessage();
                    pressEnter();
                    goto chooseRestorePokemon;
                }
                // if Pokémon selected doesn't have full HP, but also isn't fainted...
                else {
                    // if item selected restores HP...
                    if (Battle::player->getItem(itemType, userItem).getRestoreType() == RestoreType::HP) {
                        Battle::displayHPBar();

                        Battle::player->getItem(itemType, userItem).use();
                        Battle::player->getItem(itemType, userItem).useMessage();

                        Battle::player->getItem(itemType, userItem).restore((*Battle::player)[pokemon]);
                        Battle::player->getItem(itemType, userItem).restoreMessage((*Battle::player)[pokemon]);
                    }
                    // if item selected restores PP...
                    else if (Battle::player->getItem(itemType, userItem).getRestoreType() == RestoreType::PP) {
                        int move = 0;
                        print = true;

                        choosePokemon:
                        Battle::displayHPBar();
                        Battle::displayMoves((*Battle::player)[pokemon], move, print);

                        if (not chooseOption(move, (*Battle::player)[0].numMoves()))
                            goto choosePokemon;

                        if (move == (*Battle::player)[0].numMoves())
                            goto chooseRestorePokemon;

                        else {
                            Battle::displayHPBar();

                            Battle::player->getItem(itemType, userItem).use();
                            Battle::player->getItem(itemType, userItem).useMessage();

                            Battle::player->getItem(itemType, userItem).restore((*Battle::player)[pokemon][move]);
                            Battle::player->getItem(itemType, userItem).restoreMessage((*Battle::player)[pokemon][move]);
                        }
                    }
                }
            }
            // trainer is out of selected item
            else {
                Battle::displayHPBar();
                itemErrorMessage(Battle::player->getItem(itemType, userItem));
                goto chooseRestoreItem;
            }
            break;

        case 1:
            print = true;

        chooseStatusItem:
            Battle::displayHPBar();
            displayItems(Battle::player, itemType, userItem, print);

            if (not chooseOption(userItem, Battle::player->getNumItems(itemType)))
                goto chooseStatusItem;

            if (userItem == Battle::player->getNumItems(itemType)) {
                resetVariables();
                goto chooseItemType;
            }

            // if trainer has at least 1 of the item selected...
            else if (Battle::player->getItem(itemType, userItem)) {
                int pokemon = 0;
                print = true;

                chooseStatusPokemon:
                Battle::displayHPBar();
                displayPokemon(pokemon, print);

                if (not chooseOption(pokemon, Battle::player->partySize())) {
                    goto chooseStatusPokemon;
                }

                if (pokemon == Battle::player->partySize()) {
                    resetVariables();
                    goto chooseStatusItem;
                }

                // if Pokémon is not fainted...
                else if (not (*Battle::player)[pokemon].isFainted()) {
                    // if Pokémon has status condition...
                    if ((*Battle::player)[pokemon].isAfflicted()) {
                        Battle::displayHPBar();

                        Battle::player->getItem(itemType, userItem).use();
                        Battle::player->getItem(itemType, userItem).useMessage();

                        Battle::player->getItem(itemType, userItem).restore((*Battle::player)[pokemon]);
                        Battle::player->getItem(itemType, userItem).restoreMessage((*Battle::player)[pokemon]);
                    }
                    // Pokémon did not have a status condition
                    else {
                        Battle::displayHPBar();

                        Battle::player->getItem(itemType, userItem).use();
                        noEffectMessage(Battle::player->getItem(itemType, userItem), (*Battle::player)[pokemon]);
                    }
                }
                // Pokémon is fainted
                else {
                    Battle::displayHPBar();
                    (*Battle::player)[pokemon - 1].hpEmptyMessage();
                    pressEnter();
                    goto chooseStatusPokemon;
                }
            }
            // trainer is out of selected item
            else {
                Battle::displayHPBar();
                itemErrorMessage(Battle::player->getItem(itemType, userItem));
                goto chooseStatusItem;
            }
            break;

        case 2:
            print = true;

        choosePokeball:
            Battle::displayHPBar();
            displayItems(Battle::player, itemType, userItem, print);

            if (not chooseOption(userItem, Battle::player->getNumItems(itemType)))
                goto choosePokeball;

            if (userItem == Battle::player->getNumItems(itemType)) {
                resetVariables();
                goto chooseItemType;
            }

            // if a trainer has at least one of the items selected...
            else if (Battle::player->getItem(itemType, userItem)) {
                if (isTrainerBattle) {
                    Battle::displayHPBar();
                    printMessage("You can't catch another trainer's Pokemon!");
                    pressEnter();
                    goto chooseItemType;
                }
                Battle::displayHPBar();

                Battle::player->getItem(itemType, userItem).use();
                Battle::player->getItem(itemType, userItem).useMessage();

                bool shakes[4];
                bool caught = catchPokemon(shakes);
                catchPokemonMessage((*Battle::opponent)[0], shakes);
                if (caught) {
                    keepPlaying = false;
                    return;
                }
            }
            // trainer is out of selected item
            else {
                Battle::displayHPBar();
                itemErrorMessage(Battle::player->getItem(itemType, userItem));
                goto choosePokeball;
            }
            break;

        case 3:
            print = true;

        chooseBattleItem:
            Battle::displayHPBar();
            displayItems(Battle::player, itemType, userItem, print);

            if (not chooseOption(userItem, Battle::player->getNumItems(itemType)))
                goto chooseBattleItem;

            if (userItem == Battle::player->getNumItems(itemType)) {
                resetVariables();
                goto chooseItemType;
            }

            // if trainer has at least 1 of the item selected...
            else if (Battle::player->getItem(itemType, userItem)) {
                Battle::displayHPBar();

                Battle::player->getItem(itemType, userItem).use();
                Battle::player->getItem(itemType, userItem).useMessage();

                bool limitReached = false;
                boostStat(&Battle::player->getItem(itemType, userItem), (*Battle::player)[0], 1, limitReached);
                boostMessage((*Battle::player)[0], Battle::player->getItem(itemType, userItem).getStat(), 1, limitReached);
            }
            // trainer is out of selected item
            else {
                Battle::displayHPBar();
                itemErrorMessage(Battle::player->getItem(itemType, userItem));
                goto chooseBattleItem;
            }
            break;

        default:
            skip = true;
            return;
    }
}

bool Battle::runAway(bool &skip, bool canRun) {
    Battle::displayHPBar();

    if (not canRun) {
        runErrorMessage();
        skip = true;
        return false;
    }
    else {
        //bool runAway = run();
        //FIXME commented out for testing purposes
        bool runAway = true;
        runMessage(runAway);

        return runAway;
    }
}

void Battle::choosePokemon(bool &skip) {
    int pokemon = 0;
    bool print = true;

    choosePokemon:
    Battle::displayHPBar();
    displayPokemon(pokemon, print);

    if (not chooseOption(pokemon, Battle::player->partySize()))
        goto choosePokemon;

    if (pokemon == Battle::player->partySize()) {
        skip = true;
        return;
    }

    int option = 0;
    print = true;

    chooseOption:
    Battle::displayHPBar();
    pokemonPrompt(option, print);

    if (not chooseOption(option, 2))
        goto chooseOption;

    int userMove;

    switch (option) {
        case 0:
            userMove = 0;
            print = true;

        chooseMove:
            Battle::displayHPBar();
            Battle::displayMoves((*Battle::player)[pokemon], userMove, print);

            if (not chooseOption(userMove, (*Battle::player)[pokemon].numMoves()))
                goto chooseMove;

            if (userMove == (*Battle::player)[pokemon].numMoves()) {
                option = 0;
                print = true;
                goto chooseOption;
            }

            Battle::displayHPBar();
            Battle::displayMoveSummary((*Battle::player)[pokemon][userMove]);
            pressEnter();

            userMove = 0;
            print = true;
            goto chooseMove;

        case 1:
            // trainer chose Pokémon currently in battle
            if (pokemon == 0) {
                Battle::displayHPBar();
                inBattleMessage();
                goto chooseOption;
            }
            else {
                // Pokémon chosen is not fainted
                if (not (*Battle::player)[pokemon].isFainted()) {
                    Battle::displayHPBar();
                    Battle::player->swapPokemon(0, pokemon);
                    switchOutMessage(Battle::player, pokemon);
                }
                // Pokémon chosen is fainted
                else {
                    Battle::displayHPBar();
                    (*Battle::player)[pokemon].hpEmptyMessage();
                    pressEnter();
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

void Battle::fight(int userMove, bool &keepPlaying) {
    Battle::displayHPBar();

    int opponentMove;
    // re-selects opponent move if it's out of PP
    do {
        opponentMove = generateInteger(0, (*Battle::opponent)[0].numMoves() - 1);
    } while (not (*Battle::opponent)[0][opponentMove]);

    bool skip = false;
    // if trainer chose to attack this turn...
    if (userMove != (*Battle::player)[0].numMoves()) {
        // if trainer is faster than opponent...
        if ((*Battle::player)[0].isFasterThan((*Battle::opponent)[0])) {
            PreStatus(userMove, opponentMove, true, keepPlaying);
            PostStatus(true, keepPlaying);
        }
        // if opponent is faster than trainer...
        else if ((*Battle::opponent)[0].isFasterThan((*Battle::player)[0])) {
            PreStatus(userMove, opponentMove, false, keepPlaying);
            PostStatus(false, keepPlaying);
        }
        // if trainer and opponent rival in speed; choose randomly
        else {
            if (coinFlip()) {
                PreStatus(userMove, opponentMove, true, keepPlaying);
                PostStatus(true, keepPlaying);
            }
            else {
                PreStatus(userMove, opponentMove, false, keepPlaying);
                PostStatus(false, keepPlaying);
            }
        }
    }
    // trainer chose not to attack this turn
    else {
        const Status status = (*Battle::opponent)[0].getStatus();
        if (not (status == Status::PARALYSIS ? generateInteger(1, 4) == 1 : status == Status::FREEZE or status == Status::SLEEP))
            Action(Battle::opponent, Battle::player, opponentMove, skip, false, keepPlaying);
        else
            inflictedMessage((*Battle::opponent)[0]);

        // if trainer is faster than opponent...
        if ((*Battle::player)[0].isFasterThan((*Battle::opponent)[0]))
            Battle::PostStatus(true, keepPlaying);

        // if opponent is faster than trainer...
        else if ((*Battle::opponent)[0].isFasterThan((*Battle::player)[0]))
            Battle::PostStatus(false, keepPlaying);

        // if trainer and opponent rival in speed; choose randomly
        else
            coinFlip() ? Battle::PostStatus(true, keepPlaying) : Battle::PostStatus(false, keepPlaying);
    }
    ++Battle::turn;
}

Battle::Battle(Player *trainer_1, Trainer *trainer_2) {
    Battle::player = trainer_1;
    Battle::opponent = trainer_2;

    Battle::engageBattle(false);
}

void Battle::engageBattle(bool isTrainer) {
    Battle::displayHPBar(false);
    Battle::introMessage();

    bool keepPlaying = true;

    while (keepPlaying) { // enters the battle
        int option = 0;
        bool print = true;

        reprint:
        Battle::displayHPBar();
        Battle::displayChoices(option, print);

        if (not chooseOption(option, 3))
            goto reprint;

        int userMove = (*Battle::player)[0].numMoves();    // passed into the fight to determine move used
        bool cancel = false;                               // passed into core four functions to know if to return

        chooseOption:
        switch (option) {
            case 0:
                userMove = Battle::chooseMove(cancel);
                break;
            case 1:
                Battle::chooseItem(cancel, isTrainer, keepPlaying);
                break;
            case 2:
                if (Battle::runAway(cancel, not isTrainer)) {
                    Battle::opponent->clearParty();
                    return;
                }
                break;
            case 3:
                Battle::choosePokemon(cancel);
                break;
            default:
                goto chooseOption;
        }

        if (not cancel)
            Battle::fight(userMove, keepPlaying);
    }
}
