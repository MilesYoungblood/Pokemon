//
// Created by Miles on 11/24/2023.
//

#include "Heatmor.h"

Heatmor::Heatmor() : Pokemon(1, 85, 97, 66, 105, 66, 65) {}

Heatmor::Heatmor(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Heatmor::getName() const {
    return "Heatmor";
}

Type Heatmor::getType(bool type1) const {
    return type1 ? Type::FIRE : Type::NONE;
}

int Heatmor::getCatchRate() const {
    return 90;
}

Pokemon::Id Heatmor::getId() const {
    return Pokemon::Id::HEATMOR;
}
