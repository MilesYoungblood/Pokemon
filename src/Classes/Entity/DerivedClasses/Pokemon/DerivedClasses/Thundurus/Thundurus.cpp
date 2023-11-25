//
// Created by Miles on 11/24/2023.
//

#include "Thundurus.h"

Thundurus::Thundurus() : Pokemon(40, 79, 115, 70, 125, 80, 111) {}

Thundurus::Thundurus(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Thundurus::getName() const {
    return "Thundurus";
}

Type Thundurus::getType(bool type1) const {
    return type1 ? Type::ELECTRIC : Type::FLYING;
}

int Thundurus::getCatchRate() const {
    return 3;
}

Pokemon::Id Thundurus::getId() const {
    return Pokemon::Id::THUNDURUS;
}
