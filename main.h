//
// Created by miles on 5/5/2022.
//

#ifndef POKEMON_BATTLE_MAIN_H
#define POKEMON_BATTLE_MAIN_H

#include "Pokemon.h"
#include "Moves.h"
#include "Items.h"

#include <iostream>
#include <vector>
#include <random>
#include <unistd.h>

#include <windows.h>

void Restore(Pokemon& pokemonToRestore, int amountToRestore) { // HP variant
    pokemonToRestore.SetHP(pokemonToRestore.GetHP() + amountToRestore);
    if (pokemonToRestore.GetHP() > pokemonToRestore.GetMaxHP()) {
        pokemonToRestore.SetHP(pokemonToRestore.GetMaxHP());
    }
}

void Restore(Moves& moveToRestore, int amountToRestore) { // PP variant
    moveToRestore.SetPP(moveToRestore.GetPP() + amountToRestore);
    if (moveToRestore.GetPP() > moveToRestore.GetMaxPP()) {
        moveToRestore.SetPP(moveToRestore.GetMaxPP());
    }
}

void RestoreMessage(const Pokemon& pokemonRestored, int amountRestored) { // HP variant
    std::cout << pokemonRestored.GetName() << " recovered " << amountRestored << " HP!" << std::endl;
    sleep(2);
}

void RestoreMessage(const Moves& moveRestored, int amountRestored) { // PP variant
    std::cout << moveRestored.GetName() << " recovered " << amountRestored << " PP!" << std::endl;
    sleep(2);
}

void Cure(Pokemon& pokemonToCure, const StatusItems& itemToUse) {
    if (itemToUse.GetRType() == "paralysis") {
        if (pokemonToCure.GetStatus() == "paralyzed") {
            pokemonToCure.SetStatus("No status");
        }
    }
    else if (itemToUse.GetRType() == "burn") {
        if (pokemonToCure.GetStatus() == "burned") {
            pokemonToCure.SetStatus("No status");
        }
    }
    else if (itemToUse.GetRType() == "freeze") {
        if (pokemonToCure.GetStatus() == "frozen") {
            pokemonToCure.SetStatus("No status");
        }
    }
    else if (itemToUse.GetRType() == "poison") {
        if (pokemonToCure.GetStatus() == "poisoned") {
            pokemonToCure.SetStatus("No status");
        }
    }
    else if (itemToUse.GetRType() == "sleep") {
        if (pokemonToCure.GetStatus() == "asleep") {
            pokemonToCure.SetStatus("No status");
        }
    }
}

void CureMessage(Pokemon pokemonCured, const std::string& status) {
    if (pokemonCured.GetStatus() == "No status") {
        std::cout << pokemonCured.GetName() << " recovered from " << status << '!' << std::endl;
        sleep(1);
    }
    else {
        std::cout << "But it failed!" << std::endl;
        sleep(1);
    }
}

void ItemErrorMessage(const std::string& item) {
    std::cout << "You don't have any " << item << "'s." << std::endl;
}

void IntroMessage(const std::vector<Pokemon>& userParty, const std::vector<Pokemon>& opponentParty) {
    std::cout << "A wild " << opponentParty.at(0).GetName() << " appeared! ";
    sleep(2);

    std::cout << "Go " << userParty.at(0).GetName() << "!" << std::endl << std::endl;
    sleep(2);
}

void DisplayChoices(const std::vector<Pokemon>& party) {
    std::cout << "What will " << party.at(0).GetName() << " do?" << std::endl
              << "   Fight:   (f)" << std::endl
              << "   Bag:     (b)" << std::endl
              << "   Run:     (r)" << std::endl
              << "   Pokemon: (p)" << std::endl;
}

void DisplayMoves(Pokemon& pokemon) {
    std::cout << "Choose a move: (Press 0 to go back)" << std::endl;
    for (int i = 0; i < NUM_MOVES; ++i) {
        std::cout << "   " << pokemon.GetMove(i).GetName() << std::string(15 - pokemon.GetMove(i).GetName().length(), ' ')
                  << " (PP: " << pokemon.GetMove(i).GetPP() << ") = " << i + 1 << std::endl;
    }
}

void DisplayBag() {
    std::cout << "Choose an option: (Press 0 to go back)" << std::endl
              << "   HP/PP Restore  (1)" << std::endl
              << "   Status Restore (2)" << std::endl
              << "   Poke Balls     (3)" << std::endl
              << "   Battle Items   (4)" << std::endl;
}

template <typename T>
void DisplayItems(const std::vector<T>& items) {
    std::cout << "Choose an item:" << std::endl;
    for (int i = 0; i < items.size(); ++i) {
        std::cout << "   " << items.at(i).GetName() << " x" << items.at(i).GetQuantity() << std::string(15 - items.at(i).GetName().length(), ' ')
                  << " (" << i + 1 << ')' << std::endl;
    }
    std::cout << std::endl << "Go back (0)" << std::endl;
}

