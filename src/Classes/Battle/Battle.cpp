//
// Created by Miles on 10/1/2023.
//

#include "Battle.h"

static constexpr int NUM_TYPES = 18;

static constexpr std::array<std::array<double, NUM_TYPES>, NUM_TYPES> TYPE_CHART = {
        std::array<double, NUM_TYPES> { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 0.0, 1.0, 1.0, 0.5, 1.0 }, // normal
        std::array<double, NUM_TYPES> { 1.0, 0.5, 0.5, 1.0, 2.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 0.5, 1.0, 2.0, 1.0 }, // fire
        std::array<double, NUM_TYPES> { 1.0, 2.0, 0.5, 1.0, 0.5, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 1.0, 1.0 }, // water
        std::array<double, NUM_TYPES> { 1.0, 1.0, 2.0, 0.5, 0.5, 1.0, 1.0, 1.0, 0.0, 2.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0 }, // electric
        std::array<double, NUM_TYPES> { 1.0, 0.5, 2.0, 1.0, 0.5, 1.0, 1.0, 0.5, 2.0, 0.5, 1.0, 0.5, 2.0, 1.0, 0.5, 1.0, 0.5, 1.0 }, // grass
        std::array<double, NUM_TYPES> { 1.0, 0.5, 0.5, 1.0, 2.0, 0.5, 1.0, 1.0, 2.0, 2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0 }, // ice
        std::array<double, NUM_TYPES> { 2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 0.5, 0.5, 0.5, 2.0, 0.0, 1.0, 2.0, 2.0, 0.5 }, // fighting
        std::array<double, NUM_TYPES> { 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 0.5, 0.5, 1.0, 1.0, 1.0, 0.5, 0.5, 1.0, 1.0, 0.0, 2.0 }, // poison
        std::array<double, NUM_TYPES> { 1.0, 2.0, 1.0, 2.0, 0.5, 1.0, 1.0, 2.0, 1.0, 0.0, 1.0, 0.5, 2.0, 1.0, 1.0, 1.0, 2.0, 1.0 }, // ground
        std::array<double, NUM_TYPES> { 1.0, 1.0, 1.0, 0.5, 2.0, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 1.0, 1.0, 0.5, 1.0 }, // flying
        std::array<double, NUM_TYPES> { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 2.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0, 1.0, 0.0, 0.5, 1.0 }, // psychic
        std::array<double, NUM_TYPES> { 1.0, 0.5, 1.0, 1.0, 2.0, 1.0, 0.5, 0.5, 1.0, 0.5, 2.0, 1.0, 1.0, 0.5, 1.0, 2.0, 0.5, 0.5 }, // bug
        std::array<double, NUM_TYPES> { 1.0, 2.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 0.5, 2.0, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0 }, // rock
        std::array<double, NUM_TYPES> { 0.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 1.0 }, // ghost
        std::array<double, NUM_TYPES> { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 0.5, 0.0 }, // dragon
        std::array<double, NUM_TYPES> { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.5, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 2.0, 1.0, 0.5, 1.0, 0.5 }, // dark
        std::array<double, NUM_TYPES> { 1.0, 0.5, 0.5, 0.5, 1.0, 2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 1.0, 1.0, 1.0, 0.5, 2.0 }, // steel
        std::array<double, NUM_TYPES> { 1.0, 0.5, 1.0, 1.0, 1.0, 1.0, 2.0, 0.5, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 2.0, 2.0, 0.5, 1.0 }  // fairy
};

Player *Battle::player = nullptr;
Trainer *Battle::opponent = nullptr;
size_t Battle::turn = 0ULL;

bool Battle::skipPlayerTurn = false;
bool Battle::skipOpponentTurn = false;

void Battle::sendOutMessage(const Pokemon &pokemon, const bool isPlayer) {
    if (isPlayer) {
        printMessage("Go " + pokemon.getName() + "!\n");
    }
    else {
        printMessage("Your opponent sent out " + pokemon.getName() + "!\n");
    }
}

void Battle::returnMessage(const Pokemon &pokemon) {
    printMessage(pokemon.getName() + ", return! ");
}

void Battle::introMessage() {
    Battle::sendOutMessage((*Battle::opponent)[0], false);
    pressEnter();
    Battle::sendOutMessage((*Battle::player)[0], true);
    pressEnter();
}

