//
// Created by Miles on 12/2/2023.
//

#include "Liepard.h"

Liepard::Liepard() : Pokemon(binomial() ? Ability::Id::LIMBER : Ability::Id::UNBURDEN, 50.0, 20, 41,
                             50, 37, 50, 37, 66) {}

std::string Liepard::getName() const {
    return "Liepard";
}

std::string Liepard::getSpecies() const {
    return "Cruel";
}

Type Liepard::getType1() const {
    return Type::DARK;
}

double Liepard::getHeight() const {
    return 1.1;
}

double Liepard::getWeight() const {
    return 37.5;
}

int Liepard::getCatchRate() const {
    return 90;
}

Pokemon::Id Liepard::getId() const {
    return Pokemon::Id::LIEPARD;
}

namespace {
    std::jthread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(pokemonMutex);
        pokemonMap.insert(std::make_pair(Pokemon::Id::LIEPARD,
                                         [] -> std::unique_ptr<Pokemon> { return std::make_unique<Liepard>(); }));
    });
}
