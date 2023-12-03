//
// Created by Miles on 12/2/2023.
//

#include "Emboar.h"

Emboar::Emboar() : Pokemon(87.5, 36, 110, 123, 65, 100, 65, 65) {}

std::string Emboar::getName() const {
    return "Emboar";
}

std::string Emboar::getSpecies() const {
    return "Mega Fire Pig";
}

Type Emboar::getType(bool type1) const {
    return type1 ? Type::FIRE : Type::FIGHTING;
}

double Emboar::getHeight() const {
    return 1.6;
}

double Emboar::getWeight() const {
    return 150.0;
}

int Emboar::getCatchRate() const {
    return 45;
}

Pokemon::Id Emboar::getId() const {
    return Pokemon::Id::EMBOAR;
}

