//
// Created by Miles on 11/24/2023.
//

#include "Chandelure.h"

Chandelure::Chandelure() : Pokemon(41, 60, 55, 90, 145, 90, 80) {}

Chandelure::Chandelure(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Chandelure::getName() const {
    return "Chandelure";
}

Type Chandelure::getType(bool type1) const {
    return type1 ? Type::GHOST : Type::FIRE;
}

int Chandelure::getCatchRate() const {
    return 45;
}

Pokemon::Id Chandelure::getId() const {
    return Pokemon::Id::CHANDELURE;
}