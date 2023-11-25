//
// Created by Miles on 11/24/2023.
//

#include "Volcarona.h"

Volcarona::Volcarona() : Pokemon(59, 85, 60, 65, 135, 105, 100) {}

Volcarona::Volcarona(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Volcarona::getName() const {
    return "Volcarona";
}

Type Volcarona::getType(bool type1) const {
    return type1 ? Type::BUG : Type::FIRE;
}

int Volcarona::getCatchRate() const {
    return 15;
}

Pokemon::Id Volcarona::getId() const {
    return Pokemon::Id::VOLCARONA;
}
