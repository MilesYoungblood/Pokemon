//
// Created by Miles on 11/24/2023.
//

#include "Genesect.h"

Genesect::Genesect() : Pokemon(15, 71, 120, 95, 120, 95, 99) {}

Genesect::Genesect(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Genesect::getName() const {
    return "Genesect";
}

Type Genesect::getType(bool type1) const {
    return type1 ? Type::BUG : Type::STEEL;
}

int Genesect::getCatchRate() const {
    return 3;
}

Pokemon::Id Genesect::getId() const {
    return Pokemon::Id::GENESECT;
}
