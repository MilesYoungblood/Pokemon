//
// Created by miles on 5/5/2022.
//

#include "Pokemon.h"

Pokemon::Pokemon() {
    maxHp = 300;
    currentHp = 300;
    attack = 6;
    spAttack = 6;
    defense = 6;
    spDefense = 6;
    speed = 6;
    accuracy = 6;

    baseAttack = 100;
    baseSpAttack = 100;
    baseDefense = 100;
    baseSpDefense = 100;
    baseSpeed = 100;

    name = "No name";
    status = "No status";
}

Pokemon::Pokemon(const std::string& nameToSet, int hpToSet) {
    maxHp = hpToSet;
    currentHp = hpToSet;
    attack = 1;
    spAttack = 1;
    defense = 1;
    spDefense = 1;
    speed = 1;
    accuracy = 1;

    baseAttack = 100;
    baseSpAttack = 100;
    baseDefense = 100;
    baseSpDefense = 100;
    baseSpeed = 100;

    name = nameToSet;
    status = "No status";
}

void Pokemon::SetHP(int val) { currentHp = val; }
void Pokemon::SetAttack(int val) { attack = val; }
void Pokemon::SetSpAttack(int val) { spAttack = val; }
void Pokemon::SetDefense(int val) { defense = val; }
void Pokemon::SetSpDefense(int val) { spDefense = val; }
void Pokemon::SetSpeed(int val) { speed = val; }
void Pokemon::SetAccuracy(int val) { accuracy = val; }

int Pokemon::GetMaxHP() const { return maxHp; }
int Pokemon::GetHP() const { return currentHp; }
int Pokemon::GetAttack() const { return attack; }
int Pokemon::GetSpAttack() const { return spAttack; }
int Pokemon::GetDefense() const { return defense; }
int Pokemon::GetSpDefense() const { return spDefense; }
int Pokemon::GetSpeed() const { return speed; }
int Pokemon::GetAccuracy() const { return accuracy; }

void Pokemon::SetBaseStats(int bAttack, int bSpAttack, int bDefense, int bSpDefense, int bSpeed) {
    baseAttack = bAttack;
    baseSpAttack = bSpAttack;
    baseDefense = bDefense;
    baseSpDefense = bSpDefense;
    baseSpeed = bSpeed;
}

int Pokemon::GetBaseAttack() const { return baseAttack; }
int Pokemon::GetBaseSpAttack() const { return baseSpAttack; }
int Pokemon::GetBaseDefense() const { return baseDefense; }
int Pokemon::GetBaseSpDefense() const { return baseSpDefense; }
int Pokemon::GetBaseSpeed() const { return baseSpeed; }

void Pokemon::SetName(const std::string& newName) { name = newName; }
std::string Pokemon::GetName() const { return name; }

void Pokemon::SetStatus(const std::string &newStatus) {
    status = newStatus;
}
std::string Pokemon::GetStatus() {
    return status;
}

void Pokemon::SetMoves(const Moves& move1, const Moves& move2, const Moves& move3, const Moves& move4) {
    moveSet[0] = move1;
    moveSet[1] = move2;
    moveSet[2] = move3;
    moveSet[3] = move4;
}

Moves& Pokemon::GetMove(int move) { return moveSet[move]; }