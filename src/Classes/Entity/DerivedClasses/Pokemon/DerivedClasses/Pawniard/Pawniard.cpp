//
// Created by Miles on 11/24/2023.
//

#include "Pawniard.h"

Pawniard::Pawniard() : Pokemon(1, 45, 85, 70, 40, 40, 60) {}

Pawniard::Pawniard(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Pawniard::getName() const {
    return "Pawniard";
}

Type Pawniard::getType(bool type1) const {
    return type1 ? Type::DARK : Type::STEEL;
}

int Pawniard::getCatchRate() const {
    return 120;
}

Pokemon::Id Pawniard::getId() const {
    return Pokemon::Id::PAWNIARD;
}
