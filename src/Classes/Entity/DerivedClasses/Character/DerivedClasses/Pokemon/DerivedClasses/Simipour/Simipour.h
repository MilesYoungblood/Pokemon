//
// Created by Miles on 12/16/2023.
//

#pragma once

#include "../../Pokemon.h"

struct Simipour : public Pokemon {
    Simipour();

    std::string getName() const override;

    std::string getSpecies() const override;

    Type getType1() const override;

    double getHeight() const override;

    double getWeight() const override;

    int getCatchRate() const override;
};
