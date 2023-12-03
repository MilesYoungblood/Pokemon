//
// Created by Miles on 12/2/2023.
//

#include "Servine.h"

Servine::Servine() : Pokemon(87.5, 17, 60, 60, 75, 60, 75, 83) {}

std::string Servine::getName() const {
    return "Servine";
}

std::string Servine::getSpecies() const {
    return "Grass Snake";
}

Type Servine::getType(bool type1) const {
    return type1 ? Type::GRASS : Type::NONE;
}

double Servine::getHeight() const {
    return 0.8;
}

double Servine::getWeight() const {
    return 16.0;
}

int Servine::getCatchRate() const {
    return 45;
}

Pokemon::Id Servine::getId() const {
    return Pokemon::Id::SERVINE;
}
