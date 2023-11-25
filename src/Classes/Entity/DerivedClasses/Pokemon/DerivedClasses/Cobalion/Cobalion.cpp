//
// Created by Miles on 11/24/2023.
//

#include "Cobalion.h"

Cobalion::Cobalion() : Pokemon(42, 91, 90, 129, 90, 72, 108) {}

Cobalion::Cobalion(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Cobalion::getName() const {
    return "Cobalion";
}

Type Cobalion::getType(bool type1) const {
    return type1 ? Type::STEEL : Type::FIGHTING;
}

int Cobalion::getCatchRate() const {
    return 3;
}

Pokemon::Id Cobalion::getId() const {
    return Pokemon::Id::COBALION;
}
