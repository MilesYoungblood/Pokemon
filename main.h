//
// Created by miles on 5/5/2022.
//

#ifndef POKEMON_BATTLE_MAIN_H
#define POKEMON_BATTLE_MAIN_H

#include "Pokemon.h"
#include "Moves.h"
#include "Items.h"

#include <iostream>
#include <unistd.h>
#include <vector>

void InvalidOptionMessage() {
    std::cout << "Invalid option. Please try again." << std::endl;
    sleep(2);
}

void Heal(Pokemon& pokemonToHeal, int amountToHeal) {
    pokemonToHeal.SetHP(pokemonToHeal.GetHP() + amountToHeal);
    if (pokemonToHeal.GetHP() > pokemonToHeal.GetMaxHP()) {
        pokemonToHeal.SetHP(pokemonToHeal.GetMaxHP());
    }
}

void HealMessage(const Pokemon& pokemonHealed, int amountHealed) {
    std::cout << pokemonHealed.GetName() << " recovered " << amountHealed << " HP!" << std::endl;
    sleep(2);
}

void IntroMessage(const std::vector<Pokemon>& userParty, const std::vector<Pokemon>& opponentParty) {
    std::cout << "A wild " << opponentParty.at(0).GetName() << " appeared!" << std::endl;
    sleep(2);

    std::cout << "Go " << userParty.at(0).GetName() << "!" << std::endl << std::endl;
    sleep(2);
}

void DisplayChoices(const std::vector<Pokemon>& party) {
    std::cout << "What will " << party.at(0).GetName() << " do?" << std::endl
         << "   Fight:   f" << std::endl
         << "   Bag:     b" << std::endl
         << "   Run:     r" << std::endl
         << "   Pokemon: p" << std::endl;
}

void GetChoice(char& choice) {
    std::cin >> choice;
    while (choice != 'f' && choice != 'b' && choice != 'r' && choice != 's') {
        InvalidOptionMessage();
        std::cin >> choice;
    }
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

void DisplayRestoreItems(const std::vector<RestoreItems>& restoreItems) {
    std::cout << "Choose an item:" << std::endl;
    for (int i = 0; i < restoreItems.size(); ++i) {
        std::cout << "   " << restoreItems.at(i).GetName() << " x" << restoreItems.at(i).GetQuantity() << std::string(15 - restoreItems.at(i).GetName().length(), ' ')
                  << " (" << i + 1 << ')' << std::endl;
    }
}

void DisplayStatusItems(const std::vector<StatusItems>& statusItems) {
    std::cout << "Choose an item:" << std::endl;
    for (int i = 0; i < statusItems.size(); ++i) {
        std::cout << "   " << statusItems.at(i).GetName() << " x" << statusItems.at(i).GetQuantity() << std::string(15 - statusItems.at(i).GetName().length(), ' ')
                  << " (" << i + 1 << ')' << std::endl;
    }
}

void DisplayPokemon(const std::vector<Pokemon>& party, const std::vector<Pokemon>& faintedParty) {
    std::cout << "Switch " << party.at(0).GetName() << " with: (Press 0 to go back)" << std::endl;
    if (!faintedParty.empty()) {
        std::cout << "Healthy Pokemon:" << std::endl;
    }
    for (int i = 1; i < party.size(); ++i) {
        if (!faintedParty.empty()) {
            std::cout << "   ";
        }
        std::cout << party.at(i).GetName() << std::string(15 - party.at(i).GetName().length(), ' ') << "(" << i << ")" << std::endl;
    }
    if (!faintedParty.empty()) {
        for (const auto & i : faintedParty) {
            std::cout << "   " << i.GetName() << std::string(15 - i.GetName().length(), ' ') << std::endl;
        }
    }
}

void DisplayPokemonHeal(const std::vector<Pokemon>& party) {
    std::cout << "Choose a Pokemon to heal: (Press 0 to go back)" << std::endl;
    for (int i = 0; i < party.size(); ++i) {
        std::cout << "   " << party.at(i).GetName() << std::string(15 - party.at(i).GetName().length(), ' ') << "(" << i + 1<< ")" << std::endl;
    }
}

void DisplayHP(const std::vector<Pokemon>& party, const std::vector<Pokemon>& opponentParty) {
    std::cout << party.at(0).GetName() << ":" << std::string(15 - party.at(0).GetName().length(), ' ') << "| HP: " << party.at(0).GetHP() << std::endl;
    std::cout << opponentParty.at(0).GetName() << ":" << std::string(15 - opponentParty.at(0).GetName().length(), ' ') << "| HP: " << opponentParty.at(0).GetHP() << std::endl << std::endl;
}

void Attack(Pokemon& pokemonToAttack, Pokemon& attackingPokemon, int move) {
    pokemonToAttack.SetHP(pokemonToAttack.GetHP() - attackingPokemon.GetMove(move).GetDamage());
    attackingPokemon.GetMove(move).SetPP(attackingPokemon.GetMove(move).GetPP() - 1);
}

void AttackMessage(std::vector<Pokemon>& party, int move) {
    std::cout << party.at(0).GetName() << " used " << party.at(0).GetMove(move).GetName() << "! ";
    sleep(1);
    std::cout << party.at(0).GetMove(move).GetName() << " did " << party.at(0).GetMove(move).GetDamage() << " damage!" << std::endl;
    sleep(2);
}

void AttackErrorMessage() {
    std::cout << "That move is out of PP. Please select another move." << std::endl;
    sleep(2);
}

void Faint(std::vector<Pokemon>& partyVector, std::vector<Pokemon>& faintedPokemon) {
    partyVector.erase(partyVector.begin());
    faintedPokemon.push_back(partyVector.at(0));
}

void FaintMessage(std::vector<Pokemon> partyVector) {
    std::cout << partyVector.at(0).GetName() << " fainted!" << std::endl;
    sleep(2);
}

void Run(bool& runStatus) {
    int num = rand() % 2;

    if (num == 0) {
        runStatus = false;
    }
    else if (num == 1) {
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

void SwitchMessage(const std::vector<Pokemon>& party) {
    std::cout << party.at(0).GetName() << " return!" << std::endl;
    sleep(2);
    std::cout << "Go " << party.at(0).GetName() << "!" << std::endl;
    sleep(2);
}

void SwitchErrorMessage() {
    std::cout << "That Pokemon's HP is 0. Choose another Pokemon" << std::endl;
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