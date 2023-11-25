//
// Created by Miles on 11/24/2023.
//

#include "Tornadus.h"

Tornadus::Tornadus() : Pokemon(40, 79, 115, 70, 125, 80, 111) {}

Tornadus::Tornadus(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Tornadus::getName() const {
    return "Tornadus";
}

Type Tornadus::getType(bool type1) const {
    return type1 ? Type::FLYING : Type::NONE;
}

int Tornadus::getCatchRate() const {
    return 3;
}

Pokemon::Id Tornadus::getId() const {
    return Pokemon::Id::TORNADUS;
}
