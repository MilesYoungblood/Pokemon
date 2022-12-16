//
// Created by miles on 5/5/2022.
//

#pragma once

#include <iostream>
#include <unistd.h>
#include "Trainer.h"
#include "AttackFunctions.h"
#include "ItemFunctions.h"

void wildPokemonMessage(const Pokemon &pokemon) {
    std::cout << "A wild " << pokemon << " appeared! ";
    sleep(1);
}

void sendOutMessage(const Pokemon &pokemon) {
    std::cout << "Go " << pokemon << "!\n";
    sleep(1);
}

void returnMessage(const Pokemon &pokemon) {
    std::cout << pokemon << ", return! ";
    sleep(1);
}

void introMessage(const Pokemon &userPokemon, const Pokemon &opposingPokemon) {
    wildPokemonMessage(opposingPokemon);
    sendOutMessage(userPokemon);
}

void displayChoices(const Pokemon &pokemon) {
    std::cout << "What will " << pokemon << " do?\n";
    std::cout << "\tFight   (f)\n";
    std::cout << "\tBag     (b)\n";
    std::cout << "\tRun     (r)\n";
    std::cout << "\tPokemon (p)\n";
    std::cout.flush();

    /*
     * std::cout << "+-------------+-------------+\n";
       std::cout << "| Fight   (f) | Bag     (b) |\n";
       std::cout << "+-------------+-------------+\n";
       std::cout << "| Run     (r) | Pokemon (p) |\n";
       std::cout << "+-------------+-------------+\n";
     */
}

void displayPokemon(const Trainer &t) {
    std::cout << "Choose a Pokemon:\n";
    for (int i = 0; i < t.partySize(); ++i) {
        std::cout << '\t' << t[i].getName() << std::string(15 - t[i].getName().length(), ' ')
                  << "(HP: " << t[i].getHP() << std::string(3 - std::to_string(t[i].getHP()).length(), ' ')
                  << '/' << t[i].getMaxHp() << std::string(3 - std::to_string(t[i].getMaxHp()).length(), ' ')
                  << ") -> " << i + 1 << '\n';
    }
    std::cout << "\nCancel (0)\n";
    std::cout.flush();
}

void displayHP(const Pokemon &userPokemon, const Pokemon &opposingPokemon) {
    std::cout << '\n';
    std::cout << '+' << std::string(16, '-') << '+' << std::string(13, '-') << "+\n"; // top layer

    std::cout << "| " << userPokemon.getName() << std::string(15 - userPokemon.getName().length(), ' ')
              << "| HP: " << userPokemon.getHP() << std::string(3 - std::to_string(userPokemon.getHP()).length(), ' ')
              << '/' << userPokemon.getMaxHp() << std::string(3 - std::to_string(userPokemon.getMaxHp()).length(), ' ')
              << " |\n";

    std::cout << '+' << std::string(16, '-') << '+' << std::string(13, '-') << "+\n"; // middle layer

    std::cout << "| " << opposingPokemon.getName() << std::string(15 - opposingPokemon.getName().length(), ' ')
              << "| HP: " << opposingPokemon.getHP() << std::string(3 - std::to_string(opposingPokemon.getHP()).length(), ' ')
              << '/' << opposingPokemon.getMaxHp() << std::string(3 - std::to_string(userPokemon.getMaxHp()).length(), ' ')
              <<  " |\n";

    std::cout << '+' << std::string(16, '-') << '+' << std::string(13, '-') << "+\n\n"; // bottom layer
    std::cout.flush();
}

void faintMessage(const Pokemon &pokemon) {
    std::cout << pokemon << " fainted!\n";
    sleep(2);
}

void forceSwitchPrompt() {
    std::cout << "\nChoose an option:\n";
    std::cout << "\tFight (f)\n";
    std::cout << "\tRun   (r)\n";
    std::cout.flush();
}

bool run() {
    return generateInteger(0, 1) == 1;
}

void runMessage(bool runStatus) {
    runStatus ? std::cout << "Got away safely!\n" : std::cout << "Couldn't get away!\n";
    sleep(1);
}

