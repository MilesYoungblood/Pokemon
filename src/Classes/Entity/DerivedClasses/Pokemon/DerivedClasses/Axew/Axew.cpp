//
// Created by Miles on 11/24/2023.
//

#include "Axew.h"

Axew::Axew() : Pokemon(1, 46, 87, 60, 30, 40, 57) {}

Axew::Axew(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Axew::getName() const {
    return "Axew";
}

Type Axew::getType(bool type1) const {
    return type1 ? Type::DRAGON : Type::NONE;
}

int Axew::getCatchRate() const {
    return 75;
}

Pokemon::Id Axew::getId() const {
    return Pokemon::Id::AXEW;
}