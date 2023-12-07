//
// Created by Miles Youngblood on 12/6/2023.
//

#pragma once

#include "../../Pokeball.h"

struct HealBall : public PokeBall {
    explicit HealBall(int n);

    [[nodiscard]] std::string getName() const override;

    [[nodiscard]] std::string getEffect() const override;

    void postCatch(Pokemon &pokemon) const override;

    [[nodiscard]] PokeBall::Id getId() const override;
};
