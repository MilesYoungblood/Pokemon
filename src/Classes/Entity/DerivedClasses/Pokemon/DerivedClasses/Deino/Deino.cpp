//
// Created by Miles on 11/24/2023.
//

#include "Deino.h"

Deino::Deino() : Pokemon(1, 52, 65, 50, 45, 50, 38) {}

Deino::Deino(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Deino::getName() const {
    return "Deino";
}

Type Deino::getType(bool type1) const {
    return type1 ? Type::DARK : Type::DRAGON;
}

int Deino::getCatchRate() const {
    return 45;
}

Pokemon::Id Deino::getId() const {
    return Pokemon::Id::DEINO;
}
