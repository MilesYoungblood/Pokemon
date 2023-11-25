//
// Created by Miles on 11/24/2023.
//

#include "Shelmet.h"

Shelmet::Shelmet() : Pokemon(1, 50, 40, 85, 40, 65, 25) {}

Shelmet::Shelmet(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Shelmet::getName() const {
    return "Shelmet";
}

Type Shelmet::getType(bool type1) const {
    return type1 ? Type::BUG : Type::NONE;
}

int Shelmet::getCatchRate() const {
    return 200;
}

Pokemon::Id Shelmet::getId() const {
    return Pokemon::Id::SHELMET;
}