void pokemonPrompt() {
    std::cout << "Choose an option:\n";
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

void switchOutErrorMessage() {
    std::cout << "Cannot switch with only one Pokemon left in party!\n";
    sleep(2);
}

void inBattleMessage(const Pokemon &pokemon) {
    std::cout << pokemon << " is already in battle!" << std::endl;
    sleep(2);
}

void hpEmptyMessage(const Pokemon &pokemon) {
    std::cout << pokemon << "'s HP is empty!\n";
    sleep(2);
}

void hpFullMessage(const std::string& pokemon) {
    std::cout << pokemon << "'s HP is full!\n";
    sleep(2);
}

void winMessage() {
    std::cout << "Your opponent ran out of usable Pokemon! ";
    sleep(2);
    std::cout << "You won!\n";
    sleep(2);
}

void loseMessage() {
    std::cout << "You've run out of usable Pokemon! ";
    sleep(2);
    std::cout << "You blacked out!\n";
    sleep(2);
}

bool preStatus(const std::string& status) {
    return status == "paralysis" ? generateInteger(1, 4) == 1 : status == "freeze" or status == "sleep";
}

bool postStatus(const std::string& status) {
    return status == "burn" or status == "poison";
}

void inflictedMessage(const Pokemon& pokemon) {
    if (pokemon.getStatus() == "burn") {
        std::cout << pokemon.getName() << " took " << static_cast<int>(pokemon.getMaxHp() * .0625) << " damage from it's burn!\n";
    }
    else if (pokemon.getStatus() == "paralysis") {
        std::cout << pokemon.getName() << " is paralyzed! It can't move!\n";
    }
    else if (pokemon.getStatus() == "freeze") {
        std::cout << pokemon.getName() << " is frozen solid!\n";
    }
    else if (pokemon.getStatus() == "poison"){
        std::cout << pokemon.getName() << " took " << static_cast<int>(pokemon.getMaxHp() * .0625) << "damage from poison!\n";
    }
    else if (pokemon.getStatus() == "sleep") {
        std::cout << pokemon.getName() << " is fast asleep.\n";
    }
    sleep(1);
}

void userAttack(Trainer &user, Trainer &opponent, int userMove) {
    bool crit = false;
    int userDamage = calculateDamage(user[0], opponent[0], user[0][userMove - 1], crit);

    attack(opponent[0], user[0][userMove - 1], userDamage);
    attackMessage(user[0], opponent[0], userMove - 1, userDamage, crit);

    if (opponent[0].getHP() <= 0) { // if Pokémon's HP drops to zero...
        opponent[0].faint();
        opponent.incFaintCount();
        faintMessage(opponent[0]);
        if (opponent.numFainted() == opponent.partySize()) {
            winMessage();
            exit(0);
        }
    }
}

void opponentAttack(Trainer &opponent, Trainer &user, int opponentMove) {
    bool crit = false;
    int opponentDamage = calculateDamage(opponent[0], user[0], opponent[0][opponentMove], crit);

    attack(user[0], opponent[0][opponentMove - 1], opponentDamage);
    attackMessage(opponent[0], user[0], opponentMove, opponentDamage, crit);

    if (user[0].getHP() <= 0) {
        user[0].faint();
        user.incFaintCount();
        faintMessage(user[0]);
        if (user.numFainted() == user.partySize()) {
            loseMessage();
            exit(0);
        }
        forceSwitchPrompt();

        char userChoice = getChar({"f", "r"});
        int pokemon;

        if (userChoice == 'r') {
            bool runSuccess = run();
            runMessage(runSuccess);
            if (runSuccess) {
                exit(0);
            }
        }

        displayPokemon(user);
        std::cin >> pokemon;

        while ((pokemon <= 1 or user.partySize() < pokemon) or user[pokemon - 1].getHP() <= 0) {
            // cannot heal a fainted Pokémon
            if (user[pokemon - 1].getHP() <= 0) {
                hpEmptyMessage(user[pokemon - 1]);
            }
            std::cin >> pokemon;
        }

        switchOut(user, pokemon);
        sendOutMessage(user[0]);
    }
}

void battlePhase(Trainer &user, Trainer &opponent, int userMove, int opponentMove, char userChoice) {
    // if trainer chose to attack this turn...
    if (userChoice == 'f') {
        // trainer is faster than opponent...
        if (user[0].getBaseSpeed() > opponent[0].getBaseSpeed()) {
            not preStatus(user[0].getStatus()) ? userAttack(user, opponent, userMove) : inflictedMessage(user[0]);
            not preStatus(opponent[0].getStatus()) ? opponentAttack(opponent, user, opponentMove) : inflictedMessage(opponent[0]);

            if (postStatus(user[0].getStatus())) { // if Pokémon is inflicted with a post-move status condition...
                takeDamage(user, static_cast<int>(user[0].getMaxHp() * .0625));
                status::takeDamageMessage(user[0]);
                if (user.numFainted() == user.partySize()) {
                    loseMessage();
                    exit(0);
                }
            }
            if (postStatus(opponent[0].getStatus())) { // if Pokémon is inflicted with a post-move status condition...
                takeDamage(opponent, static_cast<int>(opponent[0].getMaxHp() * .0625));
                status::takeDamageMessage(user[0]);
                if (opponent.numFainted() == opponent.partySize()) {
                    winMessage();
                    exit(0);
                }
            }
        }
        // if opponent is faster than trainer...
        else if (user[0].getBaseSpeed() < opponent[0].getBaseSpeed()) {
            not preStatus(opponent[0].getStatus()) ? opponentAttack(opponent, user, opponentMove) : inflictedMessage(opponent[0]);
            not preStatus(user[0].getStatus()) ? userAttack(user, opponent, userMove) : inflictedMessage(user[0]);

            if (postStatus(opponent[0].getStatus())) { // if Pokémon is inflicted with a post-move status condition...
                takeDamage(opponent, static_cast<int>(opponent[0].getMaxHp() * .0625));
                status::takeDamageMessage(user[0]);
                if (opponent.numFainted() == opponent.partySize()) {
                    winMessage();
                    exit(0);
                }
            }
            if (postStatus(user[0].getStatus())) { // if Pokémon is inflicted with a post-move status condition...
                takeDamage(user, static_cast<int>(user[0].getMaxHp() * .0625));
                status::takeDamageMessage(user[0]);
                if (user.numFainted() == user.partySize()) {
                    loseMessage();
                    exit(0);
                }
            }
        }
        // trainer and opponent rival in speed, choose randomly
        else {
            if (generateInteger(0, 1) == 0) {
                not preStatus(user[0].getStatus()) ? userAttack(user, opponent, userMove) : inflictedMessage(user[0]);
                not preStatus(opponent[0].getStatus()) ? opponentAttack(opponent, user, opponentMove) : inflictedMessage(opponent[0]);

                if (postStatus(user[0].getStatus())) { // if Pokémon is inflicted with a post-move status condition...
                    takeDamage(user, static_cast<int>(user[0].getMaxHp() * .0625));
                    status::takeDamageMessage(user[0]);
                    if (user.numFainted() == user.partySize()) {
                        loseMessage();
                        exit(0);
                    }
                }
                if (postStatus(opponent[0].getStatus())) { // if Pokémon is inflicted with a post-move status condition...
                    takeDamage(opponent, static_cast<int>(opponent[0].getMaxHp() * .0625));
                    status::takeDamageMessage(user[0]);
                    if (opponent.numFainted() == opponent.partySize()) {
                        winMessage();
                        exit(0);
                    }
                }
            }
            else {
                not preStatus(opponent[0].getStatus()) ? opponentAttack(opponent, user, opponentMove) : inflictedMessage(opponent[0]);
                not preStatus(user[0].getStatus()) ? userAttack(user, opponent, userMove) : inflictedMessage(user[0]);

                if (postStatus(opponent[0].getStatus())) { // if Pokémon is inflicted with a post-move status condition...
                    takeDamage(opponent, static_cast<int>(opponent[0].getMaxHp() * .0625));
                    status::takeDamageMessage(user[0]);
                    if (opponent.numFainted() == opponent.partySize()) {
                        winMessage();
                        exit(0);
                    }
                }
                if (postStatus(user[0].getStatus())) { // if Pokémon is inflicted with a post-move status condition...
                    takeDamage(user, static_cast<int>(user[0].getMaxHp() * .0625));
                    status::takeDamageMessage(user[0]);
                    if (user.numFainted() == user.partySize()) {
                        loseMessage();
                        exit(0);
                    }
                }
            }
        }
    }
    // trainer chose not to attack this turn
    else {
        if (not preStatus(opponent[0].getStatus())) { // if the opponent is not inflicted with a pre-move status condition...
            opponentAttack(opponent, user, opponentMove);
        }
        if (postStatus(user[0].getStatus())) {
            takeDamage(user, static_cast<int>(user[0].getMaxHp() * .0625));
            status::takeDamageMessage(user[0]);
            if (user.numFainted() == user.partySize()) {
                loseMessage();
                exit(0);
            }
        }
        if (postStatus(opponent[0].getStatus())) { // if Pokémon is inflicted with a post-move status condition...
            takeDamage(opponent, static_cast<int>(opponent[0].getMaxHp() * .0625));
            status::takeDamageMessage(user[0]);
            if (opponent.numFainted() == opponent.partySize()) {
                winMessage();
                exit(0);
            }
        }
    }
}