void DisplayPokemon(const std::vector<Pokemon>& party) {
    std::cout << "Choose a Pokemon:" << std::endl;
    for (int i = 1; i < party.size(); ++i) {
        std::cout << "   " << party.at(i).GetName() << std::string(15 - party.at(i).GetName().length(), ' ') << "(" << i << ")" << std::endl;
    }
    std::cout << std::endl << "Go back (0)" << std::endl;
}

void DisplayPokemonHeal(const std::vector<Pokemon>& party) {
    std::cout << "Choose a Pokemon to heal: (Press 0 to go back)" << std::endl;
    for (int i = 0; i < party.size(); ++i) {
        std::cout << "   " << party.at(i).GetName() << std::string(15 - party.at(i).GetName().length(), ' ') << "(" << i + 1<< ")" << std::endl;
    }
}

void DisplayHP(const std::vector<Pokemon>& party, const std::vector<Pokemon>& opponentParty) {
    std::cout << '+' << std::string (17, '-') << '+' << std::string(9, '-') << '+' << std::endl;

    std::cout << "| " << party.at(0).GetName() << ':' << std::string(15 - party.at(0).GetName().length(), ' ')
              << "| HP: " << party.at(0).GetHP() << " |" << std::endl;

    std::cout << '+' << std::string (17, '-') << '+' << std::string(9, '-') << '+' << std::endl;

    std::cout << "| " << opponentParty.at(0).GetName() << ':' << std::string(15 - opponentParty.at(0).GetName().length(), ' ')
              << "| HP: " << opponentParty.at(0).GetHP() << " |" << std::endl;

    std::cout << '+' << std::string (17, '-') << '+' << std::string(9, '-') << '+' << std::endl << std::endl;
}

void Attack(Pokemon& pokemonToAttack, Pokemon& attackingPokemon, int move) {
    pokemonToAttack.SetHP(pokemonToAttack.GetHP() - attackingPokemon.GetMove(move).GetPower());
    attackingPokemon.GetMove(move).SetPP(attackingPokemon.GetMove(move).GetPP() - 1);
}

void AttackMessage(std::vector<Pokemon>& party, int move) {
    std::cout << party.at(0).GetName() << " used " << party.at(0).GetMove(move).GetName() << "! ";
    sleep(1);
    std::cout << party.at(0).GetMove(move).GetName() << " did " << party.at(0).GetMove(move).GetPower() << " damage!" << std::endl;
    sleep(2);
}

void AttackErrorMessage() {
    std::cout << "That move is out of PP. Please select another move." << std::endl;
    sleep(2);
}

void Faint(Pokemon& pokemon, int& faintCounter) {
    pokemon.SetHP(0);
    faintCounter++;
}

void FaintMessage(std::vector<Pokemon> partyVector) {
    std::cout << partyVector.at(0).GetName() << " fainted!" << std::endl;
    sleep(2);
}

void ForceSwitchPrompt() {
    std::cout << std::endl << "Choose an option:" << std::endl;
    std::cout << "   Fight (f)" << std::endl;
    std::cout << "   Run   (r)" << std::endl;
}

void Run(bool& runStatus) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 2.0);

    if ((int)dist(mt) == 0) {
        runStatus = false;
    }
    else if ((int)dist(mt) == 1) {
        runStatus = true;
    }
}

void RunMessage(bool runStatus) {
    if (runStatus) {
        std::cout << "Got away safely!" << std::endl;
    }
    else {
        std::cout << "Couldn't get away!" << std::endl;
    }
    sleep(1);
}

void Switch(std::vector<Pokemon>& pokemonParty, int pokemonToSwitch) {
    Pokemon copyParty = pokemonParty.at(0);
    pokemonParty.at(0) = pokemonParty.at(pokemonToSwitch);
    pokemonParty.at(pokemonToSwitch) = copyParty;
}

void SwitchMessage(const std::vector<Pokemon>& party, int pokemonSwitched) {
    std::cout << party.at(pokemonSwitched).GetName() << " return!";
    sleep(2);
    std::cout << "Go " << party.at(0).GetName() << "!" << std::endl;
    sleep(2);
}

void SwitchErrorMessage() {
    std::cout << "Cannot switch with only one Pokemon left in party" << std::endl;
    sleep(2);
}

void HPEmptyMessage(const Pokemon& pokemon) {
    std::cout << pokemon.GetName() << "'s HP is empty!" << std::endl;
    sleep(2);
}

void HPFullMessage(const Pokemon& pokemon) {
    std::cout << pokemon.GetName() << "'s HP is full!" << std::endl;
    sleep(2);
}

void WinMessage() {
    std::cout << "You won!" << std::endl;
    sleep(2);
}

void LoseMessage() {
    std::cout << "You've run out of usable Pokemon!" << std::endl;
    sleep(2);
    std::cout << "You blacked out!" << std::endl;
    sleep(2);
}

#endif //POKEMON_BATTLE_MAIN_H