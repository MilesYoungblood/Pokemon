//
// Created by Miles on 12/16/2023.
//

#pragma once

#include "../../Pokemon.h"

struct Pansear : public Pokemon {
    Pansear();

    std::string getName() const override;

    std::string getSpecies() const override;

    Type getType1() const override;

    double getHeight() const override;

    double getWeight() const override;

    int getCatchRate() const override;

    Pokemon::Id getId() const override;
};
