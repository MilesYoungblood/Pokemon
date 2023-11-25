//
// Created by Miles on 11/24/2023.
//

#include "Beartic.h"

Beartic::Beartic() : Pokemon(37, 95, 130, 80, 70, 80, 50) {}

Beartic::Beartic(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Beartic::getName() const {
    return "Beartic";
}

Type Beartic::getType(bool type1) const {
    return type1 ? Type::ICE : Type::NONE;
}

int Beartic::getCatchRate() const {
    return 60;
}

Pokemon::Id Beartic::getId() const {
    return Pokemon::Id::BEARTIC;
}
