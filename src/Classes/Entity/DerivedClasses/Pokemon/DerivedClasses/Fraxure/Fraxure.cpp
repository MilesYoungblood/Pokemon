//
// Created by Miles on 11/24/2023.
//

#include "Fraxure.h"

Fraxure::Fraxure() : Pokemon(38, 66, 117, 70, 40, 50, 67) {}

Fraxure::Fraxure(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Fraxure::getName() const {
    return "Fraxure";
}

Type Fraxure::getType(bool type1) const {
    return type1 ? Type::DRAGON : Type::NONE;
}

int Fraxure::getCatchRate() const {
    return 60;
}

Pokemon::Id Fraxure::getId() const {
    return Pokemon::Id::FRAXURE;
}
