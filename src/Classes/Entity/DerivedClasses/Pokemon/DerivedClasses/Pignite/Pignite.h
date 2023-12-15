//
// Created by Miles on 12/2/2023.
//

#pragma once

#include "../../Pokemon.h"

struct Pignite : public Pokemon {
    Pignite();

    std::string getName() const override;

    std::string getSpecies() const override;

    Type getType1() const override;

    Type getType2() const override;

    double getHeight() const override;

    double getWeight() const override;

    int getCatchRate() const override;

    Pokemon::Id getId() const override;
};
