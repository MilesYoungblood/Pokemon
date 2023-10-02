//
// Created by Miles on 10/1/2023.
//

#include "Battle.h"

Trainer * Battle::user = nullptr;
Trainer * Battle::opponent = nullptr;
size_t Battle::turn = 1ull;

void Battle::wildPokemonMessage(const Pokemon &pokemon) {
    printMessage("Your opponent sent out " + pokemon.getName() + "! ");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void Battle::sendOutMessage(const Pokemon &pokemon) {
    printMessage("Go " + pokemon.getName() + "!\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void Battle::returnMessage(const Pokemon &pokemon) {
    printMessage(pokemon.getName() + ", return! ");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void Battle::introMessage() {
    Battle::wildPokemonMessage((*Battle::opponent)[0]);
    Battle::sendOutMessage((*Battle::user)[0]);
}

void Battle::displayChoices(int arrow, bool &print) {
    if (print) {
        printMessage("What will " + (*Battle::user)[0].getName() + " do?\n");
    }
    else {
        std::cout << "What will " << (*Battle::user)[0] << " do?\n";
    }
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
    for (int i = 0; i < Battle::user->partySize(); ++i) {
        if (arrow == i) {
            std::cout << "   ->   " << (*Battle::user)[i] << std::string(15 - (*Battle::user)[i].getName().length(), ' ')
                      << "(HP: " << (*Battle::user)[i].getHP() << std::string(3 - std::to_string((*Battle::user)[i].getHP()).length(), ' ')
                      << '/' << std::string(3 - std::to_string((*Battle::user)[i].getMaxHp()).length(), ' ') << (*Battle::user)[i].getMaxHp()
                      << ")\n";
        }
        else {
            std::cout << '\t' << (*Battle::user)[i] << std::string(15 - (*Battle::user)[i].getName().length(), ' ')
                      << "(HP: " << (*Battle::user)[i].getHP() << std::string(3 - std::to_string((*Battle::user)[i].getHP()).length(), ' ')
                      << '/' << std::string(3 - std::to_string((*Battle::user)[i].getMaxHp()).length(), ' ') << (*Battle::user)[i].getMaxHp()
                      << ")\n";
        }
    }
    arrow == Battle::user->partySize() ? std::cout << "\n   ->   Cancel\n" : std::cout << "\n\tCancel\n";
    std::cout.flush();

    print = false;
}

void Battle::displayPokemon(const Trainer &t) {
    printMessage("Choose a Pokemon:\n");
    for (int i = 0; i < t.partySize(); ++i) {
        std::cout << '\t' << t[i] << std::string(15 - t[i].getName().length(), ' ')
                  << "(HP: " << t[i].getHP() << std::string(3 - std::to_string(t[i].getHP()).length(), ' ')
                  << '/' << t[i].getMaxHp() << std::string(3 - std::to_string(t[i].getMaxHp()).length(), ' ')
                  << ") -> " << i + 1 << '\n';
    }
    std::cout << "\nCancel (0)\n";
    std::cout.flush();
}

void Battle::displayHPBar(bool displayPokemon) {
    system("cls");
    std::cout << "Turn " << Battle::turn << '\n';

    if (displayPokemon) {
        std::cout << '+' << std::string(16, '-') << '+' << std::string(13, '-') << "+\n"; // top layer

        std::cout << "| " << (*Battle::user)[0] << std::string(15 - (*Battle::user)[0].getName().length(), ' ')
                  << "| HP: " << (*Battle::user)[0].getHP()
                  << std::string(3 - std::to_string((*Battle::user)[0].getHP()).length(), ' ')
                  << '/' << (*Battle::user)[0].getMaxHp()
                  << std::string(3 - std::to_string((*Battle::user)[0].getMaxHp()).length(), ' ')
                  << " |\n";

        std::cout << '+' << std::string(16, '-') << '+' << std::string(13, '-') << "+\n"; // middle layer

        std::cout << "| " << (*Battle::opponent)[0] << std::string(15 - (*Battle::opponent)[0].getName().length(), ' ')
                  << "| HP: " << (*Battle::opponent)[0].getHP()
                  << std::string(3 - std::to_string((*Battle::opponent)[0].getHP()).length(), ' ')
                  << '/' << (*Battle::opponent)[0].getMaxHp()
                  << std::string(3 - std::to_string((*Battle::user)[0].getMaxHp()).length(), ' ')
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

void Battle::forcedSwitchPrompt() {
    printMessage("Choose an option:\n");
    std::cout << "\tFight (f)\n";
    std::cout << "\tRun   (r)\n";
    std::cout.flush();
}

__attribute__((unused)) bool Battle::run(const Pokemon &trainer_1, const Pokemon &trainer_2) {
    return ((trainer_1.getBaseSpeed() * 32) / ((trainer_2.getBaseSpeed() / 4) % 256)) + 30;
}

bool Battle::run() {
    return generateInteger(0, 1) == 1;
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

void Battle::switchOutMessage(const Trainer &t, int pokemonSwitched) {
    Battle::returnMessage(t[pokemonSwitched]);
    Battle::sendOutMessage(t[0]);
}

void Battle::inBattleMessage() {
    printMessage((*Battle::user)[0].getName() + " is already in battle!\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

void Battle::hpEmptyMessage(const Pokemon &pokemon) {
    printMessage(pokemon.getName() + "'s HP is empty!\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

void Battle::hpFullMessage(const Pokemon &pokemon) {
    printMessage(pokemon.getName() + "'s HP is full!\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

void Battle::winMessage() {
    printMessage("Your opponent ran out of usable Pokemon! ");
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    printMessage("You won!\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

void Battle::loseMessage() {
    printMessage("You've run out of usable Pokemon! ");
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    printMessage("You blacked out!\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

bool Battle::preStatus(Status status) {
    return status == Status::PARALYSIS ? generateInteger(1, 4) == 1 : status == Status::FREEZE or status == Status::SLEEP;
}

bool Battle::postStatus(Status status) {
    return status == Status::BURN or status == Status::POISON;
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

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
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
    std::cout << move << '\n';
    std::cout << "\tType:     " << move.getType() << '\n';
    std::cout << "\tCategory: " << move.getCategory() << '\n';
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

void Battle::takeDamage(Trainer &t, int damage) {
    t[0].setHP(t[0].getHP() - damage);
    if (t[0].isFainted()) {
        t[0].faint();
        t.incFaintCount();
    }
}

void Battle::takeDamageMessage(const Pokemon &pokemon) {
    printMessage(pokemon.getName() + " took " + std::to_string(static_cast<int>(lround(pokemon.getMaxHp() * .0625))) + " damage from it's ");
    if (pokemon.getStatus() == Status::BURN)
        printMessage( "burn!\n");

    else if (pokemon.getStatus() == Status::POISON)
        printMessage("poisoning!\n");

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

int Battle::getPhysicalAttack(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, Move &move) {
    const int levelCalc = (2 * attackingPokemon.getLevel() / 5) + 2;
    return levelCalc * attackingPokemon.getBaseAttack() * move.getDamage() / defendingPokemon.getBaseDefense();
}

int Battle::getSpecialAttack(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, Move &move) {
    const int levelCalc = (2 * attackingPokemon.getLevel() / 5) + 2;
    return levelCalc * attackingPokemon.getBaseSpAttack() * move.getDamage() / defendingPokemon.getBaseSpDefense();
}

std::pair<double, bool> Battle::criticalHit() {
    if (generateInteger(1, 16) == 1) {
        return std::make_pair(2.0, true);
    }
    else {
        return std::make_pair(1.0, false);
    }
}

// returns 1.5 if move is a STAB move, and 1.0 otherwise
double Battle::stabCheck(const Pokemon &pokemon, const Move &move) {
    return pokemon.getType(true) == move.getType() or pokemon.getType(false) == move.getType() ? 1.5 : 1.0;
}

int Battle::calculateDamage(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, Move &move, bool &crit) {
    int initialDamage = 0;
    if (move.getCategory() == "physical")
        initialDamage = getPhysicalAttack(attackingPokemon, defendingPokemon, move);

    else if (move.getCategory() == "special")
        initialDamage = getSpecialAttack(attackingPokemon, defendingPokemon, move);

    const int finalDamage = (initialDamage / 50) + 2;
    const std::pair<double, bool> c = criticalHit();
    crit = c.second;

    //FIXME recalculate damage
    return static_cast<int>(finalDamage * stabCheck(attackingPokemon, move) * getTypeEffective(move, defendingPokemon) * c.first);
}

void Battle::SwitchOut(Trainer &trainer, bool isUser, bool &keepPlaying) {
    displayHPBar(true);
    int toSwitch;

    if (isUser) {
        forcedSwitchPrompt();

        if (getChar({ 'f', 'r' }) == 'r') {
            //FIXME consider trainer battle
            bool runSuccess = run();
            runMessage(runSuccess);
            if (runSuccess) {
                keepPlaying = false;
                return;
            }
        }

        while (true) {
            displayPokemon(trainer);
            toSwitch = getInt(2, trainer.partySize());

            //FIXME might be a bug
            if (trainer[toSwitch - 1].isFainted())
                hpEmptyMessage(trainer[toSwitch - 1]);

            else
                break;
        }
    }

    else {
        do {
            toSwitch = generateInteger(0, trainer.partySize() - 1);
        } while (trainer[toSwitch].isFainted());
    }

    trainer.swapPokemon(0, toSwitch);
    sendOutMessage(trainer[0]);
}

void Battle::Action(Trainer &attacker, Trainer &defender, int move, bool &switched, bool isUserAttacking, bool &keepPlaying) {
    bool crit = false;
    const int damage = calculateDamage(attacker[0], defender[0], attacker[0][move], crit);

    attacker[0][move].action(attacker[0], defender[0], damage);
    attacker[0][move].actionMessage(attacker[0], defender[0], damage, crit, getTypeEffective(attacker[0][move], defender[0]));

    if (defender[0].isFainted()) {
        defender[0].faint();
        defender.incFaintCount();
        faintMessage(defender[0]);
        if (not defender.canFight()) {
            defender.defeat();
            displayHPBar(true);
            isUserAttacking ? winMessage() : loseMessage();
            keepPlaying = false;
        }
        else {
            isUserAttacking ? SwitchOut(defender, false, keepPlaying) : SwitchOut(defender, true, keepPlaying);
            switched = true;
        }
    }
}

void Battle::PostStatus(Trainer &trainer, bool isUser, bool &keepPlaying) {
    takeDamage(trainer, static_cast<int>(lround(trainer[0].getMaxHp() * 0.0625)));
    takeDamageMessage(trainer[0]);

    if (not trainer.canFight()) {
        trainer.defeat();
        isUser ? loseMessage() : winMessage();
        keepPlaying = false;
    }
    if (trainer[0].isFainted())
        isUser ? SwitchOut(trainer, true, keepPlaying) : SwitchOut(trainer, false, keepPlaying);
}

// This function commences attacking of each Pokémon and takes into account who is faster.
// If a Pokémon is inflicted by a pre-attack status condition (paralysis, sleep, frozen), it cannot attack.
void Battle::PreStatus(int userMove, int opponentMove, bool isUserFaster, bool &keepPlaying) {
    bool skip = false;
    if (isUserFaster) {
        not preStatus((*Battle::user)[0].getStatus()) ? Action(*Battle::user, *Battle::opponent, userMove, skip, true, keepPlaying) : inflictedMessage((*Battle::user)[0]);

        if (not skip and keepPlaying)
            not preStatus((*Battle::opponent)[0].getStatus()) ? Action(*Battle::opponent, *Battle::user, opponentMove, skip, false, keepPlaying) : inflictedMessage((*Battle::opponent)[0]);
    }
    else {
        not preStatus((*Battle::opponent)[0].getStatus()) ? Action(*opponent, *Battle::user, opponentMove, skip, false, keepPlaying) : inflictedMessage((*Battle::opponent)[0]);

        if (not skip and keepPlaying)
            not preStatus((*Battle::user)[0].getStatus()) ? Action(*Battle::user, *Battle::opponent, userMove, skip, true, keepPlaying) : inflictedMessage((*Battle::user)[0]);
    }
}

// If a Pokémon is inflicted with a post-move status condition (burn, poison), it will take damage based on max HP.
void Battle::PostStatus(bool isUserFaster, bool &keepPlaying) {
    if (isUserFaster) {
        // if Pokémon is inflicted with a post-move status condition...
        if (postStatus((*Battle::user)[0].getStatus()))
            PostStatus(*Battle::user, true, keepPlaying);

        // if Pokémon is inflicted with a post-move status condition...
        if (postStatus((*Battle::opponent)[0].getStatus()))
            PostStatus(*Battle::opponent, false, keepPlaying);
    }
    else {
        // if Pokémon is inflicted with a post-move status condition...
        if (postStatus((*Battle::opponent)[0].getStatus()))
            PostStatus(*Battle::opponent, false, keepPlaying);

        // if Pokémon is inflicted with a post-move status condition...
        if (postStatus((*Battle::user)[0].getStatus()))
            PostStatus(*Battle::user, true, keepPlaying);
    }
}

int Battle::chooseMove(bool &skip) {
    int move = 0;
    bool print = true;

    chooseMove:
    displayHPBar(true);
    displayMoves((*Battle::user)[0], move, print);

    if (not chooseOption(move, (*Battle::user)[0].numMoves())) {
        goto chooseMove;
    }

    // user chose to go back
    if (move == (*Battle::user)[0].numMoves()) {
        skip = true;
        return 0;
    }
        // if move chosen is out of PP...
    else if (not (*Battle::user)[0][move]) {
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

    chooseItemType:
    displayHPBar(true);
    displayBag(itemType, print);

    if (not chooseOption(itemType, 4))
        goto chooseItemType;

    // trainer chose HP/PP items
    switch (itemType) {
        case 0:
            print = true;

        chooseRestoreItem:
            displayHPBar(true);
            displayItems(Battle::user, itemType, userItem, print);

            if (not chooseOption(userItem, Battle::user->getNumItems(itemType)))
                goto chooseRestoreItem;

            if (userItem == Battle::user->getNumItems(itemType)) {
                itemType = 0;
                userItem = 0;
                print = true;
                goto chooseItemType;
            }

            // if trainer has at least 1 of the item selected...
            else if (Battle::user->getItem(itemType, userItem)) {
                int pokemon = 0;
                print = true;

                chooseRestorePokemon:
                displayHPBar(true);
                displayPokemon(pokemon, print);

                if (not chooseOption(pokemon, Battle::user->partySize()))
                    goto chooseRestorePokemon;

                if (pokemon == Battle::user->partySize()) {
                    itemType = 0;
                    userItem = 0;
                    print = true;
                    goto chooseRestoreItem;
                }
                // Pokémon's HP is already full
                else if ((*Battle::user)[pokemon].isFullHP()) {
                    displayHPBar(true);
                    hpFullMessage((*Battle::user)[pokemon]);
                    goto chooseRestorePokemon;
                }
                // Pokémon is fainted
                else if ((*Battle::user)[pokemon].isFainted()) {
                    displayHPBar(true);
                    hpEmptyMessage((*Battle::user)[pokemon]);
                    goto chooseRestorePokemon;
                }
                // if Pokémon selected doesn't have full HP, but also isn't fainted...
                else {
                    // if item selected restores HP...
                    if (Battle::user->getItem(itemType, userItem).getRestoreType() == RestoreType::HP) {
                        displayHPBar(true);
                        useItem(Battle::user->getItem(itemType, userItem));
                        useItemMessage(Battle::user->getItem(itemType, userItem).getName());
                        HP::restore((*Battle::user)[pokemon], Battle::user->getItem(itemType, userItem).getAmount());
                        HP::restoreMessage((*Battle::user)[pokemon], Battle::user->getItem(itemType, userItem).getAmount());
                    }
                    // if item selected restores PP...
                    else if (Battle::user->getItem(itemType, userItem).getRestoreType() == RestoreType::PP) {
                        int move = 0;
                        print = true;

                        choosePokemon:
                        displayHPBar(true);
                        displayMoves((*Battle::user)[pokemon], move, print);
                        //int move = getInt(0, trainer_1[0].numMoves());

                        if (not chooseOption(move, (*Battle::user)[0].numMoves()))
                            goto choosePokemon;

                        if (move == (*Battle::user)[0].numMoves())
                            goto chooseRestorePokemon;

                        else {
                            displayHPBar(true);
                            useItem(Battle::user->getItem(itemType, userItem));
                            useItemMessage(Battle::user->getItem(itemType, userItem).getName());
                            PP::restore((*Battle::user)[pokemon][move], Battle::user->getItem(itemType, userItem).getAmount());
                            PP::restoreMessage((*Battle::user)[pokemon][move], Battle::user->getItem(itemType, userItem).getAmount());
                        }
                    }
                }
            }
            // trainer is out of selected item
            else {
                displayHPBar(true);
                itemErrorMessage(Battle::user->getItem(itemType, userItem));
                goto chooseRestoreItem;
            }
            break;

        case 1:
            print = true;

        chooseStatusItem:
            displayHPBar(true);
            displayItems(Battle::user, itemType, userItem, print);

            if (not chooseOption(userItem, Battle::user->getNumItems(itemType)))
                goto chooseStatusItem;

            if (userItem == Battle::user->getNumItems(itemType)) {
                itemType = 0;
                userItem = 0;
                print = true;
                goto chooseItemType;
            }

            // if trainer has at least 1 of the item selected...
            else if (Battle::user->getItem(itemType, userItem)) {
                int pokemon = 0;
                print = true;

                chooseStatusPokemon:
                displayHPBar(true);
                displayPokemon(pokemon, print);

                if (not chooseOption(pokemon, Battle::user->partySize())) {
                    pokemon = 0;
                    goto chooseStatusPokemon;
                }
                // if Pokémon is not fainted...
                else if (not (*Battle::user)[pokemon].isFainted()) {
                    // if Pokémon has status condition...
                    if ((*Battle::user)[pokemon].isAfflicted()) {
                        displayHPBar(true);
                        useItem(Battle::user->getItem(itemType, userItem));
                        useItemMessage(Battle::user->getItem(itemType, userItem).getName());
                        cure((*Battle::user)[pokemon], &Battle::user->getItem(itemType, userItem));
                        cureMessage((*Battle::user)[pokemon], Battle::user->getItem(itemType, userItem).getStatus());
                    }
                    // Pokémon did not have a status condition
                    else {
                        displayHPBar(true);
                        useItem(Battle::user->getItem(itemType, userItem));
                        noEffectMessage(Battle::user->getItem(itemType, userItem), (*Battle::user)[pokemon]);
                    }
                }
                // Pokémon is fainted
                else {
                    displayHPBar(true);
                    hpEmptyMessage((*Battle::user)[pokemon - 1]);
                    goto chooseStatusPokemon;
                }
            }
            // trainer is out of selected item
            else {
                displayHPBar(true);
                itemErrorMessage(Battle::user->getItem(itemType, userItem));
                goto chooseStatusItem;
            }
            break;

        case 2:
            print = true;

        choosePokeball:
            displayHPBar(true);
            displayItems(Battle::user, itemType, userItem, print);

            if (not chooseOption(userItem, Battle::user->getNumItems(itemType)))
                goto choosePokeball;

            if (userItem == Battle::user->getNumItems(itemType)) {
                itemType = 0;
                userItem = 0;
                print = true;
                goto chooseItemType;
            }

            // if a trainer has at least one of the items selected...
            else if (Battle::user->getItem(itemType, userItem)) {
                if (isTrainerBattle) {
                    displayHPBar(true);
                    printMessage("You cannot catch another trainer's Pokemon!");
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                    goto chooseItemType;
                }
                displayHPBar(true);
                useItem(Battle::user->getItem(itemType, userItem));
                useItemMessage(Battle::user->getItem(itemType, userItem).getName());

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
                displayHPBar(true);
                itemErrorMessage(Battle::user->getItem(itemType, userItem));
                goto choosePokeball;
            }
            break;

        case 3:
            print = true;

        chooseBattleItem:
            displayHPBar(true);
            displayItems(Battle::user, itemType, userItem, print);

            if (not chooseOption(userItem, Battle::user->getNumItems(itemType)))
                goto chooseBattleItem;

            if (userItem == Battle::user->getNumItems(itemType)) {
                itemType = 0;
                userItem = 0;
                print = true;
                goto chooseItemType;
            }

            // if trainer has at least 1 of the item selected...
            else if (Battle::user->getItem(itemType, userItem)) {
                displayHPBar(true);
                useItem(Battle::user->getItem(itemType, userItem));
                useItemMessage(Battle::user->getItem(itemType, userItem).getName());

                bool limitReached = false;
                boostStat(&Battle::user->getItem(itemType, userItem), (*Battle::user)[0], 1, limitReached);
                boostMessage((*Battle::user)[0], Battle::user->getItem(itemType, userItem).getStat(), 1, limitReached);
            }
            // trainer is out of selected item
            else {
                displayHPBar(true);
                itemErrorMessage(Battle::user->getItem(itemType, userItem));
                goto chooseBattleItem;
            }
            break;

        default:
            skip = true;
            return;
    }
}

bool Battle::runAway(bool &skip, bool canRun) {
    displayHPBar(true);

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

void Battle::choosePokemon(bool &skip) {
    int pokemon = 0;
    bool print = true;

    choosePokemon:
    displayHPBar(true);
    displayPokemon(pokemon, print);

    if (not chooseOption(pokemon, Battle::user->partySize()))
        goto choosePokemon;


    if (pokemon == Battle::user->partySize()) {
        skip = true;
        return;
    }

    int option = 0;
    print = true;

    chooseOption:
    displayHPBar(true);
    pokemonPrompt(option, print);

    if (not chooseOption(option, 2))
        goto chooseOption;

    int userMove;

    switch (option) {
        case 0:
            userMove = 0;
            print = true;

        chooseMove:
            displayHPBar(true);
            displayMoves((*Battle::user)[pokemon], userMove, print);

            if (not chooseOption(userMove, (*Battle::user)[pokemon].numMoves()))
                goto chooseMove;

            if (userMove == (*Battle::user)[pokemon].numMoves()) {
                option = 0;
                print = true;
                goto chooseOption;
            }

            displayHPBar(true);
            displayMoveSummary((*Battle::user)[pokemon][userMove]);
            std::cin.ignore();

            userMove = 0;
            print = true;
            goto chooseMove;

        case 1:
            // trainer chose Pokémon currently in battle
            if (pokemon == 0) {
                displayHPBar(true);
                inBattleMessage();
                goto chooseOption;
            }
            else {
                // Pokémon chosen is not fainted
                if (not (*Battle::user)[pokemon].isFainted()) {
                    displayHPBar(true);
                    Battle::user->swapPokemon(0, pokemon);
                    switchOutMessage((*Battle::user), pokemon);
                }
                    // Pokémon chosen is fainted
                else {
                    displayHPBar(true);
                    hpEmptyMessage((*Battle::user)[pokemon]);
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
    displayHPBar(true);
    int opponentMove = generateInteger(0, (*Battle::opponent)[0].numMoves() - 1);
    // re-selects opponent move if it's out of PP
    while (not (*Battle::opponent)[0][opponentMove])
        opponentMove = generateInteger(0, 3);

    bool skip = false;
    // if trainer chose to attack this turn...
    if (userMove != (*Battle::user)[0].numMoves()) {
        // if trainer is faster than opponent...
        if ((*Battle::user)[0].isFasterThan((*Battle::opponent)[0])) {
            PreStatus(userMove, opponentMove, true, keepPlaying);
            PostStatus(true, keepPlaying);
        }
            // if opponent is faster than trainer...
        else if ((*Battle::opponent)[0].isFasterThan((*Battle::user)[0])) {
            PreStatus(userMove, opponentMove, false, keepPlaying);
            PostStatus(false, keepPlaying);
        }
            // if trainer and opponent rival in speed; choose randomly
        else {
            if (generateInteger(0, 1) == 0) {
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
        not preStatus((*Battle::opponent)[0].getStatus()) ? Action(*Battle::opponent, *Battle::user, opponentMove, skip, false, keepPlaying) : inflictedMessage((*Battle::opponent)[0]);

        // if trainer is faster than opponent...
        if ((*Battle::user)[0].isFasterThan((*Battle::opponent)[0]))
            PostStatus(true, keepPlaying);

            // if opponent is faster than trainer...
        else if ((*Battle::opponent)[0].isFasterThan((*Battle::user)[0]))
            PostStatus(false, keepPlaying);

            // if trainer and opponent rival in speed; choose randomly
        else
            generateInteger(0, 1) == 1 ? PostStatus(true, keepPlaying) : PostStatus(false, keepPlaying);
    }
    ++Battle::turn;
}

Battle::Battle(Trainer *trainer_1, Trainer *trainer_2) {
    Battle::user = trainer_1;
    Battle::opponent = trainer_2;

    Battle::engageBattle(false);
}

void Battle::engageBattle(bool isTrainer) {
    displayHPBar(false);
    introMessage();

    bool keepPlaying = true;

    while (keepPlaying) { // enters the battle
        int option = 0;
        bool print = true;

        reprint:
        displayHPBar(true);
        displayChoices(option, print);

        // FIXME change 4 back to 3; only using 4 for testing purposes
        if (not chooseOption(option, 3))
            goto reprint;

        int userMove = (*Battle::user)[0].numMoves();    // passed into the fight to determine move used
        bool cancel = false;                    // passed into core four functions to know if to return

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
                    Battle::opponent->defeat();
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
