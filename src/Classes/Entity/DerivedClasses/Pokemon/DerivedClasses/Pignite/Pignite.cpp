//
// Created by Miles on 12/2/2023.
//

#include "Pignite.h"

Pignite::Pignite() : Pokemon(Ability::Id::BLAZE, 87.5, 17, 90, 93, 55, 70, 55, 55) {}

std::string Pignite::getName() const {
    return "Pignite";
}

std::string Pignite::getSpecies() const {
    return "Fire Pig";
}

Type Pignite::getType(bool type1) const {
    return type1 ? Type::FIRE : Type::FIGHTING;
}

double Pignite::getHeight() const {
    return 1.0;
}

double Pignite::getWeight() const {
    return 55.5;
}

int Pignite::getCatchRate() const {
    return 45;
}

Pokemon::Id Pignite::getId() const {
    return Pokemon::Id::PIGNITE;
}
