//
// Created by miles on 5/5/2022.
//

#include "Pokemon.h"

Pokemon::Pokemon() {
    hp = 300;
    attack = 6;
    spAttack = 6;
    defense = 6;
    spDefense = 6;
    speed = 6;
    accuracy = 6;

    name = "No name";
    moveSet.resize(NUM_MOVES);
}

Pokemon::Pokemon(const string& nameToSet, int hpToSet) {
    hp = hpToSet;
    attack = 6;
    spAttack = 6;
    defense = 6;
    spDefense = 6;
    speed = 6;
    accuracy = 6;

    name = nameToSet;
    moveSet.resize(NUM_MOVES);
}

void Pokemon::SetHP(int val) { hp = val; }
void Pokemon::SetAttack(int val) { attack = val; }
void Pokemon::SetSpAttack(int val) { spAttack = val; }
void Pokemon::SetDefense(int val) { defense = val; }
void Pokemon::SetSpDefense(int val) { spDefense = val; }
void Pokemon::SetSpeed(int val) { speed = val; }
void Pokemon::SetAccuracy(int val) { accuracy = val; }

int Pokemon::GetHP() const { return hp; }
int Pokemon::GetAttack() const { return attack; }
int Pokemon::GetSpAttack() const { return spAttack; }
int Pokemon::GetDefense() const { return defense; }
int Pokemon::GetSpDefense() const { return spDefense; }
int Pokemon::GetSpeed() const { return speed; }
int Pokemon::GetAccuracy() const { return accuracy; }

void Pokemon::SetName(const string& newName) { name = newName; }
string Pokemon::GetName() const { return name; }

void Pokemon::SetMoves(const Moves& move1, const Moves& move2, const Moves& move3, const Moves& move4) {
    moveSet.at(0) = move1;
    moveSet.at(1) = move2;
    moveSet.at(2) = move3;
    moveSet.at(3) = move4;
}

vector<Moves> Pokemon::GetMoves() const { return moveSet; }