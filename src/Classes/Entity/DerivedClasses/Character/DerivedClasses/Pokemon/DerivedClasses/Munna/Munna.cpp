//
// Created by Miles on 12/16/2023.
//

#include "Munna.h"

Munna::Munna() : Pokemon(binomial() ? Ability::Id::FOREWARN : Ability::Id::SYNCHRONIZE, 50.0, 1, 76, 25, 45, 67, 55, 24) {}

std::string Munna::getName() const {
    return "Munna";
}

std::string Munna::getSpecies() const {
    return "Dream Eater";
}

Type Munna::getType1() const {
    return Type::PSYCHIC;
}

double Munna::getHeight() const {
    return 0.6;
}

double Munna::getWeight() const {
    return 23.3;
}

int Munna::getCatchRate() const {
    return 190;
}

Pokemon::Id Munna::getId() const {
    return Pokemon::Id::MUNNA;
}

namespace {
    std::jthread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(pokemonMutex);
        pokemonMap["Munna"] = [] -> std::unique_ptr<Pokemon> { return std::make_unique<Munna>(); };
    });
}
