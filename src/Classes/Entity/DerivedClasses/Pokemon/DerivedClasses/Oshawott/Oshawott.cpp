//
// Created by Miles on 12/2/2023.
//

#include "Oshawott.h"

Oshawott::Oshawott() : Pokemon(Ability::Id::TORRENT, 87.5, 1, 55, 55, 45, 63, 45, 45) {}

std::string Oshawott::getName() const {
    return "Oshawott";
}

std::string Oshawott::getSpecies() const {
    return "Sea Otter";
}

Type Oshawott::getType(bool type1) const {
    return type1 ? Type::WATER : Type::NONE;
}

double Oshawott::getHeight() const {
    return 0.5;
}

double Oshawott::getWeight() const {
    return 5.9;
}

int Oshawott::getCatchRate() const {
    return 45;
}

Pokemon::Id Oshawott::getId() const {
    return Pokemon::Id::OSHAWOTT;
}

namespace {
    std::jthread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(pokemonMutex);
        pokemonMap.insert(std::make_pair(Pokemon::Id::OSHAWOTT,
                                         [] -> std::unique_ptr<Pokemon> { return std::make_unique<Oshawott>(); }));
    });
}
