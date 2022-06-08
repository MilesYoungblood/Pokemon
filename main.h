//
// Created by miles on 5/5/2022.
//

#ifndef POKEMON_BATTLE_MAIN_H
#define POKEMON_BATTLE_MAIN_H

#include "Pokemon.h"
#include "Moves.h"
#include "Items.h"
#include "AttackFunctions.h"

void introMessage(const std::vector<Pokemon>& userParty, const std::vector<Pokemon>& opponentParty) {
    std::cout << "A wild " << opponentParty.at(0).getName() << " appeared! ";
    sleep(2);

    std::cout << "Go " << userParty.at(0).getName() << "!\n\n";
    sleep(2);
}

void displayChoices(const std::vector<Pokemon>& party) {
    std::cout << "What will " << party.at(0).getName() << " do?\n"
              << "\tFight:   (f)\n"
              << "\tBag:     (b)\n"
              << "\tRun:     (r)\n"
              << "\tPokemon: (p)\n";
}

void displayPokemon(const std::vector<Pokemon>& party) {
    std::cout << "Choose a Pokemon:\n";
    for (int i = 0; i < party.size(); ++i) {
        std::cout << '\t' << party.at(i).getName() << std::string(15 - party.at(i).getName().length(), ' ') << '(' << i + 1 << ")\n";
    }
    std::cout << "\nGo back (0)\n";
}

void displayHP(const std::vector<Pokemon>& userParty, const std::vector<Pokemon>& opponentParty) {
    std::cout << '+' << std::string (16, '-') << '+' << std::string(13, '-') << "+\n";

    std::cout << "| " << userParty.at(0).getName() << std::string(15 - userParty.at(0).getName().length(), ' ')
              << "| HP: " << userParty.at(0).getHP() << std::string(3 - std::to_string(userParty.at(0).getHP()).length(), ' ')
              << '/' << userParty.at(0).getMaxHp() << std::string(3 - std::to_string(userParty.at(0).getMaxHp()).length(), ' ')
              << " |\n";

    std::cout << '+' << std::string (16, '-') << '+' << std::string(13, '-') << "+\n";

    std::cout << "| " << opponentParty.at(0).getName() << std::string(15 - opponentParty.at(0).getName().length(), ' ')
              << "| HP: " << opponentParty.at(0).getHP() << std::string(3 - std::to_string(opponentParty.at(0).getHP()).length(), ' ')
              << '/' << opponentParty.at(0).getMaxHp() << std::string(3 - std::to_string(userParty.at(0).getMaxHp()).length(), ' ')
              <<  " |\n";

    std::cout << '+' << std::string (16, '-') << '+' << std::string(13, '-') << "+\n\n";
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
    std::cout << "\t run   (r)\n";
}

void run(bool& runStatus) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 1);

    if (dist(mt) == 0) {
        runStatus = false;
    }
    else if (dist(mt) == 1) {
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

void switchOut(std::vector<Pokemon>& party, int pokemonToSwitch) {
    Pokemon copyParty = party.at(0);
    party.at(0) = party.at(pokemonToSwitch);
    party.at(pokemonToSwitch) = copyParty;
}

void switchOutMessage(const std::vector<Pokemon>& party, int pokemonSwitched) {
    std::cout << party.at(pokemonSwitched).getName() << " return! ";
    sleep(2);
    std::cout << "Go " << party.at(0).getName() << "!\n";
    sleep(2);
}

void switchOutErrorMessage() {
    std::cout << "Cannot switch with only one Pokemon left in party!\n";
    sleep(2);
}

void hpEmptyMessage(const Pokemon& pokemon) {
    std::cout << pokemon.getName() << "'s HP is empty!\n";
    sleep(2);
}

void hpFullMessage(const Pokemon& pokemon) {
    std::cout << pokemon.getName() << "'s HP is full!\n";
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

void userAttack(std::vector<Pokemon>& userParty, std::vector<Pokemon>& opponentParty, int userMove, int opponentMonsFainted, bool& gameOver) {
    bool userMoveLanded = false;
    int userDamage = userParty.at(0).getMove(userMove - 1).getDamage();
    attack(opponentParty.at(0), userParty.at(0).getMove(userMove - 1), userDamage, userMoveLanded);
    attackMessage(userParty.at(0), opponentParty.at(0), userMove - 1, userDamage, userMoveLanded);

    if (opponentParty.at(0).getHP() <= 0) { // if Pokémon's HP drops to zero...
        faint(opponentParty.at(0), opponentMonsFainted);
        faintMessage(opponentParty.at(0));
        if (opponentMonsFainted == opponentParty.size()) {
            winMessage();
            gameOver = true;
        }
    }
}

void opponentAttack(std::vector<Pokemon>& opponentParty, std::vector<Pokemon>& userParty, int opponentMove, int userMonsFainted, bool& gameOver) {
    bool opponentMoveLanded = false;
    int opponentDamage = opponentParty.at(0).getMove(opponentMove).getDamage();
    attack(userParty.at(0), opponentParty.at(0).getMove(opponentMove - 1), opponentDamage, opponentMoveLanded);
    attackMessage(opponentParty.at(0), userParty.at(0), opponentMove, opponentDamage, opponentMoveLanded);

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

        if (userMonsFainted < userParty.size() - 1) { // forces switch after Pokémon is fainted
            displayPokemon(userParty);
            std::cin >> userSwitch;

            while ((userSwitch < 1 or userParty.size() - 1 < userSwitch) and userParty.at(userSwitch - 1).getHP() <= 0) {
                if (userParty.at(userSwitch - 1).getHP() <= 0) {
                    hpEmptyMessage(userParty.at(userSwitch - 1));
                }
                std::cin >> userSwitch;
            }

            switchOut(userParty, userSwitch);
        }
    }
}

#endif //POKEMON_BATTLE_MAIN_H