void Battle::displayChoices(const int arrow, bool &print) {
    if (print) {
        printMessage("What will " + (*Battle::player)[0].getName() + " do?\n");
    }
    else {
        std:: cout << "What will " << (*Battle::player)[0] << " do?\n";
    }

    arrow == 0 ? std::cout << "   ->   Fight\n" : std::cout << "\tFight\n";
    arrow == 1 ? std::cout << "   ->   Bag\n" : std::cout << "\tBag\n";
    arrow == 2 ? std::cout << "   ->   Run\n" : std::cout << "\tRun\n";
    arrow == 3 ? std::cout << "   ->   Pokemon\n" : std::cout << "\tPokemon\n";

    std::cout.flush();

    print = false;
}

void Battle::displayPokemon(const int arrow, bool &print) {
    void (*printOut)(const char *, const int) = [](const char *string, const int index) -> void {
        std::cout << string << (*Battle::player)[index] << std::string(15 - (*Battle::player)[index].getName().length(), ' ')
                  << "(HP: " << (*Battle::player)[index].getHP() << std::string(3 - std::to_string((*Battle::player)[index].getHP()).length(), ' ')
                  << '/' << std::string(3 - std::to_string((*Battle::player)[index].getMaxHp()).length(), ' ') << (*Battle::player)[index].getMaxHp()
                  << ")\n";
    };

    if (print) {
        printMessage("Choose a Pokemon:\n");
    }
    else {
        std::cout << "Choose a Pokemon:\n";
    }

    for (int i = 0; i < Battle::player->partySize(); ++i) {
        if (arrow == i) {
            printOut("   ->   ", i);
        }
        else {
            printOut("        ", i);
        }
    }

    arrow == Battle::player->partySize() ? std::cout << "\n   ->   Cancel\n" : std::cout << "\n\tCancel\n";
    std::cout.flush();

    print = false;
}

