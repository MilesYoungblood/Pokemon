//
// Created by Miles on 11/24/2023.
//

#include "Mienfoo.h"

Mienfoo::Mienfoo() : Pokemon(1, 45, 85, 50, 55, 50, 65) {}

Mienfoo::Mienfoo(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Mienfoo::getName() const {
    return "Mienfoo";
}

Type Mienfoo::getType(bool type1) const {
    return type1 ? Type::FIGHTING : Type::NONE;
}

int Mienfoo::getCatchRate() const {
    return 180;
}

Pokemon::Id Mienfoo::getId() const {
    return Pokemon::Id::MIENFOO;
}
