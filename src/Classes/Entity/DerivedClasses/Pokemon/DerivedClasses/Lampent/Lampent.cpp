//
// Created by Miles on 11/24/2023.
//

#include "Lampent.h"

Lampent::Lampent() : Pokemon(41, 60, 40, 60, 95, 60, 55) {}

Lampent::Lampent(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Lampent::getName() const {
    return "Lampent";
}

Type Lampent::getType(bool type1) const {
    return type1 ? Type::GHOST : Type::FIRE;
}

int Lampent::getCatchRate() const {
    return 90;
}

Pokemon::Id Lampent::getId() const {
    return Pokemon::Id::LAMPENT;
}
