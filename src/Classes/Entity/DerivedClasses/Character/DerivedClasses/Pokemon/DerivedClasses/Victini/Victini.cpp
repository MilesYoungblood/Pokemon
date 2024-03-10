//
// Created by Miles Youngblood on 12/2/2023.
//

#include "Victini.h"

Victini::Victini() : Pokemon(Ability::Id::VICTORY_STAR, 15, 100, 100, 100, 100, 100, 100) {}

std::string Victini::getName() const {
    return "Victini";
}

std::string Victini::getSpecies() const {
    return "Victory";
}

Type Victini::getType1() const {
    return Type::PSYCHIC;
}

Type Victini::getType2() const {
    return Type::FIRE;
}

double Victini::getHeight() const {
    return 0.4;
}

double Victini::getWeight() const {
    return 4.0;
}

int Victini::getCatchRate() const {
    return 3;
}

Pokemon::Id Victini::getId() const {
    return Pokemon::Id::VICTINI;
}

namespace {
    std::jthread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(pokemonMutex);
        pokemonMap.insert(std::make_pair(Pokemon::Id::VICTINI,
                                         [] -> std::unique_ptr<Pokemon> { return std::make_unique<Victini>(); }));
    });
}
