//
// Created by Miles on 12/2/2023.
//

#include "Patrat.h"

Patrat::Patrat() : Pokemon(binomial() ? Ability::Id::RUN_AWAY : Ability::Id::KEEN_EYE, 50.0, 1,
                           45, 55, 39, 35, 39, 42) {}

std::string Patrat::getName() const {
    return "Patrat";
}

std::string Patrat::getSpecies() const {
    return "Scout";
}

Type Patrat::getType1() const {
    return Type::NORMAL;
}

double Patrat::getHeight() const {
    return 0.5;
}

double Patrat::getWeight() const {
    return 11.6;
}

int Patrat::getCatchRate() const {
    return 255;
}

Pokemon::Id Patrat::getId() const {
    return Pokemon::Id::PATRAT;
}

namespace {
    std::jthread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(pokemonMutex);
        pokemonMap.insert(std::make_pair(Pokemon::Id::PATRAT,
                                         [] -> std::unique_ptr<Pokemon> { return std::make_unique<Patrat>(); }));
    });
}
