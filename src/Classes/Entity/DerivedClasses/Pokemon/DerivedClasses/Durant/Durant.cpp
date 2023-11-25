//
// Created by Miles on 11/24/2023.
//

#include "Durant.h"

Durant::Durant() : Pokemon(1, 58, 109, 112, 48, 48, 109) {}

Durant::Durant(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Durant::getName() const {
    return "Durant";
}

Type Durant::getType(bool type1) const {
    return type1 ? Type::BUG : Type::STEEL;
}

int Durant::getCatchRate() const {
    return 90;
}

Pokemon::Id Durant::getId() const {
    return Pokemon::Id::DURANT;
}
