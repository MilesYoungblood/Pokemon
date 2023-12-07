//
// Created by Miles Youngblood on 12/6/2023.
//

#pragma once

#include "../../Pokeball.h"

struct PremierBall : public PokeBall {
    explicit PremierBall(int n);

    [[nodiscard]] std::string getName() const override;

    [[nodiscard]] std::string getEffect() const override;

    [[nodiscard]] PokeBall::Id getId() const override;
};
