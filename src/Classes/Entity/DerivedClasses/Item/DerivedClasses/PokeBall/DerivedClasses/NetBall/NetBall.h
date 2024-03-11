//
// Created by Miles Youngblood on 12/6/2023.
//

#pragma once

#include "../../PokeBall.h"

struct NetBall : public PokeBall {
    explicit NetBall(int n);

    NetBall(int n, int x, int y);

    [[nodiscard]] std::string getName() const override;

    [[nodiscard]] std::string getEffect() const override;

    [[nodiscard]] double getCatchRate(const Pokemon &pokemon, Time time, int turn, bool isCave) const override;
};
