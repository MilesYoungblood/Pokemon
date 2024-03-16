//
// Created by Miles Youngblood on 12/15/2023.
//

#include "Pansage.h"

Pansage::Pansage() : Pokemon(Ability::Id::GLUTTONY, 87.5, 1, 50, 53, 48, 53, 48, 64) {}

std::string Pansage::getName() const {
    return "Pansage";
}

std::string Pansage::getSpecies() const {
    return "Grass Monkey";
}

Type Pansage::getType1() const {
    return Type::GRASS;
}

double Pansage::getHeight() const {
    return 0.6;
}

double Pansage::getWeight() const {
    return 10.5;
}

int Pansage::getCatchRate() const {
    return 190;
}

namespace {
    std::jthread init([] -> void {
        const std::lock_guard<std::mutex> lock_guard(pokemonMutex);
        pokemonMap["Pansage"] = [] -> std::unique_ptr<Pokemon> { return std::make_unique<Pansage>(); };
    });
}
