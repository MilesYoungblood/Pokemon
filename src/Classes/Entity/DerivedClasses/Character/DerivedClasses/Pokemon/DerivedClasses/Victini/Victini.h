//
// Created by Miles Youngblood on 12/2/2023.
//

#pragma once
#pragma once

#include "../../Pokemon.h"

struct Victini : public Pokemon {
    Victini();

    std::string getName() const override;

    std::string getSpecies() const override;

    Type getType1() const override;

    Type getType2() const override;

    double getHeight() const override;

    double getWeight() const override;

    int getCatchRate() const override;
};
