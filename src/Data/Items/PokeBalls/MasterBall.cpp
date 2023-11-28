//
// Created by Miles on 11/27/2023.
//

#include "PokeBalls.h"

namespace {
    void init() {
        pokeBalls.insert({ PokeBall::Id::MASTER_BALL, {
                "Master Ball",
                [](const Pokemon & /*pokemon*/, Time  /*time*/, int  /*turn*/, bool  /*isCave*/) -> double {
                    return 255.0;
                },
                [](Pokemon &pokemon) -> void {}
        }});
    }

    bool invoke{ (init(), true) };
}