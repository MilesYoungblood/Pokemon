//
// Created by Miles Youngblood on 12/15/2023.
//

#include "Simisage.h"

Simisage::Simisage() : Pokemon(Ability::Id::GLUTTONY, 87.5, 1, 75, 98, 63, 98, 63, 101) {}

std::string Simisage::getName() const {
    return "Simisage";
}

std::string Simisage::getSpecies() const {
    return "Thorn Monkey";
}

Type Simisage::getType1() const {
    return Type::GRASS;
}

double Simisage::getHeight() const {
    return 1.1;
}

double Simisage::getWeight() const {
    return 30.5;
}

int Simisage::getCatchRate() const {
    return 75;
}

namespace {
    std::jthread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(pokemonMutex);
        pokemonMap["Simisage"] = [] -> std::unique_ptr<Pokemon> { return std::make_unique<Simisage>(); };
    });
}
