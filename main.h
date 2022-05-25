//
// Created by miles on 5/5/2022.
//

#ifndef POKEMON_BATTLE_MAIN_H
#define POKEMON_BATTLE_MAIN_H

#include "Pokemon.h"
#include "Moves.h"

#include <vector>

void DisplayChoices(const vector<Pokemon>& party) {
    cout << "What will " << party.at(0).GetName() << " do?" << endl
         << "   Fight:  f" << endl
         << "   Bag:    b" << endl
         << "   Run:    r" << endl
         << "   Switch: s" << endl;
}

void DisplayMoves(const vector<Moves>& userMoves) {
    cout << "Choose a move: (Press 0 to go back)" << endl;
    for (int i = 0; i < NUM_MOVES; ++i) {
        cout << "   " << userMoves.at(i).GetName() << string(15 - userMoves.at(i).GetName().length(), ' ')
             << " (PP: " << userMoves.at(i).GetPP() << ") = " << i + 1 << endl;
    }
}

void DisplayPokemon(const vector<Pokemon>& party, const vector<Pokemon>& faintedParty) {
    cout << "Switch " << party.at(0).GetName() << " with: (Press 0 to go back)" << endl;
    if (!faintedParty.empty()) {
        cout << "Healthy Pokemon:" << endl;
    }
    for (int i = 1; i < party.size(); ++i) {
        if (!faintedParty.empty()) {
            cout << "   ";
        }
        cout << party.at(i).GetName() << string(15 - party.at(i).GetName().length(), ' ') << "(" << i << ")" << endl;
    }
    if (!faintedParty.empty()) {
        for (const auto & i : faintedParty) {
            cout << "   " << i.GetName() << string(15 - i.GetName().length(), ' ') << endl;
        }
    }
}

void DisplayHP(const vector<Pokemon>& party, const vector<Pokemon>& opponentParty) {
    cout << party.at(0).GetName() << ":" << string(15 - party.at(0).GetName().length(), ' ') << "| HP: " << party.at(0).GetHP() << endl;
    cout << opponentParty.at(0).GetName() << ":" << string(15 - opponentParty.at(0).GetName().length(), ' ') << "| HP: " << opponentParty.at(0).GetHP() << endl << endl;
}

void Attack(Pokemon& pokemonToAttack, Moves& moveUsed) {
    pokemonToAttack.SetHP(pokemonToAttack.GetHP() - moveUsed.GetDamage());
    moveUsed.SetPP(moveUsed.GetPP() - 1);
}

void AttackMessage(const vector<Pokemon>& partyVector, const vector<Moves>& moveVector, int move) {
    cout << partyVector.at(0).GetName() << " used " << moveVector.at(move).GetName() << "! ";
    sleep(1);
    cout << moveVector.at(move).GetName() << " did " << moveVector.at(move).GetDamage()
         << " damage!" << endl;
    sleep(2);
}

void Faint(vector<Pokemon>& partyVector, vector<Pokemon>& faintedPokemon) {
    partyVector.erase(partyVector.begin());
    faintedPokemon.push_back(partyVector.at(0));
}

void FaintMessage(vector<Pokemon> partyVector) {
    cout << partyVector.at(0).GetName() << " fainted!" << endl;
    sleep(2);
}

void Run(bool& runStatus) {
    srand(time(nullptr));
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
        cout << "Got away safely!" << endl;
        sleep(1);
    }
    else {
        cout << "Couldn't get away!" << endl;
        sleep(1);
    }
}

void Switch(vector<Pokemon>& pokemonParty, int pokemonToSwitch) {
    Pokemon copyParty = pokemonParty.at(0);
    pokemonParty.at(0) = pokemonParty.at(pokemonToSwitch);
    pokemonParty.at(pokemonToSwitch) = copyParty;
}

void SwitchMessage(const vector<Pokemon>& party) {
    cout << party.at(0).GetName() << " return!" << endl;
    sleep(2);
    cout << "Go " << party.at(0).GetName() << "!" << endl;
    sleep(2);
}



#endif //POKEMON_BATTLE_MAIN_H