//
// Created by Miles on 12/2/2023.
//

#include "Lillipup.h"

Lillipup::Lillipup() : Pokemon(0.5, 1, 45, 60, 45, 25, 45, 55) {}

std::string Lillipup::getName() const {
    return "Lillipup";
}

std::string Lillipup::getSpecies() const {
    return "Puppy";
}

Type Lillipup::getType(bool type1) const {
    return type1 ? Type::NORMAL : Type::NONE;
}

double Lillipup::getHeight() const {
    return 0.4;
}

double Lillipup::getWeight() const {
    return 4.1;
}

int Lillipup::getCatchRate() const {
    return 255;
}

Pokemon::Id Lillipup::getId() const {
    return Pokemon::Id::LILLIPUP;
}
