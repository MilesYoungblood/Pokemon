//
// Created by Miles on 11/24/2023.
//

#include "Kyurem.h"

Kyurem::Kyurem() : Pokemon(75, 125, 130, 90, 130, 90, 95) {}

Kyurem::Kyurem(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Kyurem::getName() const {
    return "Kyurem";
}

Type Kyurem::getType(bool type1) const {
    return type1 ? Type::DRAGON : Type::ICE;
}

int Kyurem::getCatchRate() const {
    return 3;
}

Pokemon::Id Kyurem::getId() const {
    return Pokemon::Id::KYUREM;
}
