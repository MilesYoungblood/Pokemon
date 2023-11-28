//
// Created by Miles on 11/27/2023.
//

#include "PokeBalls.h"

namespace {
    void init() {
        pokeBalls.insert({ PokeBall::Id::QUICK_BALL, {
                "Quick Ball",
                [](const Pokemon & /*pokemon*/, Time  /*time*/, int turn, bool  /*isCave*/) -> double {
                    return turn > 1 ? 1.0 : 5.0;
                },
                [](Pokemon &pokemon) -> void {}
        }});
    }

    bool invoke{ (init(), true) };
}