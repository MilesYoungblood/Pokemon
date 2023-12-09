//
// Created by Miles on 12/2/2023.
//

#include "Watchog.h"

Watchog::Watchog() : Pokemon(binomial() ? Ability::Id::ILLUMINATE : Ability::Id::KEEN_EYE, 0.5, 20,
                             60, 85, 69, 60, 69, 77) {}

std::string Watchog::getName() const {
    return "Watchog";
}

std::string Watchog::getSpecies() const {
    return "Lookout";
}

Type Watchog::getType(bool type1) const {
    return type1 ? Type::NORMAL : Type::NONE;
}

double Watchog::getHeight() const {
    return 1.1;
}

double Watchog::getWeight() const {
    return 27.0;
}

int Watchog::getCatchRate() const {
    return 255;
}

Pokemon::Id Watchog::getId() const {
    return Pokemon::Id::WATCHOG;
}

namespace {
    std::jthread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(pokemonMutex);
        pokemonMap.insert(std::make_pair(Pokemon::Id::WATCHOG,
                                         [] -> std::unique_ptr<Pokemon> { return std::make_unique<Watchog>(); }));
    });
}
