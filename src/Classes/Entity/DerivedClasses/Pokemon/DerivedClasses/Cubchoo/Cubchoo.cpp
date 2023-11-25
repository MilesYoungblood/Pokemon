//
// Created by Miles on 11/24/2023.
//

#include "Cubchoo.h"

Cubchoo::Cubchoo() : Pokemon(1, 55, 70, 40, 60, 40, 40) {}

Cubchoo::Cubchoo(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Cubchoo::getName() const {
    return "Cubchoo";
}

Type Cubchoo::getType(bool type1) const {
    return type1 ? Type::ICE : Type::NONE;
}

int Cubchoo::getCatchRate() const {
    return 120;
}

Pokemon::Id Cubchoo::getId() const {
    return Pokemon::Id::CUBCHOO;
}
