//
// Created by Miles on 11/24/2023.
//

#include "Meloetta.h"

Meloetta::Meloetta() : Pokemon(15, 100, 77, 77, 128, 128, 90) {}

Meloetta::Meloetta(int level, int hp, int bAttack, int bDefense, int bSpAttack, int bSpDefense, int bSpeed)
        : Pokemon(level, hp, bAttack, bDefense, bSpAttack, bSpDefense, bSpeed) {}

std::string Meloetta::getName() const {
    return "Meloetta";
}

Type Meloetta::getType(bool type1) const {
    return type1 ? Type::NORMAL : Type::PSYCHIC;
}

int Meloetta::getCatchRate() const {
    return 3;
}

Pokemon::Id Meloetta::getId() const {
    return Pokemon::Id::MELOETTA;
}
