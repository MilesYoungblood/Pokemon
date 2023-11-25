//
// Created by Miles on 11/24/2023.
//

#include "Reshiram.h"

Reshiram::Reshiram() : Pokemon(50, 100, 120, 100, 150, 120, 90) {}

Reshiram::Reshiram(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Reshiram::getName() const {
    return "Reshiram";
}

Type Reshiram::getType(bool type1) const {
    return type1 ? Type::DRAGON : Type::FIRE;
}

int Reshiram::getCatchRate() const {
    return 3;
}

Pokemon::Id Reshiram::getId() const {
    return Pokemon::Id::RESHIRAM;
}
