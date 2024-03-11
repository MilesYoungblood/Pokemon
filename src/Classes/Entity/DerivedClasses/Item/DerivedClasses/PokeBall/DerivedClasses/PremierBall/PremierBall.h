//
// Created by Miles Youngblood on 12/6/2023.
//

#pragma once

#include "../../PokeBall.h"

struct PremierBall : public PokeBall {
    explicit PremierBall(int n);

    PremierBall(int n, int x, int y);

    [[nodiscard]] std::string getName() const override;

    [[nodiscard]] std::string getEffect() const override;
};
