//
// Created by Miles on 12/2/2023.
//

#pragma once

#include "../../Pokemon.h"

struct Purrloin : public Pokemon {
    Purrloin();

    std::string getName() const override;

    std::string getSpecies() const override;

    Type getType(bool type1) const override;

    double getHeight() const override;

    double getWeight() const override;

    int getCatchRate() const override;

    Pokemon::Id getId() const override;
};
