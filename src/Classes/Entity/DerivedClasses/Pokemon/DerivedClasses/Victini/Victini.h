//
// Created by Miles Youngblood on 12/2/2023.
//

#pragma once

#include "../../Pokemon.h"

struct Victini : public Pokemon {
    Victini();

    std::string getName() const override;

    std::string getSpecies() const override;

    Type getType(bool type1) const override;

    double getHeight() const override;

    double getWeight() const override;

    int getCatchRate() const override;
};

namespace {
    inline void initialize() {
        typeMap.insert(std::make_pair(Pokemon::Id::VICTINI,
                                      [] -> std::unique_ptr <Pokemon> { return std::make_unique<Victini>(); }));
    }

    [[maybe_unused]] inline bool foo{ (initialize(), true) };
}