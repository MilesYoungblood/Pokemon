//
// Created by Miles on 12/2/2023.
//

#include "Dewott.h"

Dewott::Dewott() : Pokemon(Ability::Id::TORRENT, 87.5, 17, 75, 75, 60, 83, 60, 60) {}

std::string Dewott::getName() const {
    return "Dewott";
}

std::string Dewott::getSpecies() const {
    return "Discipline";
}

Type Dewott::getType(bool type1) const {
    return type1 ? Type::WATER : Type::NONE;
}

double Dewott::getHeight() const {
    return 0.8;
}

double Dewott::getWeight() const {
    return 24.5;
}

int Dewott::getCatchRate() const {
    return 45;
}

Pokemon::Id Dewott::getId() const {
    return Pokemon::Id::DEWOTT;
}
