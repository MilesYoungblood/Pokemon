//
// Created by Miles on 12/2/2023.
//

#include "Dewott.h"

Dewott::Dewott() : Pokemon(Ability::Id::TORRENT, 87.5, 17, 75, 75, 60, 83, 60, 60) {}

std::string Dewott::getName() const {
    return "Dewott";
}

std::string Dewott::getSpecies() const {
    return "Discipline";
}

Type Dewott::getType1() const {
    return Type::WATER;
}

double Dewott::getHeight() const {
    return 0.8;
}

double Dewott::getWeight() const {
    return 24.5;
}

int Dewott::getCatchRate() const {
    return 45;
}

Pokemon::Id Dewott::getId() const {
    return Pokemon::Id::DEWOTT;
}

namespace {
    std::jthread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(pokemonMutex);
        pokemonMap.insert(std::make_pair(Pokemon::Id::DEWOTT,
                                         [] -> std::unique_ptr<Pokemon> { return std::make_unique<Dewott>(); }));
    });
}
