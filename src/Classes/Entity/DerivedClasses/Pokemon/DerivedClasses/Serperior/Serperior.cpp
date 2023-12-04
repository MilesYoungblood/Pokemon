//
// Created by Miles on 12/2/2023.
//

#include "Serperior.h"

Serperior::Serperior() : Pokemon(Ability::Id::OVERGROW, 87.5, 36, 75, 75, 95, 75, 96, 113) {}

std::string Serperior::getName() const {
    return "Serperior";
}

std::string Serperior::getSpecies() const {
    return "Regal";
}

Type Serperior::getType(bool type1) const {
    return type1 ? Type::GRASS : Type::NONE;
}

double Serperior::getHeight() const {
    return 3.3;
}

double Serperior::getWeight() const {
    return 63.0;
}

int Serperior::getCatchRate() const {
    return 45;
}

Pokemon::Id Serperior::getId() const {
    return Pokemon::Id::SERPERIOR;
}
