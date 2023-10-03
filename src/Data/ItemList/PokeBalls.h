//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../../Classes/Item/Pokeball.h"

struct GreatBall : public PokeBall {
    explicit GreatBall(int n) : PokeBall(n, 1.5, "Great Ball") {}
};

struct UltraBall : public PokeBall {
    explicit UltraBall(int n) : PokeBall(n, 2.0, "Ultra Ball") {}
};
