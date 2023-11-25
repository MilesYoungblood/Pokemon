//
// Created by Miles on 11/24/2023.
//

#include "Terrakion.h"

Terrakion::Terrakion() : Pokemon(42, 91, 129, 90, 72, 90, 108) {}

Terrakion::Terrakion(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Terrakion::getName() const {
    return "Terrakion";
}

Type Terrakion::getType(bool type1) const {
    return type1 ? Type::ROCK : Type::FIGHTING;
}

int Terrakion::getCatchRate() const {
    return 3;
}

Pokemon::Id Terrakion::getId() const {
    return Pokemon::Id::TERRAKION;
}
