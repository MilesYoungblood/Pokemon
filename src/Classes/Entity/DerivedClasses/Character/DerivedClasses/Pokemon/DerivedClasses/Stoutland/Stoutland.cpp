//
// Created by Miles on 12/2/2023.
//

#include "Stoutland.h"

Stoutland::Stoutland() : Pokemon(binomial() ? Ability::Id::INTIMIDATE : Ability::Id::SAND_RUSH, 50.0, 32,
                                 85, 110, 90, 45, 90, 80) {}

std::string Stoutland::getName() const {
    return "Stoutland";
}

std::string Stoutland::getSpecies() const {
    return "Big-Hearted";
}

Type Stoutland::getType1() const {
    return Type::NORMAL;
}

double Stoutland::getHeight() const {
    return 1.2;
}

double Stoutland::getWeight() const {
    return 61.0;
}

int Stoutland::getCatchRate() const {
    return 45;
}

Pokemon::Id Stoutland::getId() const {
    return Pokemon::Id::STOUTLAND;
}

namespace {
    std::jthread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(pokemonMutex);
        pokemonMap.insert(std::make_pair(Pokemon::Id::STOUTLAND,
                                         [] -> std::unique_ptr<Pokemon> { return std::make_unique<Stoutland>(); }));
    });
}
