//
// Created by miles on 5/5/2022.
//

#include "Moves.h"

Moves::Moves() {
    maxPp = 0;
    pp = 0;
    power = 0;
    type = "No type";
    name = "No name";
}

Moves::Moves(const std::string& name, const std::string& type, int pp, int power) {
    maxPp = pp;
    this->pp = pp;
    this->power = power;
    this->type = type;
    this->name = name;
}

Moves::Moves(const Moves& moveToCopy) {
    pp = moveToCopy.pp;
    maxPp = moveToCopy.maxPp;
    power = moveToCopy.power;
    type = moveToCopy.type;
    name = moveToCopy.name;
}

void Moves::SetPP(int newPP) { pp = newPP; }
int Moves::GetPP() const { return pp; }

int Moves::GetMaxPP() const { return maxPp; }

int Moves::GetPower() const { return power; }

__attribute__((unused)) void Moves::SetType(std::string& newType) { type = newType; }
__attribute__((unused)) std::string Moves::GetType() const { return type; }

std::string Moves::GetName() const { return name; }