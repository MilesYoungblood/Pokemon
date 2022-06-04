//
// Created by miles on 5/5/2022.
//

#include "Moves.h"

Moves::Moves() {
    pp = 0;
    power = 0;
    type = "No type";
    name = "No name";
}

Moves::Moves(const std::string& nameToSet, const std::string& typeToSet, int ppToSet, int damageToSet) {
    pp = ppToSet;
    power = damageToSet;
    type = typeToSet;
    name = nameToSet;
}

Moves::Moves(const Moves& moveToCopy) {
    pp = moveToCopy.pp;
    power = moveToCopy.power;
    type = moveToCopy.type;
    name = moveToCopy.name;
}

void Moves::SetPP(int val) { pp = val; }
int Moves::GetPP() const { return pp; }

__attribute__((unused)) void Moves::SetPower(int val) { power = val; }
int Moves::GetPower() const { return power; }

__attribute__((unused)) void Moves::SetType(std::string& val) { type = val; }
__attribute__((unused)) std::string Moves::GetType() const { return type; }

std::string Moves::GetName() const { return name; }