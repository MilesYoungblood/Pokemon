//
// Created by Miles on 12/2/2023.
//

#include "Snivy.h"

Snivy::Snivy() : Pokemon(Ability::Id::OVERGROW, 87.5, 1, 45, 45, 55, 45, 55, 63) {}

std::string Snivy::getName() const {
    return "Snivy";
}

std::string Snivy::getSpecies() const {
    return "Grass Snake";
}

Type Snivy::getType1() const {
    return Type::GRASS;
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

namespace {
    std::jthread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(pokemonMutex);
        pokemonMap.insert(std::make_pair(Pokemon::Id::SNIVY,
                                         [] -> std::unique_ptr<Pokemon> { return std::make_unique<Snivy>(); }));
    });
}
