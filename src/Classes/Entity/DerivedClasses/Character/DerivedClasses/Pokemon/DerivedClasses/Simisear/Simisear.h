//
// Created by Miles on 12/16/2023.
//

#include "../../Pokemon.h"

struct Simisear : public Pokemon {
    Simisear();

    std::string getName() const override;

    std::string getSpecies() const override;

    Type getType1() const override;

    double getHeight() const override;

    double getWeight() const override;

    int getCatchRate() const override;

    Pokemon::Id getId() const override;
};
