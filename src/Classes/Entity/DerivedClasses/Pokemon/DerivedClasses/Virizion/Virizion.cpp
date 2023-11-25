//
// Created by Miles on 11/24/2023.
//

#include "Virizion.h"

Virizion::Virizion() : Pokemon(42, 91, 90, 72, 90, 129, 108) {}

Virizion::Virizion(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Virizion::getName() const {
    return "Virizion";
}

Type Virizion::getType(bool type1) const {
    return type1 ? Type::GRASS : Type::FIGHTING;
}

int Virizion::getCatchRate() const {
    return 3;
}

Pokemon::Id Virizion::getId() const {
    return Pokemon::Id::VIRIZION;
}
