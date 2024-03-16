//
// Created by Miles on 12/2/2023.
//

#pragma once

#include "../../Pokemon.h"

struct Tepig : public Pokemon {
    Tepig();

    std::string getName() const override;

    std::string getSpecies() const override;

    Type getType1() const override;

    double getHeight() const override;

    double getWeight() const override;

    int getCatchRate() const override;
};
