//
// Created by Miles on 11/24/2023.
//

#include "Golurk.h"

Golurk::Golurk() : Pokemon(43, 89, 124, 80, 55, 80, 55) {}

Golurk::Golurk(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Golurk::getName() const {
    return "Golurk";
}

Type Golurk::getType(bool type1) const {
    return type1 ? Type::GROUND : Type::GHOST;
}

int Golurk::getCatchRate() const {
    return 90;
}

Pokemon::Id Golurk::getId() const {
    return Pokemon::Id::GOLURK;
}
