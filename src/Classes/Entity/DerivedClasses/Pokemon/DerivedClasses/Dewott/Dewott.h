//
// Created by Miles on 12/2/2023.
//

#pragma once

#include "../../Pokemon.h"

struct Dewott : public Pokemon {
    Dewott();

    std::string getName() const override;

    std::string getSpecies() const override;

    Type getType(bool type1) const override;

    double getHeight() const override;

    double getWeight() const override;

    int getCatchRate() const override;

    Pokemon::Id getId() const override;
};

namespace {
    inline AutoThread init([] -> void {
        pokemonLookupTable.insert(std::make_pair(Pokemon::Id::DEWOTT,
                                                 [] -> std::unique_ptr<Pokemon> { return std::make_unique<Dewott>(); }));
    });
}