void Battle::displayHPBar(const bool displayPokemon = true) {
    void (*printOut)(Trainer *) = [](Trainer *trainer) -> void {
        std::cout << "| " << (*trainer)[0] << std::string(15 - (*trainer)[0].getName().length(), ' ')
                  << "| HP: " << (*trainer)[0].getHP()
                  << std::string(3 - std::to_string((*trainer)[0].getHP()).length(), ' ')
                  << '/' << (*trainer)[0].getMaxHp()
                  << std::string(3 - std::to_string((*trainer)[0].getMaxHp()).length(), ' ')
                  << " |\n";
    };

    system("cls");
    std::cout << "Turn " << Battle::turn << '\n';

    if (displayPokemon) {
        std::cout << '+' << std::string(16, '-') << '+' << std::string(13, '-') << "+\n"; // top layer
        printOut(Battle::player);

        std::cout << '+' << std::string(16, '-') << '+' << std::string(13, '-') << "+\n"; // middle layer
        printOut(Battle::opponent);
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

void Battle::forcedSwitchPrompt(const int arrow, bool &print) {
    if (print) {
        printMessage("Choose an option:\n");
    }
    else {
        std::cout << "Choose an option:\n";
    }

    arrow == 0 ? std::cout << "   ->   Fight\n" : std::cout << "\tFight\n";
    arrow == 1 ? std::cout << "   ->   Run" : std::cout << "\tRun";

    print = false;
    std::cout.flush();
}

auto Battle::run() -> bool {
    const int opponentSpeed = ((*Battle::opponent)[0].getBaseSpeed() / 4) % 256;
    const int odds = (((*Battle::player)[0].getBaseSpeed() * 32) / opponentSpeed) + 30;

    return opponentSpeed == 0 or odds > 255 or generateInteger(0, 255) < odds;
}

void Battle::runMessage(const bool runStatus) {
    runStatus ? printMessage("Got away safely!\n") : printMessage("Couldn't get away!\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void Battle::runErrorMessage() {
    printMessage("You can't run away from a trainer battle!");
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void Battle::pokemonPrompt(const int arrow, bool &print) {
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

void Battle::switchOutMessage(const Trainer *trainer, const int pokemonSwitched) {
    Battle::returnMessage((*trainer)[pokemonSwitched]);
    pressEnter();
    Battle::sendOutMessage((*trainer)[0], true);
    pressEnter();
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
    switch (pokemon.getStatus()) {
        case Status::BURN:
            printMessage(pokemon.getName() + " took " + std::to_string(static_cast<int>(lround(pokemon.getMaxHp() * 0.0625))) + " damage from it's burn!\n");
            break;
        case Status::PARALYSIS:
            printMessage(pokemon.getName() + " is paralyzed! It can't move!\n");
            break;
        case Status::FREEZE:
            printMessage(pokemon.getName() + " is frozen solid!\n");
            break;
        case Status::POISON:
            printMessage(pokemon.getName() + " took " + std::to_string(static_cast<int>(lround(pokemon.getMaxHp() * 0.0625))) + " damage from it's poisoning!\n");
            break;
        case Status::SLEEP:
            printMessage(pokemon.getName() + " is fast asleep!\n");
            break;
        default:
            throw std::runtime_error("Unexpected error: function inflictedMessage");
    }

    pressEnter();
}

void Battle::displayMoves(const Pokemon &pokemon, const int arrow, bool &print) {
    const auto printOut = [&pokemon](const char *string, int index) -> void {
        std::cout << string << pokemon[index] << std::string(15 - pokemon[index].getName().length(), ' ')
                  << " (PP: " << pokemon[index].getPP() << std::string(2 - std::to_string(pokemon[index].getPP()).length(), ' ')
                  << '/' << std::string(2 - std::to_string(pokemon[index].getMaxPP()).length(), ' ') << pokemon[index].getMaxPP()
                  << ")\n";
    };

    if (print) {
        printMessage("Choose a move:\n");
    }
    else {
        std::cout << "Choose a move:\n";
    }

    for (int i = 0; i < pokemon.numMoves(); ++i) {
        if (arrow == i) {
            printOut("   ->   ", i);
        }
        else {
            printOut("        ", i);
        }
    }

    arrow == pokemon.numMoves() ? std::cout << "\n   ->   Cancel\n" : std::cout << "\n\tCancel\n";
    std::cout.flush();

    print = false;
}

void Battle::displayMoveSummary(const Move &move) {
    std::cout << move << '\n';
    std::cout << "\tType:     " << move.getTypeAsString() << '\n';
    std::cout << "\tCategory: " << move.getCategoryAsString() << '\n';
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

// generates a random number between 1 and 16, inclusive
// returns true and 2.0 if that number is 1 and 1.0 and false otherwise
auto Battle::criticalHit() -> std::pair<double, bool> {
    return generateInteger(1, 16) == 1 ? std::make_pair(2.0, true) : std::make_pair(1.0, false);
}

// returns 1.5 if move is a STAB move, and 1.0 otherwise
auto Battle::stabCheck(const Pokemon &pokemon, const Move &move) -> double {
    return pokemon.getType(true) == move.getType() or pokemon.getType(false) == move.getType() ? 1.5 : 1.0;
}

auto Battle::checkType(const Move &move, const Pokemon &pokemon) -> double {
    const int moveType = static_cast<int>(move.getType()) - 1;
    const double type_1 = TYPE_CHART.at(moveType).at(static_cast<int>(pokemon.getType(true)) - 1);

    double type_2;
    if (pokemon.getType(false) == Type::NONE) {
        type_2 = 1.0;
    }
    else {
        type_2 = TYPE_CHART.at(moveType).at(static_cast<int>(pokemon.getType(false)) - 1);
    }

    return type_1 * type_2;
}

auto Battle::calculateDamage(const Pokemon &attackingPokemon, const Pokemon &defendingPokemon, const Move &move, bool &crit) -> int {
    int initialDamage = 0;

    const int levelCalc = (2 * attackingPokemon.getLevel() / 5) + 2;
    if (move.getCategory() == Category::PHYSICAL) {
        initialDamage = attackingPokemon.getBaseAttack() * move.getDamage() / defendingPokemon.getBaseDefense();
    }
    else if (move.getCategory() == Category::SPECIAL) {
        initialDamage = levelCalc * attackingPokemon.getBaseSpAttack() * move.getDamage() / defendingPokemon.getBaseSpDefense();
    }

    const int finalDamage = (initialDamage / 50) + 2;
    const std::pair<double, bool> c = criticalHit();
    crit = c.second;

    //FIXME recalculate damage
    return static_cast<int>(finalDamage * stabCheck(attackingPokemon, move) * checkType(move, defendingPokemon) * c.first);
}

void Battle::SwitchOut(Trainer *trainer, const bool isUser, bool &keepPlaying) {
    Battle::displayHPBar();
    int toSwitch = 0;

    if (isUser) {
        bool print = true;

        while (true) {
            forcedSwitchPrompt(toSwitch, print);
            if (chooseOption(toSwitch, 2)) {
                break;
            }
        }

        // player attempts to run
        //FIXME does not take into account trainer battle
        if (toSwitch == 1) {
            const bool runSuccess = run();
            Battle::runMessage(runSuccess);
            if (runSuccess) {
                keepPlaying = false;
                return;
            }
        }

        print = true;

        while (true) {
            displayPokemon(toSwitch, print);

            if (not chooseOption(toSwitch, Battle::player->partySize())) {
                continue;
            }

            if ((*trainer)[toSwitch].isFainted()) {
                (*trainer)[toSwitch - 1].hpEmptyMessage();
                pressEnter();
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

void Battle::Action(Trainer *attacker, Trainer *defender, const int move, bool &switched, const bool isUserAttacking, bool &keepPlaying) {
    bool &skip = isUserAttacking ? Battle::skipOpponentTurn : Battle::skipPlayerTurn;
    bool crit = false;
    const int dmg = calculateDamage((*attacker)[0], (*defender)[0], (*attacker)[0][move], crit);

    (*attacker)[0][move].action((*attacker)[0], (*defender)[0], dmg, skip);
    (*attacker)[0][move].actionMessage((*attacker)[0], (*defender)[0], dmg, skip,
                                       crit, checkType((*attacker)[0][move], (*defender)[0]));

    if ((*defender)[0].isFainted()) {
        defender->incFaintCount();
        faintMessage((*defender)[0]);

        int toSwitch = 0;
        while (((*defender)[toSwitch].isFainted() and defender->partySize() - 1 != 0)) {
            toSwitch = generateInteger(0, defender->partySize() - 1);
        }

        // FIXME find a way to swap afterward because the HP Bar is inaccurate
        Battle::opponent->swapPokemon(0, toSwitch);
        Battle::opponent->removePokemon(toSwitch);

        if (not defender->canFight()) {
            Battle::displayHPBar(false);
            if (isUserAttacking) {
                for (int i = 0; i < Battle::player->partySize(); ++i) {
                    (*Battle::player)[i].resetStatMods();
                }
                Battle::winMessage();
            }
            else {
                Battle::loseMessage();
            }
            keepPlaying = false;
        }
        else {
            if (isUserAttacking) {
                int option = 0;
                bool print = true;

                reprint_1:
                Battle::displayHPBar();

                if (print) {
                    printMessage("Your opponent is about to send out " + (*Battle::opponent)[0].getName() + ".\n");
                }
                else {
                    std::cout << "Your opponent is about to send out " << (*Battle::opponent)[0] << ".\n";
                }

                if (print) {
                    pressEnter();
                }

                if (print) {
                    printMessage("Would you like to swap out?\n");
                }
                else {
                    std::cout << "Would you like to swap out?\n";
                }

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
                        Battle::sendOutMessage((*Battle::opponent)[0], false);
                    }
                }
            }
            else {
                Battle::SwitchOut(defender, true, keepPlaying);
            }
            switched = true;
        }
    }
}

// This function commences attacking of each Pokémon and takes into account who is faster.
// If a Pokémon is inflicted by a pre-attack status condition (paralysis, sleep, frozen), it cannot attack.
void Battle::PreStatus(const int userMove, const int opponentMove, const bool isUserFaster, bool &keepPlaying) {
    bool (*hasStatusCondition)(const Status) = [](const Status status) -> bool {
        return status == Status::PARALYSIS ? generateInteger(1, 4) == 1 : status == Status::FREEZE or status == Status::SLEEP;
    };

    const auto userAction = [&userMove, &hasStatusCondition, &keepPlaying] -> void {
        if (userMove < (*Battle::player)[0].numMoves()) {
            if (not hasStatusCondition((*Battle::player)[0].getStatus())) {
                Battle::Action(Battle::player, Battle::opponent, userMove, Battle::skipOpponentTurn, true, keepPlaying);
            }
            else {
                inflictedMessage((*Battle::player)[0]);
            }
        }
    };

    const auto opponentAction = [&opponentMove, &hasStatusCondition, &keepPlaying] -> void {
        if (not hasStatusCondition((*Battle::opponent)[0].getStatus())) {
            Battle::Action(Battle::opponent, Battle::player, opponentMove, Battle::skipPlayerTurn, false, keepPlaying);
        }
        else {
            inflictedMessage((*Battle::opponent)[0]);
        }
    };

    if (isUserFaster) {
        userAction();

        if (not Battle::skipOpponentTurn and keepPlaying) {
            opponentAction();
        }

        Battle::skipOpponentTurn = false;

    }
    else {
        opponentAction();

        if (not Battle::skipPlayerTurn and keepPlaying) {
            userAction();
        }

        Battle::skipPlayerTurn = false;

    }
}

// If a Pokémon is inflicted with a post-move status condition (burn, poison), it will take damage based on max HP.
void Battle::PostStatus(const bool isUserFaster, bool &keepPlaying) {
    if (not keepPlaying) {
        return;
    }

    bool (*hasStatusCondition)(Status) = [](Status status) -> bool {
        return status == Status::BURN or status == Status::POISON;
    };

    auto PostStatus = [&keepPlaying](Trainer *trainer, bool isUser) {
        (*trainer)[0].takeDamage(static_cast<int>(lround((*trainer)[0].getMaxHp() * 0.0625)));
        inflictedMessage((*trainer)[0]);

        if ((*trainer)[0].isFainted()) {
            (*trainer).incFaintCount();
            faintMessage((*trainer)[0]);
        }

        if (not *trainer) {
            Battle::displayHPBar(false);
            if (isUser) {
                for (int i = 0; i < Battle::player->partySize(); ++i) {
                    (*Battle::player)[i].resetStatMods();
                }
                Battle::winMessage();
            }
            else {
                Battle::loseMessage();
            }
            keepPlaying = false;
        }
        if ((*trainer)[0].isFainted()) {
            isUser ? Battle::SwitchOut(trainer, true, keepPlaying) : Battle::SwitchOut(trainer, false, keepPlaying);
        }
    };

    if (isUserFaster) {
        // if Pokémon is inflicted with a post-move status condition...
        if (hasStatusCondition((*Battle::player)[0].getStatus())) {
            PostStatus(Battle::player, true);
        }

        // if Pokémon is inflicted with a post-move status condition...
        if (hasStatusCondition((*Battle::opponent)[0].getStatus())) {
            PostStatus(Battle::opponent, false);
        }
    }
    else {
        // if Pokémon is inflicted with a post-move status condition...
        if (hasStatusCondition((*Battle::opponent)[0].getStatus())) {
            PostStatus(Battle::opponent, false);
        }

        // if Pokémon is inflicted with a post-move status condition...
        if (hasStatusCondition((*Battle::player)[0].getStatus())) {
            PostStatus(Battle::player, true);
        }
    }
}

auto Battle::chooseMove(bool &skip) -> int {
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
    if (not (*Battle::player)[0][move]) {
        attackErrorMessage();
        goto chooseMove;
    }

    return move;

}

void Battle::chooseItem(bool &skip, const bool isTrainerBattle, bool &keepPlaying) {
    int userType = 0;
    int userItem = 0;
    bool print = true;

    const auto resetVariables = [&userType, &userItem, &print] -> void {
        userType = 0;
        userItem = 0;
        print = true;
    };

    chooseItemType:
    Battle::displayHPBar();
    displayBag(userType, print);

    if (not chooseOption(userType, 4)) {
        goto chooseItemType;
    }

    // trainer chose HP/PP items
    switch (userType) {
        case 0:
            print = true;

        chooseRestoreItem:
            Battle::displayHPBar();
            displayItems(Battle::player, userType, userItem, print);

            if (not chooseOption(userItem, Battle::player->getNumItems(userType))) {
                goto chooseRestoreItem;
            }

            if (userItem == Battle::player->getNumItems(userType)) {
                resetVariables();
                goto chooseItemType;
            }

            // if trainer has at least 1 of the item selected...
            else if (Battle::player->getItem(userType, userItem)) {
                int pokemon = 0;
                print = true;

                chooseRestorePokemon:
                Battle::displayHPBar();
                displayPokemon(pokemon, print);

                if (not chooseOption(pokemon, Battle::player->partySize())) {
                    goto chooseRestorePokemon;
                }

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
                    if (Battle::player->getItem(userType, userItem).getRestoreType() == RestoreType::HP) {
                        Battle::displayHPBar();

                        Battle::player->getItem(userType, userItem).use();
                        Battle::player->getItem(userType, userItem).useMessage();

                        Battle::player->getItem(userType, userItem).restore((*Battle::player)[pokemon]);
                        Battle::player->getItem(userType, userItem).restoreMessage((*Battle::player)[pokemon]);

                        // automatically removes the item if it's quantity is now 0
                        if (not Battle::player->getItem(userType, userItem)) {
                            Battle::player->removeItem(userType, userItem);
                        }
                    }
                    // if item selected restores PP...
                    else if (Battle::player->getItem(userType, userItem).getRestoreType() == RestoreType::PP) {
                        int move = 0;
                        print = true;

                        choosePokemon:
                        Battle::displayHPBar();
                        Battle::displayMoves((*Battle::player)[pokemon], move, print);

                        if (not chooseOption(move, (*Battle::player)[0].numMoves())) {
                            goto choosePokemon;
                        }

                        if (move == (*Battle::player)[0].numMoves()) {
                            goto chooseRestorePokemon;
                        }
                        else {
                            Battle::displayHPBar();

                            Battle::player->getItem(userType, userItem).use();
                            Battle::player->getItem(userType, userItem).useMessage();

                            Battle::player->getItem(userType, userItem).restore((*Battle::player)[pokemon][move]);
                            Battle::player->getItem(userType, userItem).restoreMessage((*Battle::player)[pokemon][move]);

                            // automatically removes the item if it's quantity is now 0
                            if (not Battle::player->getItem(userType, userItem)) {
                                Battle::player->removeItem(userType, userItem);
                            }
                        }
                    }
                }
            }
            break;

        case 1:
            print = true;

        chooseStatusItem:
            Battle::displayHPBar();
            displayItems(Battle::player, userType, userItem, print);

            if (not chooseOption(userItem, Battle::player->getNumItems(userType))) {
                goto chooseStatusItem;
            }

            if (userItem == Battle::player->getNumItems(userType)) {
                resetVariables();
                goto chooseItemType;
            }

            // if trainer has at least 1 of the item selected...
            else if (Battle::player->getItem(userType, userItem)) {
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

                        Battle::player->getItem(userType, userItem).use();
                        Battle::player->getItem(userType, userItem).useMessage();
                        pressEnter();

                        Battle::player->getItem(userType, userItem).restore((*Battle::player)[pokemon]);
                        Battle::player->getItem(userType, userItem).restoreMessage((*Battle::player)[pokemon]);
                        pressEnter();

                        // automatically removes the item if it's quantity is now 0
                        if (not Battle::player->getItem(userType, userItem)) {
                            Battle::player->removeItem(userType, userItem);
                        }
                    }
                    // Pokémon did not have a status condition
                    else {
                        Battle::displayHPBar();

                        Battle::player->getItem(userType, userItem).use();
                        noEffectMessage(Battle::player->getItem(userType, userItem), (*Battle::player)[pokemon]);

                        // automatically removes the item if it's quantity is now 0
                        if (not Battle::player->getItem(userType, userItem)) {
                            Battle::player->removeItem(userType, userItem);
                        }
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
            break;

        case 2:
            print = true;

        choosePokeball:
            Battle::displayHPBar();
            displayItems(Battle::player, userType, userItem, print);

            if (not chooseOption(userItem, Battle::player->getNumItems(userType))) {
                goto choosePokeball;
            }

            if (userItem == Battle::player->getNumItems(userType)) {
                resetVariables();
                goto chooseItemType;
            }

            // if a trainer has at least one of the items selected...
            else if (Battle::player->getItem(userType, userItem)) {
                if (isTrainerBattle) {
                    Battle::displayHPBar();
                    printMessage("You can't catch another trainer's Pokemon!");
                    pressEnter();
                    goto chooseItemType;
                }
                Battle::displayHPBar();

                Battle::player->getItem(userType, userItem).use();
                Battle::player->getItem(userType, userItem).useMessage();

                // automatically removes the item if it's quantity is now 0
                if (not Battle::player->getItem(userType, userItem)) {
                    Battle::player->removeItem(userType, userItem);
                }

                std::array<bool, 4> shakes{};
                const bool caught = Battle::player->getItem(userType, userItem).catchPokemon((*Battle::opponent)[0], shakes);
                catchPokemonMessage((*Battle::opponent)[0], shakes);
                if (caught) {
                    keepPlaying = false;
                    return;
                }
            }
            break;

        case 3:
            print = true;

        chooseBattleItem:
            Battle::displayHPBar();
            displayItems(Battle::player, userType, userItem, print);

            if (not chooseOption(userItem, Battle::player->getNumItems(userType))) {
                goto chooseBattleItem;
            }

            if (userItem == Battle::player->getNumItems(userType)) {
                resetVariables();
                goto chooseItemType;
            }

            // if trainer has at least 1 of the item selected...
            else if (Battle::player->getItem(userType, userItem)) {
                Battle::displayHPBar();

                Battle::player->getItem(userType, userItem).use();
                Battle::player->getItem(userType, userItem).useMessage();

                bool limitReached = false;
                boostStat(&Battle::player->getItem(userType, userItem), (*Battle::player)[0], 2, limitReached);
                boostMessage((*Battle::player)[0], Battle::player->getItem(userType, userItem).getStat(), 2, limitReached);

                // automatically removes the item if it's quantity is now 0
                if (not Battle::player->getItem(userType, userItem)) {
                    Battle::player->removeItem(userType, userItem);
                }
            }
            break;

        default:
            skip = true;
            return;
    }
}

auto Battle::runAway(bool &skip, const bool canRun) -> bool {
    Battle::displayHPBar();

    if (not canRun) {
        runErrorMessage();
        skip = true;
        return false;
    }
    //bool runAway = run();
    //FIXME commented out for testing purposes
    const bool runAway = true;
    Battle::runMessage(runAway);

    return runAway;
}

void Battle::choosePokemon(bool &skip) {
    int pokemon = 0;
    bool print = true;

    choosePokemon:
    Battle::displayHPBar();
    displayPokemon(pokemon, print);

    if (not chooseOption(pokemon, Battle::player->partySize())) {
        goto choosePokemon;
    }

    if (pokemon == Battle::player->partySize()) {
        skip = true;
        return;
    }

    int option = 0;
    print = true;

    chooseOption:
    Battle::displayHPBar();
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
            Battle::displayHPBar();
            Battle::displayMoves((*Battle::player)[pokemon], userMove, print);

            if (not chooseOption(userMove, (*Battle::player)[pokemon].numMoves())) {
                goto chooseMove;
            }

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

void Battle::fight(const int userMove, bool &keepPlaying) {
    Battle::displayHPBar();

    int opponentMove = 0;
    if (not (*Battle::opponent)[0].canAttack()) {
        // TODO add struggle
        throw std::runtime_error("Struggle not implemented yet");
    }
    // re-selects opponent move if it's out of PP
    opponentMove = generateInteger(0, (*Battle::opponent)[0].numMoves() - 1);
    while (not(*Battle::opponent)[0][opponentMove]) {
        opponentMove = generateInteger(0, (*Battle::opponent)[0].numMoves() - 1);
    }


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

    ++Battle::turn;
}

Battle::Battle(Player *trainer_1, Trainer *trainer_2) {
    Battle::player = trainer_1;
    Battle::opponent = trainer_2;

    Battle::engageBattle(false);
}

void Battle::engageBattle(const bool isTrainer) {
    Battle::displayHPBar(false);
    Battle::introMessage();

    ++Battle::turn;
    bool keepPlaying = true;

    while (keepPlaying) { // enters the battle
        int option = 0;
        bool print = true;

        reprint:
        Battle::displayHPBar();
        Battle::displayChoices(option, print);

        if (not chooseOption(option, 3)) {
            goto reprint;
        }

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
                    for (int i = 0; i < Battle::player->partySize(); ++i) {
                        (*Battle::player)[i].resetStatMods();
                    }
                    return;
                }
                break;
            case 3:
                Battle::choosePokemon(cancel);
                break;
            default:
                goto chooseOption;
        }

        if (not cancel) {
            Battle::fight(userMove, keepPlaying);
        }
    }
}
