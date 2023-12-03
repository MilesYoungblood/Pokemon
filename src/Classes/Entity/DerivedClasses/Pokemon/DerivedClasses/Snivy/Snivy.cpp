//
// Created by Miles on 12/2/2023.
//

#include "Snivy.h"

Snivy::Snivy() : Pokemon(87.5, 1, 45, 45, 55, 45, 55, 63) {}

std::string Snivy::getName() const {
    return "Snivy";
}

std::string Snivy::getSpecies() const {
    return "Grass Snake";
}

Type Snivy::getType(bool type1) const {
    return type1 ? Type::GRASS : Type::NONE;
}

double Snivy::getHeight() const {
    return 0.6;
}

double Snivy::getWeight() const {
    return 8.1;
}

int Snivy::getCatchRate() const {
    return 45;
}

Pokemon::Id Snivy::getId() const {
    return Pokemon::Id::SNIVY;
}
