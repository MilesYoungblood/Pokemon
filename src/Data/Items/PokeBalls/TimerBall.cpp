//
// Created by Miles on 11/27/2023.
//

#include "PokeBalls.h"

namespace {
    void init() {
        pokeBalls.insert({ PokeBall::Id::TIMER_BALL, {
                "Great Ball",
                [](const Pokemon & /*pokemon*/, Time  /*time*/, int turn, bool  /*isCave*/) -> double {
                    return std::min(1 + turn * 1229 / 4069.0, 4.0);
                },
                [](Pokemon &pokemon) -> void {}
        }});
    }

    bool invoke{ (init(), true) };
}