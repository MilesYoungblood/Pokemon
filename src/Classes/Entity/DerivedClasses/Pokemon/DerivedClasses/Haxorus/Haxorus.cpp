//
// Created by Miles on 11/24/2023.
//

#include "Haxorus.h"

Haxorus::Haxorus() : Pokemon(48, 76, 147, 90, 60, 70, 97) {}

Haxorus::Haxorus(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Haxorus::getName() const {
    return "Haxorus";
}

Type Haxorus::getType(bool type1) const {
    return type1 ? Type::DRAGON : Type::NONE;
}

int Haxorus::getCatchRate() const {
    return 45;
}

Pokemon::Id Haxorus::getId() const {
    return Pokemon::Id::HAXORUS;
}
