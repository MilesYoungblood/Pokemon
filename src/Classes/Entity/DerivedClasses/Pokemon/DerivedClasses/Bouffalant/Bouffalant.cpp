//
// Created by Miles on 11/24/2023.
//

#include "Bouffalant.h"

Bouffalant::Bouffalant() : Pokemon(1, 95, 110, 95, 40, 95, 55) {}

Bouffalant::Bouffalant(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Bouffalant::getName() const {
    return "Bouffalant";
}

Type Bouffalant::getType(bool type1) const {
    return type1 ? Type::NORMAL : Type::NONE;
}

int Bouffalant::getCatchRate() const {
    return 45;
}

Pokemon::Id Bouffalant::getId() const {
    return Pokemon::Id::BOUFFALANT;
}
