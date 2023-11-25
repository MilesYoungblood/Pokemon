//
// Created by Miles on 11/24/2023.
//

#include "Zekrom.h"

Zekrom::Zekrom() : Pokemon(50, 100, 150, 120, 120, 100, 90) {}

Zekrom::Zekrom(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Zekrom::getName() const {
    return "Zekrom";
}

Type Zekrom::getType(bool type1) const {
    return type1 ? Type::DRAGON : Type::ELECTRIC;
}

int Zekrom::getCatchRate() const {
    return 3;
}

Pokemon::Id Zekrom::getId() const {
    return Pokemon::Id::ZEKROM;
}
