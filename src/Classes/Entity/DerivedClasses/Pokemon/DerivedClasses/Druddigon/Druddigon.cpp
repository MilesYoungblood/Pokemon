//
// Created by Miles on 11/24/2023.
//

#include "Druddigon.h"

Druddigon::Druddigon() : Pokemon(1, 77, 120, 90, 60, 90, 48) {}

Druddigon::Druddigon(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Druddigon::getName() const {
    return "Druddigon";
}

Type Druddigon::getType(bool type1) const {
    return type1 ? Type::DRAGON : Type::NONE;
}

int Druddigon::getCatchRate() const {
    return 45;
}

Pokemon::Id Druddigon::getId() const {
    return Pokemon::Id::DRUDDIGON;
}
