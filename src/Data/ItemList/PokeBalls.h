//
// Created by Miles on 10/1/2023.
//

#pragma once

#include "../../Classes/Item/Pokeball.h"

struct GreatBall : public PokeBall {
    explicit GreatBall(int n) : PokeBall("Great Ball", n, 1.5) {}
};

struct UltraBall : public PokeBall {
    explicit UltraBall(int n) : PokeBall("Ultra Ball", n, 2.0) {}
};
