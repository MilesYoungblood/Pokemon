//
// Created by Miles Youngblood on 12/6/2023.
//

#pragma once

#include "../PokeBall.h"

struct UltraBall final : PokeBall {
    explicit UltraBall(int n);

    UltraBall(int n, int x, int y);

    [[nodiscard]] std::string getEffect() const override;

    [[nodiscard]] double getCatchRate(const Pokemon &pokemon, std::size_t turn, bool isCave) const override;
};
