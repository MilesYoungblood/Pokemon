//
// Created by Miles on 11/24/2023.
//

#include "Mandibuzz.h"

Mandibuzz::Mandibuzz() : Pokemon(54, 110, 65, 105, 55, 95, 80) {}

Mandibuzz::Mandibuzz(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Mandibuzz::getName() const {
    return "Mandibuzz";
}

Type Mandibuzz::getType(bool type1) const {
    return type1 ? Type::DARK : Type::FLYING;
}

int Mandibuzz::getCatchRate() const {
    return 60;
}

Pokemon::Id Mandibuzz::getId() const {
    return Pokemon::Id::MANDIBUZZ;
}
