//
// Created by Miles Youngblood on 12/6/2023.
//

#pragma once

#include "../../PokeBall.h"

struct MasterBall final : PokeBall {
    explicit MasterBall(int n);

    MasterBall(int n, int x, int y);

    [[nodiscard]] std::string getEffect() const override;

    [[nodiscard]] double getCatchRate(const Pokemon &pokemon, std::size_t turn, bool isCave) const override;
};
