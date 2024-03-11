//
// Created by Miles on 12/16/2023.
//

#include "Simipour.h"

Simipour::Simipour() : Pokemon(Ability::Id::GLUTTONY, 87.5, 1, 75, 98, 63, 98, 63, 101) {}

std::string Simipour::getName() const {
    return "Simipour";
}

std::string Simipour::getSpecies() const {
    return "Geyser";
}

Type Simipour::getType1() const {
    return Type::WATER;
}

double Simipour::getHeight() const {
    return 1.0;
}

double Simipour::getWeight() const {
    return 29.0;
}

int Simipour::getCatchRate() const {
    return 75;
}

Pokemon::Id Simipour::getId() const {
    return Pokemon::Id::SIMIPOUR;
}

namespace {
    std::jthread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(pokemonMutex);
        pokemonMap["Simipour"] = [] -> std::unique_ptr<Pokemon> { return std::make_unique<Simipour>(); };
    });
}
