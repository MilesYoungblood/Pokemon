//
// Created by Miles on 12/2/2023.
//

#include "Tepig.h"

Tepig::Tepig() : Pokemon(Ability::Id::BLAZE, 87.5, 1, 65, 63, 45, 45, 45, 45) {}

std::string Tepig::getName() const {
    return "Tepig";
}

std::string Tepig::getSpecies() const {
    return "Fire Pig";
}

Type Tepig::getType(bool type1) const {
    return type1 ? Type::FIRE : Type::NONE;
}

double Tepig::getHeight() const {
    return 0.5;
}

double Tepig::getWeight() const {
    return 9.9;
}

int Tepig::getCatchRate() const {
    return 45;
}

Pokemon::Id Tepig::getId() const {
    return Pokemon::Id::TEPIG;
}
