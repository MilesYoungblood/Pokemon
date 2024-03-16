//
// Created by Miles on 12/2/2023.
//

#include "Purrloin.h"

Purrloin::Purrloin() : Pokemon(binomial() ? Ability::Id::LIMBER : Ability::Id::UNBURDEN, 50.0, 1,
                               41, 50, 37, 50, 37, 66) {}

std::string Purrloin::getName() const {
    return "Purrloin";
}

std::string Purrloin::getSpecies() const {
    return "Devious";
}

Type Purrloin::getType1() const {
    return Type::DARK;
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

namespace {
    std::jthread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(pokemonMutex);
        pokemonMap["Purrloin"] = [] -> std::unique_ptr<Pokemon> { return std::make_unique<Purrloin>(); };
    });
}
