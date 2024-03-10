//
// Created by Miles on 12/16/2023.
//

#include "Pansear.h"

Pansear::Pansear() : Pokemon(Ability::Id::GLUTTONY, 87.5, 1, 50, 53, 48, 53, 48, 64) {}

std::string Pansear::getName() const {
    return "Pansear";
}

std::string Pansear::getSpecies() const {
    return "High Temp";
}

Type Pansear::getType1() const {
    return Type::FIRE;
}

double Pansear::getHeight() const {
    return 0.6;
}

double Pansear::getWeight() const {
    return 11.0;
}

int Pansear::getCatchRate() const {
    return 190;
}

Pokemon::Id Pansear::getId() const {
    return Pokemon::Id::PANSEAR;
}

namespace {
    std::jthread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(pokemonMutex);
        pokemonMap.insert(std::make_pair(Pokemon::Id::PANSEAR,
                                         [] -> std::unique_ptr<Pokemon> { return std::make_unique<Pansear>(); }));
    });
}
