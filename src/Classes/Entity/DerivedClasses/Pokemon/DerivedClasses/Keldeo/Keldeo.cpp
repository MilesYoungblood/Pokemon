//
// Created by Miles on 11/24/2023.
//

#include "Keldeo.h"

Keldeo::Keldeo() : Pokemon(15, 91, 72, 90, 129, 90, 108) {}

Keldeo::Keldeo(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Keldeo::getName() const {
    return "Keldeo";
}

Type Keldeo::getType(bool type1) const {
    return type1 ? Type::WATER : Type::FIGHTING;
}

int Keldeo::getCatchRate() const {
    return 3;
}

Pokemon::Id Keldeo::getId() const {
    return Pokemon::Id::KELDEO;
}
