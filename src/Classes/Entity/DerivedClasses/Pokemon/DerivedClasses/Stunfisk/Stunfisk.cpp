//
// Created by Miles on 11/24/2023.
//

#include "Stunfisk.h"

Stunfisk::Stunfisk() : Pokemon(1, 109, 66, 84, 81, 99, 32) {}

Stunfisk::Stunfisk(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Stunfisk::getName() const {
    return "Stunfisk";
}

Type Stunfisk::getType(bool type1) const {
    return type1 ? Type::GROUND : Type::ELECTRIC;
}

int Stunfisk::getCatchRate() const {
    return 75;
}

Pokemon::Id Stunfisk::getId() const {
    return Pokemon::Id::STUNFISK;
}
