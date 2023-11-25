//
// Created by Miles on 11/24/2023.
//

#include "Mienshao.h"

Mienshao::Mienshao() : Pokemon(50, 65, 125, 60, 95, 60, 105) {}

Mienshao::Mienshao(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Mienshao::getName() const {
    return "Mienshao";
}

Type Mienshao::getType(bool type1) const {
    return type1 ? Type::FIGHTING : Type::NONE;
}

int Mienshao::getCatchRate() const {
    return 45;
}

Pokemon::Id Mienshao::getId() const {
    return Pokemon::Id::MIENSHAO;
}
