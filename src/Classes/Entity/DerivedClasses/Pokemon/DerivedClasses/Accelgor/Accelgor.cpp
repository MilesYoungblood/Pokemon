//
// Created by Miles on 11/24/2023.
//

#include "Accelgor.h"

Accelgor::Accelgor() : Pokemon(1, 80, 70, 40, 100, 60, 145) {}

Accelgor::Accelgor(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Accelgor::getName() const {
    return "Accelgor";
}

Type Accelgor::getType(bool type1) const {
    return type1 ? Type::BUG : Type::NONE;
}

int Accelgor::getCatchRate() const {
    return 75;
}

Pokemon::Id Accelgor::getId() const {
    return Pokemon::Id::ACCELGOR;
}
