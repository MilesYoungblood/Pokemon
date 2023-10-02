//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../../Classes/Item/Pokeball.h"

struct GreatBall : public PokeBall {
    explicit GreatBall(int quantity) : PokeBall(quantity, 1.5, "Great Ball") {}
};

struct UltraBall : public PokeBall {
    explicit UltraBall(int quantity) : PokeBall(quantity, 2.0, "Ultra Ball") {}
};
