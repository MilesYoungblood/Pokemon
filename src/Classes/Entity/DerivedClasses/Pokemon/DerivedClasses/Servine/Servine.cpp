//
// Created by Miles on 12/2/2023.
//

#include "Servine.h"

Servine::Servine() : Pokemon(Ability::Id::OVERGROW, 87.5, 17, 60, 60, 75, 60, 75, 83) {}

std::string Servine::getName() const {
    return "Servine";
}

std::string Servine::getSpecies() const {
    return "Grass Snake";
}

Type Servine::getType1() const {
    return Type::GRASS;
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

namespace {
    std::jthread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(pokemonMutex);
        pokemonMap.insert(std::make_pair(Pokemon::Id::SERVINE,
                                         [] -> std::unique_ptr<Pokemon> { return std::make_unique<Servine>(); }));
    });
}
