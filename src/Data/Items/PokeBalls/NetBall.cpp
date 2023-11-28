//
// Created by Miles on 11/27/2023.
//

#include "PokeBalls.h"

namespace {
    void init() {
        pokeBalls.insert({ PokeBall::Id::NET_BALL, {
                "Net Ball",
                [](const Pokemon &pokemon, Time  /*time*/, int  /*turn*/, bool  /*isCave*/) -> double {
                    if (pokemon.getType(true) == Type::WATER or pokemon.getType(true) == Type::BUG or
                        pokemon.getType(false) == Type::WATER or pokemon.getType(false) == Type::BUG) {
                        return 3.5;
                    }
                    return 1.0;
                },
                [](Pokemon &pokemon) -> void {}
        }});
    }

    bool invoke{ (init(), true) };
}