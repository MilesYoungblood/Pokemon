//
// Created by Miles on 11/27/2023.
//

#include "PokeBalls.h"

namespace {
    void init() {
        pokeBalls.insert({ PokeBall::Id::DUSK_BALL, {
                "Dusk Ball",
                [](const Pokemon & /*pokemon*/, Time time, int  /*turn*/, bool isCave) -> double {
                    return time == Time::NIGHT or isCave ? 3.5 : 1.0;
                },
                [](Pokemon &pokemon) -> void {}
        }});
    }

    bool invoke{ (init(), true) };
}