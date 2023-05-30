//
// Created by miles on 5/5/2022.
//

#pragma once

#include <unistd.h>
#include "../Classes/Trainer/Trainer.h"
#include "../main.h"
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

void displayEmptyHPBar(size_t t) {
    std::cout << "Turn " << t << '\n';
    for (int i = 0; i < 2; ++i) {
        std::cout << '+' << std::string(16, '-') << '+' << std::string(13, '-') << "+\n";
        std::cout << '|' << std::string(16, ' ') << "|" << std::string(13, ' ') << "|\n";
    }
    std::cout << '+' << std::string(16, '-') << '+' << std::string(13, '-') << "+\n\n"; // bottom layer
    std::cout.flush();
}

void displayHPBar(const Pokemon &userPokemon, const Pokemon &opposingPokemon, size_t t) {
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

__attribute__((unused)) bool run(const Pokemon &trainer_1, const Pokemon &trainer_2) {
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
                      << "| HP: " << opposingPokemon.getHP() - i + damage
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
                      << "| HP: " << userPokemon.getHP() - i + damage
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