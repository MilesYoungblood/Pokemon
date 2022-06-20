//
// Created by miles on 5/5/2022.
//

#pragma once

#include "Pokemon.h"
#include "Items.h"
#include "AttackFunctions.h"

int generateInteger(int lower, int upper) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(lower, upper);

    return dist(mt);
}

void wildPokemonMessage(const std::string& pokemon) {
    std::cout << "A wild " << pokemon << " appeared! ";
    sleep(2);
}

void sendOutMessage(const std::string& pokemon) {
    std::cout << "Go " << pokemon << "!\n";
    sleep(2);
}

void returnMessage(const std::string& pokemon) {
    std::cout << pokemon << ", return! ";
    sleep(2);
}

void introMessage(const std::string& userPokemon, const std::string& opposingPokemon) {
    wildPokemonMessage(opposingPokemon);
    sendOutMessage(userPokemon);
}

void getChar(char& userChar) {
    std::cin >> userChar;

    while (userChar != 'f' and userChar != 'b' and userChar != 'r' and userChar != 'p') {
        std::cin >> userChar;
    }
}

void getInt(int& userInt, int lower, int upper) {
    std::cin >> userInt;

    while (userInt < lower or upper < userInt) {
        std::cin >> userInt;
    }
}

void displayChoices(const std::string& pokemon) {
    std::cout << "What will " << pokemon << " do?\n";
    std::cout << "\tFight   (f)\n";
    std::cout << "\tBag     (b)\n";
    std::cout << "\tRun     (r)\n";
    std::cout << "\tPokemon (p)\n";
    std::cout.flush();
}

void displayPokemon(const std::vector<Pokemon>& party) {
    std::cout << "Choose a Pokemon:\n";
    for (int i = 0; i < party.size(); ++i) {
        std::cout << '\t' << party.at(i).getName() << std::string(15 - party.at(i).getName().length(), ' ')
                  << "(HP: " << party.at(i).getHP() << std::string(3 - std::to_string(party.at(i).getHP()).length(), ' ')
                  << '/' << party.at(i).getMaxHp() << std::string(3 - std::to_string(party.at(i).getMaxHp()).length(), ' ')
                  << ") -> " << i + 1 << '\n';
    }
    std::cout << "\nCancel (0)\n";
    std::cout.flush();
}

void displayHP(const Pokemon& userPokemon, const Pokemon& opposingPokemon) {
    std::cout << "\n";
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

void faint(Pokemon& pokemon, int& faintCounter) {
    pokemon.setHP(0);
    faintCounter++;
}

void faintMessage(const Pokemon& pokemon) {
    std::cout << pokemon.getName() << " fainted!\n";
    sleep(2);
}

void forceSwitchPrompt() {
    std::cout << "\nChoose an option:\n";
    std::cout << "\tFight (f)\n";
    std::cout << "\tRun   (r)\n";
    std::cout.flush();
}

void run(bool& runStatus) {
    int run = generateInteger(0, 1);

    if (run == 0) {
        runStatus = false;
    }
    else if (run == 1) {
        runStatus = true;
    }
}

void runMessage(bool runStatus) {
    if (runStatus) {
        std::cout << "Got away safely!\n";
    }
    else {
        std::cout << "Couldn't get away!\n";
    }
    sleep(1);
}

void pokemonPrompt() {
    std::cout << "Choose an option:\n";
    std::cout << "\tCheck Moves (c)\n";
    std::cout << "\tSwitch      (s)\n";
    std::cout << "\nCancel (0)\n";
    std::cout.flush();
}

void switchOut(std::vector<Pokemon>& party, int pokemonToSwitch) {
    Pokemon copyParty = party.at(0);
    party.at(0) = party.at(pokemonToSwitch);
    party.at(pokemonToSwitch) = copyParty;
}

void switchOutMessage(const std::vector<Pokemon>& party, int pokemonSwitched) {
    returnMessage(party.at(pokemonSwitched).getName());
    sendOutMessage(party.at(0).getName());
}

void switchOutErrorMessage() {
    std::cout << "Cannot switch with only one Pokemon left in party!\n";
    sleep(2);
}

void hpEmptyMessage(const std::string& pokemon) {
    std::cout << pokemon << "'s HP is empty!\n";
    sleep(2);
}

void hpFullMessage(const std::string& pokemon) {
    std::cout << pokemon << "'s HP is full!\n";
    sleep(2);
}

void winMessage() {
    std::cout << "You won!\n";
    sleep(2);
}

void loseMessage() {
    std::cout << "You've run out of usable Pokemon! ";
    sleep(2);
    std::cout << "You blacked out!\n";
    sleep(2);
}

void userAttack(std::vector<Pokemon>& attackingPokemon, std::vector<Pokemon>& defendingPokemon, int userMove, int opponentMonsFainted, bool& gameOver) {
    bool userMoveLanded = false, crit = false;
    int userDamage = calculateDamage(attackingPokemon.at(0), defendingPokemon.at(0), attackingPokemon.at(0).getMove(userMove - 1), crit);
    attack(defendingPokemon.at(0), attackingPokemon.at(0).getMove(userMove - 1), userDamage, userMoveLanded);
    attackMessage(attackingPokemon.at(0), defendingPokemon.at(0), userMove - 1, userDamage, userMoveLanded, crit);

    if (defendingPokemon.at(0).getHP() <= 0) { // if Pokémon's HP drops to zero...
        faint(defendingPokemon.at(0), opponentMonsFainted);
        faintMessage(defendingPokemon.at(0));
        if (opponentMonsFainted == defendingPokemon.size()) {
            winMessage();
            gameOver = true;
        }
    }
}

void opponentAttack(std::vector<Pokemon>& opponentParty, std::vector<Pokemon>& userParty, int opponentMove, int userMonsFainted, bool& gameOver) {
    bool opponentMoveLanded = false, crit = false;
    int opponentDamage = calculateDamage(opponentParty.at(0), userParty.at(0), opponentParty.at(0).getMove(opponentMove), crit);
    attack(userParty.at(0), opponentParty.at(0).getMove(opponentMove - 1), opponentDamage, opponentMoveLanded);
    attackMessage(opponentParty.at(0), userParty.at(0), opponentMove, opponentDamage, opponentMoveLanded, crit);

    if (userParty.at(0).getHP() <= 0) {
        faint(userParty.at(0), userMonsFainted);
        faintMessage(userParty.at(0));
        if (userMonsFainted == userParty.size()) {
            loseMessage();
            gameOver = true;
            return;
        }
        forceSwitchPrompt();

        char userChoice;
        int userSwitch;
        bool runSuccess = false;

        std::cin >> userChoice;

        while (userChoice != 'f' and userChoice != 'r') {
            std::cin >> userChoice;
        }

        if (userChoice == 'r') {
            run(runSuccess);
            runMessage(runSuccess);
            if (runSuccess) {
                gameOver = true;
                return;
            }
        }

        displayPokemon(userParty);
        std::cin >> userSwitch;

        while ((userSwitch <= 1 or userParty.size() < userSwitch) or userParty.at(userSwitch - 1).getHP() <= 0) {
            if (userParty.at(userSwitch - 1).getHP() <= 0) {
                hpEmptyMessage(userParty.at(userSwitch - 1).getName());
            }
            std::cin >> userSwitch;
        }

        switchOut(userParty, userSwitch);
        sendOutMessage(userParty.at(0).getName());
    }
}