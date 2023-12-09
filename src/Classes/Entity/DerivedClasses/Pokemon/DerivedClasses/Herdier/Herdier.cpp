//
// Created by Miles on 12/2/2023.
//

#include "Herdier.h"

Herdier::Herdier() : Pokemon(binomial() ? Ability::Id::INTIMIDATE : Ability::Id::SAND_RUSH, 0.5, 16,
                             65, 80, 65, 35, 65, 60) {}

std::string Herdier::getName() const {
    return "Herdier";
}

std::string Herdier::getSpecies() const {
    return "Loyal Dog";
}

Type Herdier::getType(bool type1) const {
    return type1 ? Type::NORMAL : Type::NONE;
}

double Herdier::getHeight() const {
    return 0.9;
}

double Herdier::getWeight() const {
    return 14.7;
}

int Herdier::getCatchRate() const {
    return 120;
}

Pokemon::Id Herdier::getId() const {
    return Pokemon::Id::HERDIER;
}

namespace {
    std::jthread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(pokemonMutex);
        pokemonMap.insert(std::make_pair(Pokemon::Id::HERDIER,
                                         [] -> std::unique_ptr<Pokemon> { return std::make_unique<Herdier>(); }));
    });
}
