//
// Created by Miles on 12/2/2023.
//

#include "Samurott.h"

Samurott::Samurott() : Pokemon(Ability::Id::TORRENT, 87.5, 36, 95, 100, 85, 108, 70, 70) {}

std::string Samurott::getName() const {
    return "Samurott";
}

std::string Samurott::getSpecies() const {
    return "Formidable";
}

Type Samurott::getType(bool type1) const {
    return type1 ? Type::WATER : Type::NONE;
}

double Samurott::getHeight() const {
    return 1.5;
}

double Samurott::getWeight() const {
    return 94.6;
}

int Samurott::getCatchRate() const {
    return 45;
}

Pokemon::Id Samurott::getId() const {
    return Pokemon::Id::SAMUROTT;
}

namespace {
    std::jthread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(pokemonMutex);
        pokemonMap.insert(std::make_pair(Pokemon::Id::SAMUROTT,
                                         [] -> std::unique_ptr<Pokemon> { return std::make_unique<Samurott>(); }));
    });
}
