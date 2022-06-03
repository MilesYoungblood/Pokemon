//
// Created by miles on 5/5/2022.
//

#include "Moves.h"

Moves::Moves() {
    pp = 0;
    damage = 0;
    type = "No type";
    name = "No name";
}

Moves::Moves(const std::string& nameToSet, const std::string& typeToSet, int ppToSet, int damageToSet) {
    pp = ppToSet;
    damage = damageToSet;
    type = typeToSet;
    name = nameToSet;
}

Moves::Moves(const Moves& moveToCopy) {
    pp = moveToCopy.pp;
    damage = moveToCopy.damage;
    type = moveToCopy.type;
    name = moveToCopy.name;
}

void Moves::SetPP(int val) { pp = val; }
int Moves::GetPP() const { return pp; }

void Moves::SetDamage(int val) { damage = val; }
int Moves::GetDamage() const { return damage; }

__attribute__((unused)) void Moves::SetType(std::string& val) { type = val; }
__attribute__((unused)) std::string Moves::GetType() const { return type; }

void Moves::SetName(const std::string &newName) { name = newName; }
std::string Moves::GetName() const { return name; }