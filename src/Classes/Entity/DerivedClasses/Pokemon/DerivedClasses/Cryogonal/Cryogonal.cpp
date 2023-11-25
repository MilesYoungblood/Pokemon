//
// Created by Miles on 11/24/2023.
//

#include "Cryogonal.h"

Cryogonal::Cryogonal() : Pokemon(1, 80, 50, 50, 95, 135, 105) {}

Cryogonal::Cryogonal(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Cryogonal::getName() const {
    return "Cryogonal";
}

Type Cryogonal::getType(bool type1) const {
    return type1 ? Type::ICE : Type::NONE;
}

int Cryogonal::getCatchRate() const {
    return 25;
}

Pokemon::Id Cryogonal::getId() const {
    return Pokemon::Id::CRYOGONAL;
}
