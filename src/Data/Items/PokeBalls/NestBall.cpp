//
// Created by Miles on 11/27/2023.
//

#include "PokeBalls.h"

namespace {
    void init() {
        pokeBalls.insert({ PokeBall::Id::NEST_BALL, {
                "Nest Ball",
                [](const Pokemon &pokemon, Time  /*time*/, int  /*turn*/, bool  /*isCave*/) -> double {
                    return ((41 - pokemon.getLevel()) * 4069 / 10.0) / 4096.0;
                },
                [](Pokemon &pokemon) -> void {}
        }});
    }

    bool invoke{ (init(), true) };
}