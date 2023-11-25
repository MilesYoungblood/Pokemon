//
// Created by Miles on 11/24/2023.
//

#include "Zweilous.h"

Zweilous::Zweilous() : Pokemon(50, 52, 65, 50, 45, 60, 38) {}

Zweilous::Zweilous(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Zweilous::getName() const {
    return "Zweilous";
}

Type Zweilous::getType(bool type1) const {
    return type1 ? Type::DARK : Type::DRAGON;
}

int Zweilous::getCatchRate() const {
    return 45;
}

Pokemon::Id Zweilous::getId() const {
    return Pokemon::Id::ZWEILOUS;
}
