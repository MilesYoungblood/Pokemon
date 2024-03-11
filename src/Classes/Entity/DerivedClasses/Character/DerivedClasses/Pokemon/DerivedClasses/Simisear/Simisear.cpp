//
// Created by Miles on 12/16/2023.
//

#include "Simisear.h"

Simisear::Simisear() : Pokemon(Ability::Id::GLUTTONY, 87.5, 1, 75, 98, 63, 98, 63, 101) {}

std::string Simisear::getName() const {
    return "Simisear";
}

std::string Simisear::getSpecies() const {
    return "Ember";
}

Type Simisear::getType1() const {
    return Type::FIRE;
}

double Simisear::getHeight() const {
    return 1.0;
}

double Simisear::getWeight() const {
    return 28.0;
}

int Simisear::getCatchRate() const {
    return 75;
}

Pokemon::Id Simisear::getId() const {
    return Pokemon::Id::SIMISEAR;
}

namespace {
    std::jthread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(pokemonMutex);
        pokemonMap["Simisear"] = [] -> std::unique_ptr<Pokemon> { return std::make_unique<Simisear>(); };
    });
}
