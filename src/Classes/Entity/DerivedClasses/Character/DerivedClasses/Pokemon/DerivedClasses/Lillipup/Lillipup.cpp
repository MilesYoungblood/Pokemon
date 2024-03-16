//
// Created by Miles on 12/2/2023.
//

#include "Lillipup.h"

Lillipup::Lillipup() : Pokemon(binomial() ? Ability::Id::VITAL_SPIRIT : Ability::Id::PICKUP, 50.0, 1,
                               45, 60, 45, 25, 45, 55) {}

std::string Lillipup::getName() const {
    return "Lillipup";
}

std::string Lillipup::getSpecies() const {
    return "Puppy";
}

Type Lillipup::getType1() const {
    return Type::NORMAL;
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

namespace {
    std::jthread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(pokemonMutex);
        pokemonMap["Lillipup"] = [] -> std::unique_ptr<Pokemon> { return std::make_unique<Lillipup>(); };
    });
}
