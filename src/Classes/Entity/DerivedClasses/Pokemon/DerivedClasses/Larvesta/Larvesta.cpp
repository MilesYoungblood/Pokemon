//
// Created by Miles on 11/24/2023.
//

#include "Larvesta.h"

Larvesta::Larvesta() : Pokemon(1, 55, 85, 55, 50, 55, 60) {}

Larvesta::Larvesta(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Larvesta::getName() const {
    return "Larvesta";
}

Type Larvesta::getType(bool type1) const {
    return type1 ? Type::BUG : Type::FIRE;
}

int Larvesta::getCatchRate() const {
    return 45;
}

Pokemon::Id Larvesta::getId() const {
    return Pokemon::Id::LARVESTA;
}
