//
// Created by Miles on 11/24/2023.
//

#include "Landorus.h"

Landorus::Landorus() : Pokemon(70, 89, 125, 90, 115, 80, 101) {}

Landorus::Landorus(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Landorus::getName() const {
    return "Landorus";
}

Type Landorus::getType(bool type1) const {
    return type1 ? Type::GROUND : Type::FLYING;
}

int Landorus::getCatchRate() const {
    return 3;
}

Pokemon::Id Landorus::getId() const {
    return Pokemon::Id::LANDORUS;
}
