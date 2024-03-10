//
// Created by Miles Youngblood on 12/15/2023.
//

#pragma once

#include "../../Pokemon.h"

struct Pansage : public Pokemon {
    Pansage();

    std::string getName() const override;

    std::string getSpecies() const override;

    Type getType1() const override;

    double getHeight() const override;

    double getWeight() const override;

    int getCatchRate() const override;

    Pokemon::Id getId() const override;
};
