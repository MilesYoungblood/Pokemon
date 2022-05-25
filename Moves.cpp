//
// Created by miles on 5/5/2022.
//

#include "Moves.h"

using namespace std;

Moves::Moves() {
    pp = 0;
    damage = 0;
    type = "No type";
    name = "No name";
}

Moves::Moves(const string& nameToSet, const string& typeToSet, int ppToSet, int damageToSet) {
    pp = ppToSet;
    damage = damageToSet;
    type = typeToSet;
    name = nameToSet;
}

void Moves::SetPP(int val) { pp = val; }
int Moves::GetPP() const { return pp; }

void Moves::SetDamage(int val) { damage = val; }
int Moves::GetDamage() const { return damage; }

__attribute__((unused)) void Moves::SetType(string& val) { type = val; }
__attribute__((unused)) string Moves::GetType() const { return type; }

void Moves::SetName(const string &newName) { name = newName; }
string Moves::GetName() const { return name; }