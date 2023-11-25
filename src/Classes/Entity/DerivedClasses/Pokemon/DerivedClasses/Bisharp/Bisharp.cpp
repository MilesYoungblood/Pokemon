//
// Created by Miles on 11/24/2023.
//

#include "Bisharp.h"

Bisharp::Bisharp() : Pokemon(52, 65, 125, 100, 60, 70, 70) {}

Bisharp::Bisharp(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Bisharp::getName() const {
    return "Bisharp";
}

Type Bisharp::getType(bool type1) const {
    return type1 ? Type::DARK : Type::STEEL;
}

int Bisharp::getCatchRate() const {
    return 45;
}

Pokemon::Id Bisharp::getId() const {
    return Pokemon::Id::BISHARP;
}
