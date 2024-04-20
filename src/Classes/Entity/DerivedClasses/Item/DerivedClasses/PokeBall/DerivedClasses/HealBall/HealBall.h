//
// Created by Miles Youngblood on 12/6/2023.
//

#pragma once

#include "../../PokeBall.h"

struct HealBall final : PokeBall {
    explicit HealBall(int n);

    HealBall(int n, int x, int y);

    [[nodiscard]] std::string getEffect() const override;

    void postCatch(Pokemon &pokemon) const override;
};
