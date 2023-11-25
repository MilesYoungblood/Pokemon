//
// Created by Miles on 11/24/2023.
//

#include "Vullaby.h"

Vullaby::Vullaby() : Pokemon(1, 70, 55, 75, 45, 65, 60) {}

Vullaby::Vullaby(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Vullaby::getName() const {
    return "Vullaby";
}

Type Vullaby::getType(bool type1) const {
    return type1 ? Type::DARK : Type::FLYING;
}

int Vullaby::getCatchRate() const {
    return 190;
}

Pokemon::Id Vullaby::getId() const {
    return Pokemon::Id::VULLABY;
}
