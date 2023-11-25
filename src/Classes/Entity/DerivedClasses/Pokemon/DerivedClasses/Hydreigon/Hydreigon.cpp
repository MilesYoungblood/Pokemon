//
// Created by Miles on 11/24/2023.
//

#include "Hydreigon.h"

Hydreigon::Hydreigon() : Pokemon(64, 92, 105, 90, 125, 90, 98) {}

Hydreigon::Hydreigon(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Hydreigon::getName() const {
    return "Hydreigon";
}

Type Hydreigon::getType(bool type1) const {
    return type1 ? Type::DARK : Type::DRAGON;
}

int Hydreigon::getCatchRate() const {
    return 45;
}

Pokemon::Id Hydreigon::getId() const {
    return Pokemon::Id::HYDREIGON;
}
