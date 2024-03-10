//
// Created by Miles Youngblood on 12/6/2023.
//

#pragma once

#include "../../Pokeball.h"

struct MasterBall : public PokeBall {
    explicit MasterBall(int n);

    MasterBall(int n, int x, int y);

    [[nodiscard]] std::string getName() const override;

    [[nodiscard]] std::string getEffect() const override;

    [[nodiscard]] double getCatchRate(const Pokemon &pokemon, Time time, int turn, bool isCave) const override;

    [[nodiscard]] PokeBall::Id getId() const override;
};
