//
// Created by Miles on 12/2/2023.
//

#include "Patrat.h"

Patrat::Patrat() : Pokemon(0.5, 1, 45, 55, 39, 35, 39, 42) {}

std::string Patrat::getName() const {
    return "Patrat";
}

std::string Patrat::getSpecies() const {
    return "Scout";
}

Type Patrat::getType(bool type1) const {
    return type1 ? Type::NORMAL : Type::NONE;
}

double Patrat::getHeight() const {
    return 0.5;
}

double Patrat::getWeight() const {
    return 11.6;
}

int Patrat::getCatchRate() const {
    return 255;
}

Pokemon::Id Patrat::getId() const {
    return Pokemon::Id::PATRAT;
}
