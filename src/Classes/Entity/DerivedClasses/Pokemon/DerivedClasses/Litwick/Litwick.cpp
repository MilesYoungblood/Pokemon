//
// Created by Miles on 11/24/2023.
//

#include "Litwick.h"

Litwick::Litwick() : Pokemon(1, 50, 30, 55, 65, 55, 20) {}

Litwick::Litwick(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Litwick::getName() const {
    return "Litwick";
}

Type Litwick::getType(bool type1) const {
    return type1 ? Type::GHOST : Type::FIRE;
}

int Litwick::getCatchRate() const {
    return 190;
}

Pokemon::Id Litwick::getId() const {
    return Pokemon::Id::LITWICK;
}
