//
// Created by miles on 5/5/2022.
//

#pragma once

#include <unistd.h>
#include "Trainer.h"
#include "AttackFunctions.h"
#include "ItemFunctions.h"

void wildPokemonMessage(const Pokemon &pokemon) {
    printMessage("A wild " + pokemon.getName() + " appeared! ");
    sleep(1);
}

void sendOutMessage(const Pokemon &pokemon) {
    printMessage("Go " + pokemon.getName() + "!\n");
    sleep(1);
}

void returnMessage(const Pokemon &pokemon) {
    printMessage(pokemon.getName() + ", return! ");
    sleep(1);
}

void introMessage(const Pokemon &userPokemon, const Pokemon &opposingPokemon) {
    //std::cout << "\n\n\n\n\n\n\n";
    wildPokemonMessage(opposingPokemon);
    sendOutMessage(userPokemon);
}

void displayChoices(const Pokemon &pokemon) {
    printMessage("What will " + pokemon.getName() + " do?\n");
    std::cout << "\tFight   (f)\n";
    std::cout << "\tBag     (b)\n";
    std::cout << "\tRun     (r)\n";
    std::cout << "\tPokemon (p)\n";
    std::cout.flush();
}

void displayPokemon(const Trainer &t) {
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

void displayEmptyHP(size_t t) {
    std::cout << "Turn " << t << '\n';
    for (int i = 0; i < 2; ++i) {
        std::cout << '+' << std::string(16, '-') << '+' << std::string(13, '-') << "+\n";
        std::cout << '|' << std::string(16, ' ') << "|" << std::string(13, ' ') << "|\n";
    }
    std::cout << '+' << std::string(16, '-') << '+' << std::string(13, '-') << "+\n\n"; // bottom layer
    std::cout.flush();
}

void displayHP(const Pokemon &userPokemon, const Pokemon &opposingPokemon, size_t t) {
    std::cout << "Turn " << t << '\n';
    std::cout << '+' << std::string(16, '-') << '+' << std::string(13, '-') << "+\n"; // top layer

    std::cout << "| " << userPokemon << std::string(15 - userPokemon.getName().length(), ' ')
              << "| HP: " << userPokemon.getHP() << std::string(3 - std::to_string(userPokemon.getHP()).length(), ' ')
              << '/' << userPokemon.getMaxHp() << std::string(3 - std::to_string(userPokemon.getMaxHp()).length(), ' ')
              << " |\n";

    std::cout << '+' << std::string(16, '-') << '+' << std::string(13, '-') << "+\n"; // middle layer

    std::cout << "| " << opposingPokemon << std::string(15 - opposingPokemon.getName().length(), ' ')
              << "| HP: " << opposingPokemon.getHP() << std::string(3 - std::to_string(opposingPokemon.getHP()).length(), ' ')
              << '/' << opposingPokemon.getMaxHp() << std::string(3 - std::to_string(userPokemon.getMaxHp()).length(), ' ')
              <<  " |\n";

    std::cout << '+' << std::string(16, '-') << '+' << std::string(13, '-') << "+\n\n"; // bottom layer
    std::cout.flush();
}

void faintMessage(const Pokemon &pokemon) {
    printMessage(pokemon.getName() + " fainted!\n");
    sleep(2);
}

void forcedSwitchPrompt() {
    printMessage("Choose an option:\n");
    std::cout << "\tFight (f)\n";
    std::cout << "\tRun   (r)\n";
    std::cout.flush();
}

bool run(const Pokemon &trainer_1, const Pokemon &trainer_2) {
    return ((trainer_1.getBaseSpeed() * 32) / ((trainer_2.getBaseSpeed() / 4) % 256)) + 30 ;
}

bool run() {
    return generateInteger(0, 1) == 1;
}

void runMessage(bool runStatus) {
    runStatus ? printMessage("Got away safely!\n") : printMessage("Couldn't get away!\n");
    sleep(1);
}

void pokemonPrompt() {
    printMessage("Choose an option:\n");
    std::cout << "\tCheck Moves (c)\n";
    std::cout << "\tSwitch      (s)\n";
    std::cout << "\nCancel (0)\n";
    std::cout.flush();
}

void switchOut(Trainer &t, int pokemonToSwitch) {
    Pokemon copy = t[0];
    t[0] = t[pokemonToSwitch];
    t[pokemonToSwitch] = copy;
}

void switchOutMessage(const Trainer &t, int pokemonSwitched) {
    returnMessage(t[pokemonSwitched]);
    sendOutMessage(t[0]);
}

void inBattleMessage(const Pokemon &pokemon) {
    printMessage(pokemon.getName() + " is already in battle!\n");
    sleep(2);
}

void hpEmptyMessage(const Pokemon &pokemon) {
    printMessage(pokemon.getName() + "'s HP is empty!\n");
    sleep(2);
}

void hpFullMessage(const Pokemon &pokemon) {
    printMessage(pokemon.getName() + "'s HP is full!\n");
    sleep(2);
}

void winMessage() {
    printMessage("Your opponent ran out of usable Pokemon! ");
    sleep(2);
    printMessage("You won!\n");
    sleep(2);
}

void loseMessage() {
    printMessage("You've run out of usable Pokemon! ");
    sleep(2);
    printMessage("You blacked out!\n");
    sleep(2);
}

bool preStatus(const std::string& status) {
    return status == "paralysis" ? generateInteger(1, 4) == 1 : status == "freeze" or status == "sleep";
}

bool postStatus(const std::string& status) {
    return status == "burn" or status == "poison";
}

void inflictedMessage(const Pokemon& pokemon) {
    if (pokemon.getStatus() == "burn")
        printMessage(pokemon.getName() + " took " + std::to_string(static_cast<int>(pokemon.getMaxHp() * .065)) + " damage from it's burn!\n");

    else if (pokemon.getStatus() == "paralysis")
        printMessage(pokemon.getName() + " is paralyzed! It can't move!\n");

    else if (pokemon.getStatus() == "freeze")
        printMessage(pokemon.getName() + " is frozen solid!\n");

    else if (pokemon.getStatus() == "poison")
        printMessage(pokemon.getName() + " took " + std::to_string(static_cast<int>(pokemon.getMaxHp() * .0625)) + " damage from it's poisoning!\n");

    else if (pokemon.getStatus() == "sleep")
        printMessage(pokemon.getName() + " is fast asleep!\n");

    sleep(1);
}

void updateHP(const Pokemon &userPokemon, const Pokemon &opposingPokemon, int damage, size_t turn, bool userAttacking) {
    for (int i = 1; i <= damage; ++i) {
        system("cls");
        if (userAttacking) {
            std::cout << "Turn " << turn << '\n';
            std::cout << '+' << std::string(16, '-') << '+' << std::string(13, '-') << "+\n"; // top layer

            std::cout << "| " << userPokemon << std::string(15 - userPokemon.getName().length(), ' ')
                      << "| HP: " << userPokemon.getHP()
                      << std::string(3 - std::to_string(userPokemon.getHP()).length(), ' ')
                      << '/' << userPokemon.getMaxHp()
                      << std::string(3 - std::to_string(userPokemon.getMaxHp()).length(), ' ')
                      << " |\n";

            std::cout << '+' << std::string(16, '-') << '+' << std::string(13, '-') << "+\n"; // middle layer

            std::cout << "| " << opposingPokemon << std::string(15 - opposingPokemon.getName().length(), ' ')
                      << "| HP: " << opposingPokemon.getHP() - i
                      << std::string(3 - std::to_string(opposingPokemon.getHP()).length(), ' ')
                      << '/' << opposingPokemon.getMaxHp()
                      << std::string(3 - std::to_string(userPokemon.getMaxHp()).length(), ' ')
                      << " |\n";

            std::cout << '+' << std::string(16, '-') << '+' << std::string(13, '-') << "+\n\n"; // bottom layer
            std::cout.flush();
            Sleep(25);
        }
        else {
            std::cout << "Turn " << turn << '\n';
            std::cout << '+' << std::string(16, '-') << '+' << std::string(13, '-') << "+\n"; // top layer

            std::cout << "| " << userPokemon << std::string(15 - userPokemon.getName().length(), ' ')
                      << "| HP: " << userPokemon.getHP() - i
                      << std::string(3 - std::to_string(userPokemon.getHP()).length(), ' ')
                      << '/' << userPokemon.getMaxHp()
                      << std::string(3 - std::to_string(userPokemon.getMaxHp()).length(), ' ')
                      << " |\n";

            std::cout << '+' << std::string(16, '-') << '+' << std::string(13, '-') << "+\n"; // middle layer

            std::cout << "| " << opposingPokemon << std::string(15 - opposingPokemon.getName().length(), ' ')
                      << "| HP: " << opposingPokemon.getHP()
                      << std::string(3 - std::to_string(opposingPokemon.getHP()).length(), ' ')
                      << '/' << opposingPokemon.getMaxHp()
                      << std::string(3 - std::to_string(userPokemon.getMaxHp()).length(), ' ')
                      << " |\n";

            std::cout << '+' << std::string(16, '-') << '+' << std::string(13, '-') << "+\n\n"; // bottom layer
            std::cout.flush();
            Sleep(25);
        }
    }
}

struct battlePhase {
private:
    static void userSwitchOut(Trainer &trainer) {
        forcedSwitchPrompt();
        char userChoice = getChar({'f', 'r'});

        if (userChoice == 'r') {
            bool runSuccess = run();
            runMessage(runSuccess);
            if (runSuccess)
                exit(0);
        }

        int pokemon;
        while (true) {
            displayPokemon(trainer);
            pokemon = getInt(2, trainer.partySize());

            if (trainer[pokemon - 1].getHP() <= 0)
                hpEmptyMessage(trainer[pokemon - 1]);

            else
                break;
        }

        switchOut(trainer, pokemon - 1);
        sendOutMessage(trainer[0]);
    }

    static void opponentSwitchOut(Trainer &trainer) {
        int toSwitch = generateInteger(0, trainer.partySize() - 1);
        while (trainer[toSwitch].isFainted())
            toSwitch = generateInteger(0, trainer.partySize() - 1);

        switchOut(trainer, toSwitch);
        sendOutMessage(trainer[0]);
    }

    static void userAttack(Trainer &user, Trainer &opponent, int move, size_t t, bool &switched) {
        bool crit = false;
        int userDamage = calculateDamage(user[0], opponent[0], user[0][move - 1], crit);

        attack(opponent[0], user[0][move - 1], userDamage);
        attackMessage(user[0], opponent[0], move - 1, userDamage, crit);
        //updateHP(user[0], opponent[0], userDamage, t, true);

        if (opponent[0].isFainted()) { // if Pokémon's HP drops to zero...
            opponent[0].faint();
            opponent.incFaintCount();
            faintMessage(opponent[0]);
            if (not opponent.canFight()) {
                winMessage();
                exit(0);
            }
            else {
                opponentSwitchOut(opponent);
                switched = true;
            }
        }
    }

    static void userAttack(Trainer &user, Trainer &opponent, int move, size_t t) {
        bool crit = false;
        int userDamage = calculateDamage(user[0], opponent[0], user[0][move - 1], crit);

        attack(opponent[0], user[0][move - 1], userDamage);
        attackMessage(user[0], opponent[0], move - 1, userDamage, crit);
        //updateHP(user[0], opponent[0], userDamage, t, true);

        if (opponent[0].isFainted()) { // if Pokémon's HP drops to zero...
            opponent[0].faint();
            opponent.incFaintCount();
            faintMessage(opponent[0]);
            if (not opponent.canFight()) {
                winMessage();
                exit(0);
            }
            else
                opponentSwitchOut(opponent);
        }
    }

    static void opponentAttack(Trainer &opponent, Trainer &user, int move, size_t t, bool &switched) {
        bool crit = false;
        int opponentDamage = calculateDamage(opponent[0], user[0], opponent[0][move], crit);

        attack(user[0], opponent[0][move - 1], opponentDamage);
        attackMessage(opponent[0], user[0], move, opponentDamage, crit);
        //updateHP(user[0], opponent[0], opponentDamage, t, false);

        // if Pokémon's HP drops to zero...
        if (user[0].isFainted()) {
            user[0].faint();
            user.incFaintCount();
            faintMessage(user[0]);
            if (not user.canFight()) {
                loseMessage();
                exit(0);
            }
            else {
                userSwitchOut(user);
                switched = true;
            }
        }
    }

    static void opponentAttack(Trainer &opponent, Trainer &user, int move, size_t t) {
        bool crit = false;
        int opponentDamage = calculateDamage(opponent[0], user[0], opponent[0][move], crit);

        attack(user[0], opponent[0][move - 1], opponentDamage);
        attackMessage(opponent[0], user[0], move, opponentDamage, crit);
        //updateHP(user[0], opponent[0], opponentDamage, t, false);

        if (user[0].isFainted()) {
            user[0].faint();
            user.incFaintCount();
            faintMessage(user[0]);
            if (not user.canFight()) {
                loseMessage();
                exit(0);
            }
            else
                userSwitchOut(user);
        }
    }

    static void userPostStatus(Trainer &user) {
        // if Pokémon is inflicted with a post-move status condition...
        if (postStatus(user[0].getStatus())) {
            takeDamage(user, static_cast<int>(user[0].getMaxHp() * .0625));
            status::takeDamageMessage(user[0]);
            if (not user.canFight()) {
                loseMessage();
                exit(0);
            }
            else
                userSwitchOut(user);
        }
    }

    static void opponentPostStatus(Trainer &opponent) {
        takeDamage(opponent, static_cast<int>(opponent[0].getMaxHp() * .0625));
        status::takeDamageMessage(opponent[0]);
        if (not opponent.canFight()) {
            winMessage();
            exit(0);
        }
        else
            opponentSwitchOut(opponent);
    }

public:
    static void fight(Trainer &user, Trainer &opponent, int userMove, size_t t) {
        int opponentMove = generateInteger(0, 3);
        // re-selects opponent move if it's out of PP
        while (not opponent[0][opponentMove].canUse())
            opponentMove = generateInteger(0, 3);

        // if trainer chose to attack this turn...
        if (userMove != 0) {
            // if trainer is faster than opponent...
            if (user[0].isFasterThan(opponent[0])) {
                bool skip = false;
                not preStatus(user[0].getStatus()) ? userAttack(user, opponent, userMove, t, skip) : inflictedMessage(user[0]);

                if (not skip)
                    not preStatus(opponent[0].getStatus()) ? opponentAttack(opponent, user, opponentMove, t) : inflictedMessage(opponent[0]);

                // if Pokémon is inflicted with a post-move status condition...
                if (postStatus(user[0].getStatus()))
                    userPostStatus(user);
                // if Pokémon is inflicted with a post-move status condition...
                if (postStatus(opponent[0].getStatus()))
                    opponentPostStatus(opponent);
            }
            // if opponent is faster than trainer...
            else if (opponent[0].isFasterThan(user[0])) {
                bool skip = false;
                not preStatus(opponent[0].getStatus()) ? opponentAttack(opponent, user, opponentMove, t, skip) : inflictedMessage(opponent[0]);

                if (not skip)
                    not preStatus(user[0].getStatus()) ? userAttack(user, opponent, userMove, t) : inflictedMessage(user[0]);

                // if Pokémon is inflicted with a post-move status condition...
                if (postStatus(opponent[0].getStatus()))
                    opponentPostStatus(opponent);

                // if Pokémon is inflicted with a post-move status condition...
                if (postStatus(user[0].getStatus()))
                    userPostStatus(user);
            }
            // if trainer and opponent rival in speed; choose randomly
            else {
                if (generateInteger(0, 1) == 0) {
                    bool skip = false;
                    not preStatus(user[0].getStatus()) ? userAttack(user, opponent, userMove, t, skip) : inflictedMessage(user[0]);

                    if (not skip)
                        not preStatus(opponent[0].getStatus()) ? opponentAttack(opponent, user, opponentMove, t) : inflictedMessage(opponent[0]);

                    // if Pokémon is inflicted with a post-move status condition...
                    if (postStatus(user[0].getStatus()))
                        userPostStatus(user);

                    // if Pokémon is inflicted with a post-move status condition...
                    if (postStatus(opponent[0].getStatus()))
                        opponentPostStatus(opponent);
                }
                else {
                    bool skip = false;
                    not preStatus(opponent[0].getStatus()) ? opponentAttack(opponent, user, opponentMove, t, skip) : inflictedMessage(opponent[0]);

                    if (not skip)
                        not preStatus(user[0].getStatus()) ? userAttack(user, opponent, userMove, t) : inflictedMessage(user[0]);

                    // if Pokémon is inflicted with a post-move status condition...
                    if (postStatus(opponent[0].getStatus()))
                        opponentPostStatus(opponent);

                    // if Pokémon is inflicted with a post-move status condition...
                    if (postStatus(user[0].getStatus()))
                        userPostStatus(opponent);
                }
            }
        }
        // trainer chose not to attack this turn
        else {
            not preStatus(opponent[0].getStatus()) ? opponentAttack(opponent, user, opponentMove, t) : inflictedMessage(opponent[0]);

            // if trainer is faster than opponent...
            if (user[0].isFasterThan(opponent[0])) {
                if (postStatus(user[0].getStatus()))
                    userPostStatus(user);

                // if Pokémon is inflicted with a post-move status condition...
                if (postStatus(opponent[0].getStatus()))
                    opponentPostStatus(opponent);

            }
            // if opponent is faster than trainer...
            else if (opponent[0].isFasterThan(user[0])) {
                // if Pokémon is inflicted with a post-move status condition...
                if (postStatus(opponent[0].getStatus()))
                    opponentPostStatus(opponent);

                // if Pokémon is inflicted with a post-move status condition...
                if (postStatus(user[0].getStatus()))
                    userPostStatus(opponent);
            }
            // if trainer and opponent rival in speed; choose randomly
            else {
                if (generateInteger(0, 1) == 1) {
                    if (postStatus(user[0].getStatus()))
                        userPostStatus(user);

                    // if Pokémon is inflicted with a post-move status condition...
                    if (postStatus(opponent[0].getStatus()))
                        opponentPostStatus(opponent);
                }
                else {
                    // if Pokémon is inflicted with a post-move status condition...
                    if (postStatus(opponent[0].getStatus()))
                        opponentPostStatus(opponent);

                    // if Pokémon is inflicted with a post-move status condition...
                    if (postStatus(user[0].getStatus()))
                        userPostStatus(opponent);
                }
            }
        }
    }
};