//
// Created by Miles on 11/24/2023.
//

#include "Rufflet.h"

Rufflet::Rufflet() : Pokemon(1, 70, 83, 50, 37, 50, 60) {}

Rufflet::Rufflet(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Rufflet::getName() const {
    return "Rufflet";
}

Type Rufflet::getType(bool type1) const {
    return type1 ? Type::NORMAL : Type::FLYING;
}

int Rufflet::getCatchRate() const {
    return 190;
}

Pokemon::Id Rufflet::getId() const {
    return Pokemon::Id::RUFFLET;
}
