//
// Created by Miles on 11/24/2023.
//

#include "Braviary.h"

Braviary::Braviary() : Pokemon(54, 100, 123, 75, 57, 75, 80) {}

Braviary::Braviary(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Braviary::getName() const {
    return "Braviary";
}

Type Braviary::getType(bool type1) const {
    return type1 ? Type::NORMAL : Type::FLYING;
}

int Braviary::getCatchRate() const {
    return 60;
}

Pokemon::Id Braviary::getId() const {
    return Pokemon::Id::BRAVIARY;
}
