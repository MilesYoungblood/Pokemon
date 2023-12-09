//
// Created by Miles on 12/2/2023.
//

#include "Purrloin.h"

Purrloin::Purrloin() : Pokemon(binomial() ? Ability::Id::LIMBER : Ability::Id::UNBURDEN, 0.5, 1,
                               41, 50, 37, 50, 37, 66) {}

std::string Purrloin::getName() const {
    return "Purrloin";
}

std::string Purrloin::getSpecies() const {
    return "Devious";
}

Type Purrloin::getType(bool type1) const {
    return type1 ? Type::DARK : Type::NONE;
}

double Purrloin::getHeight() const {
    return 0.4;
}

double Purrloin::getWeight() const {
    return 10.1;
}

int Purrloin::getCatchRate() const {
    return 255;
}

Pokemon::Id Purrloin::getId() const {
    return Pokemon::Id::PURRLOIN;
}

namespace {
    std::jthread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(pokemonMutex);
        pokemonMap.insert(std::make_pair(Pokemon::Id::PURRLOIN,
                                         [] -> std::unique_ptr<Pokemon> { return std::make_unique<Purrloin>(); }));
    });
}
