//
// Created by Miles on 12/2/2023.
//

#include "Tepig.h"

Tepig::Tepig() : Pokemon(Ability::Id::BLAZE, 87.5, 1, 65, 63, 45, 45, 45, 45) {}

std::string Tepig::getName() const {
    return "Tepig";
}

std::string Tepig::getSpecies() const {
    return "Fire Pig";
}

Type Tepig::getType1() const {
    return Type::FIRE;
}

double Tepig::getHeight() const {
    return 0.5;
}

double Tepig::getWeight() const {
    return 9.9;
}

int Tepig::getCatchRate() const {
    return 45;
}

Pokemon::Id Tepig::getId() const {
    return Pokemon::Id::TEPIG;
}

namespace {
    std::jthread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(pokemonMutex);
        pokemonMap.insert(std::make_pair(Pokemon::Id::TEPIG,
                                         [] -> std::unique_ptr<Pokemon> { return std::make_unique<Tepig>(); }));
    });
}
