//
// Created by Miles on 11/24/2023.
//

#include "Golett.h"

Golett::Golett() : Pokemon(1, 59, 74, 50, 35, 50, 35) {}

Golett::Golett(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Golett::getName() const {
    return "Golett";
}

Type Golett::getType(bool type1) const {
    return type1 ? Type::GROUND : Type::GHOST;
}

int Golett::getCatchRate() const {
    return 190;
}

Pokemon::Id Golett::getId() const {
    return Pokemon::Id::GOLETT;
}
